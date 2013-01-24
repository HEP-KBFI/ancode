// -*- C++ -*-
//
// Package:    SingleTopSidebands
// Class:      SingleTopSidebands
// 
/**\class SingleTopSidebands SingleTopSidebands.cc AnalysisCode/SingleTopSidebands/src/SingleTopSidebands.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Liis Rebane
//         Created:  Wed Jan 23 19:52:40 EET 2013
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

// Objects for analysis
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "AnalysisCode/AnalysisDataFormats/interface/Neutrino.h"
#include "AnalysisCode/AnalysisDataFormats/interface/NeutrinoFwd.h"

// Services for histogramming and trees
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include <TMath.h>

//
// class declaration
//

class SingleTopSidebands : public edm::EDAnalyzer {
   public:
      explicit SingleTopSidebands(const edm::ParameterSet&);
      ~SingleTopSidebands();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      edm::InputTag goodLepLab, vetoLepLab, metLab;
      std::vector<int> lepFlavors;

  TH1D *mtW_2j0t, *met_2j0t, *topMass_2j0t, *lightJetEta_2j0t, *jetEta_2j0t; 
  TH1D *mtW_3j1t, *met_3j1t, *topMass_3j1t, *lightJetEta_3j1t, *jetEta_3j1t;

      // ----------member data ---------------------------
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
SingleTopSidebands::SingleTopSidebands(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  goodLepLab = iConfig.getParameter<edm::InputTag>("goodLeptons");
  vetoLepLab = iConfig.getParameter<edm::InputTag>("vetoLeptons");
  metLab     = iConfig.getParameter<edm::InputTag>("met");

  lepFlavors = iConfig.getParameter<std::vector<int> >("leptonFlavors");

}


SingleTopSidebands::~SingleTopSidebands()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
SingleTopSidebands::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace pat;

   Handle<reco::CandidateCollection> leps;
   iEvent.getByLabel(goodLepLab,leps);

   Handle<reco::CandidateCollection> veto;
   iEvent.getByLabel(vetoLepLab,veto);

   Handle<METCollection> mets;
   iEvent.getByLabel(metLab,mets);

   Handle<JetCollection> ljets;
   iEvent.getByLabel("lightJet",ljets);

   Handle<JetCollection> bjets;
   iEvent.getByLabel("bJet",bjets);

   Handle<NeutrinoCollection> nus;
   iEvent.getByLabel("neutrinos",nus);
   
   double mt = 0, mett = 0, topMass = 0;

   //----------------check lepton flavour----------------------
   bool pass_lepFlavor = false;
   
   if( leps->size() ){
     int pid = abs(leps->begin()->pdgId());

     for (unsigned int i = 0; i<lepFlavors.size(); i++)
       if (pid == lepFlavors[i]) pass_lepFlavor = true;

     double mx = mets->begin()->px();
     double my = mets->begin()->py();
     mett = mets->begin()->pt();

     double lepx = leps->begin()->px();
     double lepy = leps->begin()->py();
     double leppt = leps->begin()->pt();

     mt = sqrt( pow(leppt+mett,2) - pow(lepx+mx,2) - pow(lepy+my,2) );

   }

   //------------------check for veto muons and electrons------------------
   bool muveto = false;
   bool elveto = false;
   
   for (reco::CandidateCollection::const_iterator it = veto->begin(); it != veto->end(); it++) {
     if (abs(it->pdgId()) == 11) elveto = true;
     if (abs(it->pdgId()) == 13) muveto = true;
   }
   
   //---------------2 jets 0 tag---------------------------------

   if( leps->size() == 1 && pass_lepFlavor && !muveto && !elveto && bjets->size() == 0 && ljets->size() == 2 ){

     reco::Candidate::LorentzVector p4top = reco::Candidate::LorentzVector(0,0,0,0);

     if( ljets->at(0).bDiscriminator("trackCountingHighPurBJetTags") > ljets->at(1).bDiscriminator("trackCountingHighPurBJetTags") ){
       p4top = leps->begin()->p4() + ljets->at(0).p4() + nus->begin()->P4Nu();
       topMass = TMath::Sqrt( p4top.M2() );

       topMass_2j0t->Fill(topMass);
       lightJetEta_2j0t->Fill( fabs(ljets->at(1).eta() ) );    
     }
     else{
       p4top = leps->begin()->p4() + ljets->at(1).p4() + nus->begin()->P4Nu();
       topMass = TMath::Sqrt( p4top.M2() );

       topMass_2j0t->Fill(topMass);
       lightJetEta_2j0t->Fill( fabs(ljets->at(0).eta() ) );
     }

     mtW_2j0t->Fill(mt);
     met_2j0t->Fill(mett);
     jetEta_2j0t->Fill( fabs(ljets->at(0).eta()) );
     jetEta_2j0t->Fill( fabs(ljets->at(1).eta()) );

   }

   //--------------------------- 3 jets 1 tag-----------------------------------
   if( leps->size() == 1 && pass_lepFlavor && !muveto && !elveto && bjets->size() == 1 && ljets->size() == 3 ){

     reco::Candidate::LorentzVector p4top = reco::Candidate::LorentzVector(0,0,0,0);

     if( ljets->at(0).bDiscriminator("trackCountingHighPurBJetTags") > ljets->at(1).bDiscriminator("trackCountingHighPurBJetTags") ){
       p4top = leps->begin()->p4() + ljets->at(0).p4() + nus->begin()->P4Nu();
       topMass = TMath::Sqrt( p4top.M2() );

       topMass_3j1t->Fill(topMass);
       lightJetEta_3j1t->Fill( fabs(ljets->at(1).eta() ) );
     }
     else{
       p4top = leps->begin()->p4() + ljets->at(1).p4() + nus->begin()->P4Nu();
       topMass = TMath::Sqrt( p4top.M2() );

       topMass_3j1t->Fill(topMass);
       lightJetEta_3j1t->Fill( fabs(ljets->at(0).eta() ) );
     }

     mtW_3j1t->Fill(mt);
     met_3j1t->Fill(mett);
     jetEta_3j1t->Fill( fabs(ljets->at(0).eta()) );
     jetEta_3j1t->Fill( fabs(ljets->at(1).eta()) );

   }

}


// ------------ method called once each job just before starting event loop  ------------
void 
SingleTopSidebands::beginJob()
{
  edm::Service<TFileService> fs;
  topMass_2j0t = fs->make<TH1D>("topMass_2j0t","Mass of top quark",300,0,500);
  mtW_2j0t = fs->make<TH1D>("mtW_2j0t","mT of W from met",500,0,500);
  met_2j0t = fs->make<TH1D>("met_2j0t","met",500,0,500);
  jetEta_2j0t = fs->make<TH1D>("jetEta_2j0t","jet eta",100,-0.1,5);
  lightJetEta_2j0t = fs->make<TH1D>("lightJetEta_2j0t","jet eta",100,-0.1,5);

  topMass_3j1t = fs->make<TH1D>("topMass_3j1t","Mass of top quark",300,0,500);
  mtW_3j1t = fs->make<TH1D>("mtW_3j1t","mT of W from met",500,0,500);
  met_3j1t = fs->make<TH1D>("met_3j1t","met",500,0,500);
  jetEta_3j1t = fs->make<TH1D>("jetEta_3j1t","jet eta",100,-0.1,5);
  lightJetEta_3j1t = fs->make<TH1D>("lightJetEta_3j1t","jet eta",100,-0.1,5);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SingleTopSidebands::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
SingleTopSidebands::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SingleTopSidebands::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
SingleTopSidebands::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SingleTopSidebands::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SingleTopSidebands::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SingleTopSidebands);
