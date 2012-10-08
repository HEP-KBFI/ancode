// -*- C++ -*-
//
// Package:    SingleTopAnalysis
// Class:      SingleTopAnalysis
// 
/**\class SingleTopAnalysis SingleTopAnalysis.cc AnalysisCode/SingleTopAnalysis/src/SingleTopAnalysis.cc

 Description: Analysis code for single top polarization analysis

 Implementation:
     We perform analysis chain of the single top
*/
//
// Original Author:  Mario Kadastik
//         Created:  Thu Oct  4 14:20:54 EEST 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Generic particle classes
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CMGTools/External/interface/PileupJetIdentifier.h"
#include "DataFormats/PatCandidates/interface/MET.h"

// Vertices for matching of leptons/jets
#include "DataFormats/VertexReco/interface/Vertex.h"

// Services for histogramming and trees
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"

//
// class declaration
//

class SingleTopAnalysis : public edm::EDAnalyzer {
   public:
      explicit SingleTopAnalysis(const edm::ParameterSet&);
      ~SingleTopAnalysis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
      edm::InputTag goodMuLab, vetoMuLab, goodElLab, vetoElLab, jetLab, metLab, vertLab;
      TH1D *cflow;
      reco::Vertex PV;
      bool debug,PUveto;
      double bTagCut, totalJets, looseJets, tightJets;
      std::string bTagger;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
SingleTopAnalysis::SingleTopAnalysis(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   goodMuLab  = iConfig.getParameter<edm::InputTag>("goodMuons");
   vetoMuLab  = iConfig.getParameter<edm::InputTag>("vetoMuons");
   goodElLab  = iConfig.getParameter<edm::InputTag>("goodElectrons");
   vetoElLab  = iConfig.getParameter<edm::InputTag>("vetoElectrons");
   jetLab     = iConfig.getParameter<edm::InputTag>("jets");
   metLab     = iConfig.getParameter<edm::InputTag>("met");
   vertLab    = iConfig.getParameter<edm::InputTag>("vertex");
   bTagger    = iConfig.getParameter<std::string>("bTagger");
   bTagCut    = iConfig.getParameter<double>("bTagCut");
   debug      = iConfig.getParameter<bool>("debug");
   PUveto     = iConfig.getParameter<bool>("PUveto");
   totalJets = 0;
   looseJets = 0;
   tightJets = 0;
}


SingleTopAnalysis::~SingleTopAnalysis()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
SingleTopAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace pat;
   using namespace std;

   Handle<MuonCollection> gmu;
   iEvent.getByLabel(goodMuLab,gmu);
   
   Handle<MuonCollection> vmu;
   iEvent.getByLabel(vetoMuLab,vmu);
   
   Handle<ElectronCollection> gel;
   iEvent.getByLabel(goodElLab,gel);
   
   Handle<ElectronCollection> vel;
   iEvent.getByLabel(goodElLab,vel);
   
   // Let's fill for every event to keep track how many we processed
   cflow->Fill(0);

   // Pick up Vertex collection and select the first one for primary vertex
   Handle<vector<reco::Vertex>> vertex;
   iEvent.getByLabel(vertLab,vertex);

   PV = *(vertex->begin());
   if (debug) cout << "Primary vertex location: " << PV.position() << endl;

   // Run through the good muons and apply final few missing criteria and make sure we only get 1 at maximum
   int nSigMu = 0;
   for (MuonCollection::const_iterator mu = gmu->begin(); mu != gmu->end(); mu++) {
     if (debug) cout << "Mu: pT=" << mu->pt() << " eta=" << mu->eta() << " status=" << mu->status() << endl;
     if (fabs(mu->vertex().z() - PV.position().z()) < 0.5) nSigMu++;
   }

   // If already at this step we have too many muons, give up
   if (nSigMu != 1) return;
   cflow->Fill(1);
   
   // Quick check, if there are more than 2 veto muons we're already in trouble because it will contain the signal muon as well
   if (vmu->size() > 1) return;
   cflow->Fill(2);

   // We shouldn't have electrons in the veto collection, let's check that
   if (vel->size()) return;
   cflow->Fill(3);

   // Check the jet collection and make sure we have the right amount of jets passing criteria. We apply the Loose PU veto here

   Handle<View<Jet> > jets;
   iEvent.getByLabel(jetLab, jets);

   Handle<ValueMap<float> > puJetIdMVA;
   iEvent.getByLabel("puJetMva","fullDiscriminant", puJetIdMVA);

   Handle<ValueMap<int> > puJetIdFlag;
   iEvent.getByLabel("puJetMva","fullId", puJetIdFlag);

   int nJet = 0;
   int nBjet = 0;
   for (unsigned int ij = 0; ij < jets->size(); ij++) {
     const Jet & it = jets->at(ij);
     totalJets++;
     float mva = (*puJetIdMVA)[jets->refAt(ij)];
     int idflag = (*puJetIdFlag)[jets->refAt(ij)];
     if (debug) cout << "Jet: " << it.pt() << " mva=" << mva << " idflag=" << idflag << " PU pass=" << PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kLoose ) << endl;
     if ( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kLoose ) ) looseJets++;
     if ( PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kTight ) ) tightJets++;

     if ( !PUveto || PileupJetIdentifier::passJetId( idflag, PileupJetIdentifier::kLoose ) ) {
       // We have an adequate jet that isn't PU jet likely, let's count them
       nJet++;
       // B-tag point from: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP we use CSV Medium
       if (it.bDiscriminator(bTagger) > bTagCut) nBjet++;
     }
   }

   // Next step is we need exactly two jets
   if (nJet != 2) return;
   cflow->Fill(4);

   // Here we should check the W mass
   Handle<METCollection> mets;
   iEvent.getByLabel(metLab,mets);

   double mt = 0;
   double mx = mets->begin()->px();
   double my = mets->begin()->py();
   double met = mets->begin()->pt();

   double mux = gmu->begin()->px();
   double muy = gmu->begin()->py();
   double mupt = gmu->begin()->pt();

   mt = sqrt( pow(mupt+met,2) - pow(mux+mx,2) - pow(muy+my,2) );

   if (mt < 40) return;
   cflow->Fill(5);

   if (nBjet != 1) return;
   cflow->Fill(6);
}


// ------------ method called once each job just before starting event loop  ------------
void 
SingleTopAnalysis::beginJob()
{
  edm::Service<TFileService> fs;
  cflow = fs->make<TH1D>("cflow","Cut flow for sync",10,0,10);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SingleTopAnalysis::endJob() 
{
  using namespace std;
  cout << "Total=" << totalJets << " loose=" << looseJets << " tight=" << tightJets << endl;
}

// ------------ method called when starting to processes a run  ------------
void 
SingleTopAnalysis::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SingleTopAnalysis::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
SingleTopAnalysis::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SingleTopAnalysis::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SingleTopAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SingleTopAnalysis);
