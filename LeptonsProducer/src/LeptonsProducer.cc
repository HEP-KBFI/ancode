// -*- C++ -*-
//
// Package:    LeptonsProducer
// Class:      LeptonsProducer
// 
/**\class LeptonsProducer LeptonsProducer.cc AnalysisCode/LeptonsProducer/src/LeptonsProducer.cc

 Description: Produces the final good and veto collections of leptons

 Implementation:
  The producer reads in the goodMuons and goodElectrons performing some final cuts and adding them to the goodLeptons collection, it then
  runs over the vetoMu and vetoEl collections and writes them out as vetoLeptons collection having removed the ones in the good collection
*/
//
// Original Author:  Mario Kadastik
//         Created:  Tue Oct 16 17:35:28 EEST 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//
// class declaration
//

class LeptonsProducer : public edm::EDProducer {
   public:
      explicit LeptonsProducer(const edm::ParameterSet&);
      ~LeptonsProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      edm::InputTag goodMuLab, vetoMuLab, goodElLab, vetoElLab, pvLab;
      double goodElMvaEB, goodElMvaEE, goodElRelIso_, goodElPtMax_;
      bool debug;
      reco::Vertex PV;
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
LeptonsProducer::LeptonsProducer(const edm::ParameterSet& iConfig)
{
   produces<reco::CandidateCollection>("goodLeptons");
   produces<reco::CandidateCollection>("vetoLeptons");

   //now do what ever other initialization is needed
   goodMuLab  = iConfig.getParameter<edm::InputTag>("goodMuLab");
   vetoMuLab  = iConfig.getParameter<edm::InputTag>("vetoMuLab");
   goodElLab  = iConfig.getParameter<edm::InputTag>("goodElLab");
   goodElMvaEB  = iConfig.getParameter<double>("goodElMvaEB");
   goodElMvaEE  = iConfig.getParameter<double>("goodElMvaEE");
   goodElRelIso_ = iConfig.getParameter<double>("goodElRelIso");
   goodElPtMax_ = iConfig.getParameter<double>("goodElPtMax");
   vetoElLab  = iConfig.getParameter<edm::InputTag>("vetoElLab");
   pvLab      = iConfig.getParameter<edm::InputTag>("pvLab");

   // Debug information
   debug      = iConfig.getParameter<bool>("debug");
}


LeptonsProducer::~LeptonsProducer()
{
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
LeptonsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace pat;
   using namespace std;

   // Prepare the auto-pointers that will store the output collection back to event
   auto_ptr<reco::CandidateCollection> selLeps(new reco::CandidateCollection());
   auto_ptr<reco::CandidateCollection> vetoLeps(new reco::CandidateCollection());
 
   // Get the primary vertex

   Handle<reco::VertexCollection> pvs;
   iEvent.getByLabel(pvLab,pvs);
   PV=*(pvs->begin());
        
   // Read in the collections
   Handle<MuonCollection> gMu;
   iEvent.getByLabel(goodMuLab,gMu);

   Handle<MuonCollection> vMu;
   iEvent.getByLabel(vetoMuLab,vMu);

   Handle<ElectronCollection> gEl;
   iEvent.getByLabel(goodElLab,gEl);

   Handle<ElectronCollection> vEl;
   iEvent.getByLabel(vetoElLab,vEl);

   // Loop over good muon collection and do the final selections
   for (MuonCollection::const_iterator mu = gMu->begin(); mu != gMu->end(); mu++) {
     if ( fabs(mu->vertex().z() - PV.position().z()) < 0.5 ) {
       selLeps->push_back(*mu);
       if (debug) cout << "mu: pt=" << mu->pt() << " eta=" << mu->eta() << " phi=" << mu->phi() << " iso=" << mu->userFloat("rhoCorrRelIso") << " tk: " << mu->globalTrack()->hitPattern().numberOfValidMuonHits() << endl;
     }
   }

   // Loop over veto muons and compare if the lepton is different from the one in goodMuons
   for (MuonCollection::const_iterator mu = vMu->begin(); mu != vMu->end(); mu++) {
     bool found = false;
     if (debug) cout << "vmu: pt=" << mu->pt() << " eta=" << mu->eta() << " phi=" << mu->phi();
     for (reco::CandidateCollection::const_iterator c = selLeps->begin(); c != selLeps->end(); c++) {
       if (reco::deltaR(mu->p4(),c->p4()) < 0.1) found = true;
     }
     if (debug) cout << " found=" << found << endl;
     if (!found)
       vetoLeps->push_back(*mu);
   }


   // Repeat for good electrons
   for (ElectronCollection::const_iterator el = gEl->begin(); el != gEl->end(); el++) {
     // Here we could do some selection
     if( ( el->pt() < goodElPtMax_) && ( ( el->isEB() && el->electronID("mvaTrigV0") > goodElMvaEB ) || ( el->isEE() && el->electronID("mvaTrigV0") > goodElMvaEE ) ) && el->userFloat("rhoCorrRelIso") < goodElRelIso_ ) //tighten cut on electron mva and relIso
       selLeps->push_back(*el);

     if (debug) cout << "el: pt=" << el->pt() << " eta=" << el->eta() << " phi=" << el->phi() << endl;
   }

   // Now filter the veto electron collection for anything already found and declared good
   for (ElectronCollection::const_iterator el = vEl->begin(); el != vEl->end(); el++) {
     bool found = false;
     if (debug) cout << "vel: pt=" << el->pt() << " eta=" << el->eta() << " phi=" << el->phi();
     for (reco::CandidateCollection::const_iterator c = selLeps->begin(); c != selLeps->end(); c++)
       if (reco::deltaR(el->p4(),c->p4()) < 0.1) found = true;
     if (debug) cout << " found=" << found << endl;
     if ( !found && el->userFloat("rhoCorrRelIso") < 0.15 ) //tighten cut on rel Iso
       vetoLeps->push_back(*el);
   }

   if (debug) cout << "Total selected leptons: " << selLeps->size() << " total veto leptons: " << vetoLeps->size() << endl;

   // Write the collections to output
   iEvent.put(selLeps,"goodLeptons");
   iEvent.put(vetoLeps,"vetoLeptons");
}

// ------------ method called once each job just before starting event loop  ------------
void 
LeptonsProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LeptonsProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
LeptonsProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
LeptonsProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
LeptonsProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
LeptonsProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
LeptonsProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(LeptonsProducer);
