// -*- C++ -*-
//
// Package:    InterestingEvents
// Class:      InterestingEvents
// 
/**\class InterestingEvents InterestingEvents.cc KBFIAnalysis/InterestingEvents/src/InterestingEvents.cc

 Description: This filter attempts to look at AOD level objects already available on wether there are interesting events to speed up
              which events are processed through PAT etc. 

 Implementation:
     Parse through electron, muon and possibly jet collections to see if it's an event worthy of writing out
*/
//
// Original Author:  Mario Kadastik
//         Created:  Tue Sep 25 13:19:30 EEST 2012
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
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/JetReco/interface/PFJet.h"

//
// class declaration
//

class InterestingEvents : public edm::EDFilter {
   public:
      explicit InterestingEvents(const edm::ParameterSet&);
      ~InterestingEvents();

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
      bool debug, isPassed;
      double muPt, elPt, jetPt;
      double muEta, elEta, jetEta;
      int minMu, minEl, minJet, minLep;
      int nMu, nEl, nJet;

      edm::InputTag muLabel, elLabel, jetLabel;
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
InterestingEvents::InterestingEvents(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   debug = iConfig.getUntrackedParameter<bool>("debug",false);

   // Minimum required object counts that satisfy other conditions
   minMu = iConfig.getUntrackedParameter<int>("minMuons",0);
   minEl = iConfig.getUntrackedParameter<int>("minElectrons",0);
   minLep = iConfig.getUntrackedParameter<int>("minLeptons",0);
   minJet = iConfig.getUntrackedParameter<int>("minJets",0);

   // Kinematic requirements
   muPt = iConfig.getUntrackedParameter<double>("muPt",0.);
   elPt = iConfig.getUntrackedParameter<double>("elPt",0.);
   jetPt = iConfig.getUntrackedParameter<double>("jetPt",0.);
   muEta = iConfig.getUntrackedParameter<double>("muEta",5.);
   elEta = iConfig.getUntrackedParameter<double>("elEta",5.);
   jetEta = iConfig.getUntrackedParameter<double>("jetEta",5.);

   // object lables as well
   muLabel = iConfig.getUntrackedParameter<edm::InputTag>("muLabel",edm::InputTag("muons"));
   elLabel = iConfig.getUntrackedParameter<edm::InputTag>("elLabel",edm::InputTag("gsfElectrons"));
   jetLabel = iConfig.getUntrackedParameter<edm::InputTag>("jetLabel",edm::InputTag("ak5PFJets"));
}


InterestingEvents::~InterestingEvents()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
InterestingEvents::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;
   using namespace std;
   
   // Reset variables at each event start to not carry over old information
   isPassed = false;
   nMu = 0;
   nEl = 0;
   nJet = 0;

   // Let's start with muons
   Handle<vector<Muon> > muIn;
   iEvent.getByLabel(muLabel,muIn);

   for (vector<Muon>::const_iterator it = muIn->begin(); it != muIn->end(); it++) {
     if (debug && it->pt() > muPt) cout << "Muon: q=" << it->charge() << " pt=" << it->pt() << " eta=" << it->eta() << endl;
     if (it->pt() > muPt && fabs(it->eta()) < muEta) nMu++;
   }
  
   // Next it's electrons
   Handle<vector<GsfElectron> > elIn;
   iEvent.getByLabel(elLabel,elIn);

   for (vector<GsfElectron>::const_iterator it = elIn->begin(); it != elIn->end(); it++) {
      if (debug && it->pt() > elPt) cout << "Electron: q=" << it->charge() << " pt=" << it->pt() << " eta=" << it->eta() << endl;
      if (it->pt() > elPt && fabs(it->eta()) < elEta) nEl++;
   }
   
   // And finally jets
   Handle<vector<PFJet> > jetIn;
   iEvent.getByLabel(jetLabel,jetIn);

   for (vector<PFJet>::const_iterator it = jetIn->begin(); it != jetIn->end(); it++) {
      if (debug && it->pt() > jetPt) cout << "Jet: q=" << it->charge() << " pt=" << it->pt() << " eta=" << it->eta() << endl;
      if (it->pt() > jetPt && fabs(it->eta()) < jetEta) nJet++;
   }
   
   if (nMu >= minMu && nEl >= minEl && nMu+nEl >= minLep && nJet >= minJet) isPassed = true;
   if (debug) cout << "Event decision: " << isPassed << " nmu=" << nMu << " nel=" << nEl << " njet=" << nJet << endl;
   return isPassed;
}

// ------------ method called once each job just before starting event loop  ------------
void 
InterestingEvents::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
InterestingEvents::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
InterestingEvents::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
InterestingEvents::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
InterestingEvents::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
InterestingEvents::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
InterestingEvents::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(InterestingEvents);
