// -*- C++ -*-
//
// Package:    SingleTopFilter
// Class:      SingleTopFilter
// 
/**\class SingleTopFilter SingleTopFilter.cc AnalysisCode/SingleTopFilter/src/SingleTopFilter.cc

 Description: Filter events based on single top reference selection

 Implementation:
     The selection is based on requiring exactly one lepton, two jets of which one is b-tagged and passing W mass constraint. The steps will be
     logged for efficiency in a histogram
*/
//
// Original Author:  Mario Kadastik
//         Created:  Thu Oct 18 11:22:04 EEST 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Objects for analysis
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "AnalysisCode/AnalysisDataFormats/interface/Neutrino.h"
#include "AnalysisCode/AnalysisDataFormats/interface/NeutrinoFwd.h"

// Services for histogramming and trees
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
//
//
// class declaration
//

class SingleTopFilter : public edm::EDFilter {
   public:
      explicit SingleTopFilter(const edm::ParameterSet&);
      ~SingleTopFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      bool debug;
      edm::InputTag goodLepLab, vetoLepLab, jetLab, metLab;
      std::string bTagger;
      double bTagCut;
      TH1D *cflow;
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
SingleTopFilter::SingleTopFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   debug      = iConfig.getParameter<bool>("debug");
   goodLepLab = iConfig.getParameter<edm::InputTag>("goodLeptons");
   vetoLepLab = iConfig.getParameter<edm::InputTag>("vetoLeptons");
   jetLab     = iConfig.getParameter<edm::InputTag>("jets");
   metLab     = iConfig.getParameter<edm::InputTag>("met");
   bTagger    = iConfig.getParameter<std::string>("bTagger");
   bTagCut    = iConfig.getParameter<double>("bTagCut");
}


SingleTopFilter::~SingleTopFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
SingleTopFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace pat;

   // Let's count all events
   cflow->Fill(0);

   // Let's start with good leptons
   Handle<reco::CandidateCollection> leps;
   iEvent.getByLabel(goodLepLab,leps);

   if (leps->size() != 1) return false;
   cflow->Fill(1); // Passed single good lepton cut

   // Next let's read the veto collection and see if there are any muons/electrons to veto the event
   bool muveto = false;
   bool elveto = false;
   Handle<reco::CandidateCollection> veto;
   iEvent.getByLabel(vetoLepLab,veto);

   for (reco::CandidateCollection::const_iterator it = veto->begin(); it != veto->end(); it++) {
     if (abs(it->pdgId()) == 11) elveto = true;
     if (abs(it->pdgId()) == 13) muveto = true;
   }

   if (muveto) return false;
   cflow->Fill(2); // Passed muon veto cut

   if (elveto) return false;
   cflow->Fill(3); // Passed also electron veto cut

   // Let's turn to jets
   Handle<JetCollection> jets;
   iEvent.getByLabel(jetLab,jets);

   if (jets->size() != 2) return false;
   cflow->Fill(4); // Passed jet counting cut

   // Now W mass constraint
   Handle<METCollection> mets;
   iEvent.getByLabel(metLab,mets);

   double mt = 0;
   double mx = mets->begin()->px();
   double my = mets->begin()->py();
   double met = mets->begin()->pt();

   double lepx = leps->begin()->px();
   double lepy = leps->begin()->py();
   double leppt = leps->begin()->pt();

   mt = sqrt( pow(leppt+met,2) - pow(lepx+mx,2) - pow(lepy+my,2) );

   //----- alternatively get mt from the neutrino obect----
   Handle<std::vector<Neutrino> > nts;
   iEvent.getByLabel("neutrinos", nts);

   mt = (nts->begin())->mTW();
   //----------------------------------------------------

   if (mt < 40) return false;
   cflow->Fill(5);

   // And finally, do we have exactly one b-jet?
   int nBjet = 0;
   for (JetCollection::const_iterator it = jets->begin(); it != jets->end(); it++)
     if (it->bDiscriminator(bTagger) > bTagCut) 
       nBjet++;

   if (nBjet != 1) return false;
   cflow->Fill(6); // Final passing count

   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
SingleTopFilter::beginJob()
{
  edm::Service<TFileService> fs;
  cflow = fs->make<TH1D>("cflow","Cut flow for sync",10,0,10);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SingleTopFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
SingleTopFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
SingleTopFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
SingleTopFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
SingleTopFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SingleTopFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(SingleTopFilter);
