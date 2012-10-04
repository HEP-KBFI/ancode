// -*- C++ -*-
//
// Package:    FilterGenEvents
// Class:      FilterGenEvents
// 
/**\class FilterGenEvents FilterGenEvents.cc AnalysisCode/FilterGenEvents/src/FilterGenEvents.cc

 Description: The class filters for particular decays

 Implementation:
     The EDFilter looks through the genParticle hierarchy and looks for particular decays allowing to filter for specific ones
*/
//
// Original Author:  Mario Kadastik
//         Created:  Tue Oct  2 16:28:13 EEST 2012
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
// Particle definitions
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
//
// class declaration
//

class FilterGenEvents : public edm::EDFilter {
   public:
      explicit FilterGenEvents(const edm::ParameterSet&);
      ~FilterGenEvents();

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
      edm::InputTag genLabel;
      bool zHadronic, zLeptonic, wHadronic, wLeptonic, hzHadronic, hzLeptonic;
      bool zHadronicOK, zLeptonicOK, wHadronicOK, wLeptonicOK, hzHadronicOK, hzLeptonicOK;
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
FilterGenEvents::FilterGenEvents(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   genLabel = iConfig.getParameter<edm::InputTag>("genLabel");
   hzHadronic = iConfig.getParameter<bool>("hzHadronic");
   hzLeptonic = iConfig.getParameter<bool>("hzLeptonic");
   zHadronic = iConfig.getParameter<bool>("zHadronic");
   zLeptonic = iConfig.getParameter<bool>("zLeptonic");
   wHadronic = iConfig.getParameter<bool>("wHadronic");
   wLeptonic = iConfig.getParameter<bool>("wLeptonic");
}


FilterGenEvents::~FilterGenEvents()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FilterGenEvents::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   // First reset the discovery states to false
   zHadronicOK = false;
   zLeptonicOK = false;
   hzHadronicOK = false;
   hzLeptonicOK = false;
   wHadronicOK = false;
   wLeptonicOK = false;

   Handle<GenParticleCollection> pIn;
   iEvent.getByLabel(genLabel,pIn);

   for (GenParticleCollection::const_iterator p = pIn->begin(); p != pIn->end(); p++) {
     int pid = abs(p->pdgId());
     if (pid == 23 && p->status() == 3) {
       // It's a Z, let's see if it's hadronic or leptonic decay
       int dpid = -1;
       if (p->daughter(0)) dpid=abs(p->daughter(0)->pdgId());
       int mpid = abs(p->mother()->pdgId());
       cout << "Z0: dpid: " << dpid << " mpid:" << mpid << endl;
       if (mpid == 25) {
         if (dpid < 6) hzHadronicOK = true;
         else hzLeptonicOK = true;
       } else {
         if (dpid < 6) zHadronicOK = true;
         else zLeptonicOK = true;
       }
     }
     if (pid == 24 && p->status() == 3) {
       cout << "W: dpid: " << p->daughter(0)->pdgId() << endl;
       int dpid = abs(p->daughter(0)->pdgId());
       if (dpid < 6) wHadronicOK = true;
       else wLeptonicOK = true;
     }
   }

   cout << "Final: zHad=" << zHadronicOK << " zLep=" << zLeptonic;
   cout << " hzHad=" << hzHadronic << " hzLep=" << hzLeptonic;
   cout << " wHad=" << wHadronic << " wLep=" << wLeptonic << endl;

   // Now check what was asked and if we satisfied it
   if ( 
       ( zHadronic && zHadronicOK ) ||
       ( zLeptonic && zLeptonicOK ) ||
       ( hzHadronic && hzHadronicOK ) ||
       ( hzLeptonic && hzLeptonicOK ) ||
       ( wHadronic && wHadronicOK ) ||
       ( wLeptonic && wLeptonicOK )
      ) return true;

   // If we got this far we didn't find anything...
   return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
FilterGenEvents::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FilterGenEvents::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
FilterGenEvents::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
FilterGenEvents::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
FilterGenEvents::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
FilterGenEvents::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FilterGenEvents::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(FilterGenEvents);
