// -*- C++ -*-
//
// Package:    SmearedJetProducer
// Class:      SmearedJetProducer
// 
/**\class SmearedJetProducer SmearedJetProducer.cc AnalysisCode/SmearedJetProducer/src/SmearedJetProducer.cc

 Description: Add smearing information to PAT jets

 Implementation:
     The class takes as input pat::Jet collection and computes the smearing factors in a pre-given
     eta binning. It then adds the information back to the event in a new Jet collection
*/
//
// Original Author:  Mario Kadastik
//         Created:  Mon Oct  8 12:23:50 EEST 2012
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
#include "DataFormats/PatCandidates/interface/Jet.h"

//
// class declaration
//

class SmearedJetProducer : public edm::EDProducer {
   public:
      explicit SmearedJetProducer(const edm::ParameterSet&);
      ~SmearedJetProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      double getFactor(double);
      // ----------member data ---------------------------
      edm::InputTag inLabel;
      std::vector<double> etaBins, factors;
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
SmearedJetProducer::SmearedJetProducer(const edm::ParameterSet& iConfig)
{
   produces<std::vector<pat::Jet> >();

  inLabel = iConfig.getParameter<edm::InputTag>("inLabel");
  etaBins = iConfig.getParameter<std::vector<double> >("etaBins");
  factors = iConfig.getParameter<std::vector<double> >("factors");
}


SmearedJetProducer::~SmearedJetProducer()
{
}


//
// member functions
//

double SmearedJetProducer::getFactor(double eta) {
  // Make sure we're talking about positive only
  eta=fabs(eta);
  double f=0;
  for (unsigned int i=0; i<etaBins.size(); i++) 
    if (eta < etaBins[i]) return factors[i];
  return f;
}

// ------------ method called to produce the data  ------------
void
SmearedJetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace pat;

   Handle<JetCollection> jets;
   iEvent.getByLabel(inLabel,jets);

   JetCollection *outJets = new JetCollection();
   for (JetCollection::const_iterator j = jets->begin(); j != jets->end(); j++) {
     Jet *jet = new Jet(*j);
     double f = getFactor(jet->eta());
     double genPt = 0;
     double smearPt = 0;
     if (jet->genJet()) {
       genPt=jet->genJet()->pt();
     }
     smearPt = max(0., genPt + f * (jet->pt() - genPt) );
     jet->addUserFloat("smearPt",smearPt);
     outJets->push_back(*jet);
   }

   std::auto_ptr<JetCollection> out(outJets);
   iEvent.put(out);
}

// ------------ method called once each job just before starting event loop  ------------
void 
SmearedJetProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SmearedJetProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
SmearedJetProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SmearedJetProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
SmearedJetProducer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SmearedJetProducer::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SmearedJetProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SmearedJetProducer);