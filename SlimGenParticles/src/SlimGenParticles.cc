// -*- C++ -*-
//
// Package:    SlimGenParticles
// Class:      SlimGenParticles
// 
/**\class SlimGenParticles SlimGenParticles.cc AnalysisCode/SlimGenParticles/src/SlimGenParticles.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Mario Kadastik
//         Created:  Thu Sep 27 15:35:27 EEST 2012
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

// Particle definitions
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

//
// class declaration
//

class SlimGenParticles : public edm::EDProducer {
   public:
      explicit SlimGenParticles(const edm::ParameterSet&);
      ~SlimGenParticles();

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
      edm::InputTag src;
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
SlimGenParticles::SlimGenParticles(const edm::ParameterSet& iConfig)
{
   //register your products
   produces<std::vector<reco::GenParticle> >();

   //now do what ever other initialization is needed
   src = iConfig.getParameter<edm::InputTag>("src");  
}


SlimGenParticles::~SlimGenParticles()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
SlimGenParticles::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;
   using namespace std;

   //Read data from event
   Handle<GenParticleCollection> gen;
   iEvent.getByLabel(src,gen);

   // Loop over gen particles and keep only those who have an interesting mother or status == 3
   GenParticleCollection *outParts = new GenParticleCollection();
   for (GenParticleCollection::const_iterator part = gen->begin(); part != gen->end(); part++) {
     int mother = 0;
     if (part->mother()) mother = abs(part->mother()->pdgId());
     if (mother == 6 || mother == 23 || mother == 24 || mother == 25 || mother == 15 || part->status()==3)
       outParts->push_back(*part);
   }
   cout << "Output collection size: " << outParts->size() << endl;

   std::auto_ptr<GenParticleCollection> out(outParts);
   iEvent.put(out);
 
}

// ------------ method called once each job just before starting event loop  ------------
void 
SlimGenParticles::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SlimGenParticles::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
SlimGenParticles::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SlimGenParticles::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
SlimGenParticles::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SlimGenParticles::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SlimGenParticles::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SlimGenParticles);
