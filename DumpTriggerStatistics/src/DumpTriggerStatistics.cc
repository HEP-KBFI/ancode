// -*- C++ -*-
//
// Package:    DumpTriggerStatistics
// Class:      DumpTriggerStatistics
// 
/**\class DumpTriggerStatistics DumpTriggerStatistics.cc AnalysisCode/DumpTriggerStatistics/src/DumpTriggerStatistics.cc

 Description: Dump strings of trigger paths that fired

 Implementation:
    runs over all trigger paths and dumps the ones that fired
*/
//
// Original Author:  Mario Kadastik
//         Created:  Tue Oct  2 15:40:18 EEST 2012
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
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

//
// class declaration
//

class DumpTriggerStatistics : public edm::EDAnalyzer {
   public:
      explicit DumpTriggerStatistics(const edm::ParameterSet&);
      ~DumpTriggerStatistics();

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
      edm::InputTag trigLabel;
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
DumpTriggerStatistics::DumpTriggerStatistics(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   trigLabel = iConfig.getParameter<edm::InputTag>("trigLabel");
}


DumpTriggerStatistics::~DumpTriggerStatistics()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DumpTriggerStatistics::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace pat;
   using namespace std;

   Handle<TriggerEvent> trig;
   iEvent.getByLabel(trigLabel,trig);

   for (unsigned int i=0; i<trig->paths()->size(); i++) {
     if (trig->paths()->at(i).wasAccept() && trig->paths()->at(i).prescale() == 1) 
       cout << "Trig: " << trig->paths()->at(i).name() << endl;
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
DumpTriggerStatistics::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DumpTriggerStatistics::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
DumpTriggerStatistics::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
DumpTriggerStatistics::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
DumpTriggerStatistics::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
DumpTriggerStatistics::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DumpTriggerStatistics::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DumpTriggerStatistics);
