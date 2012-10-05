// -*- C++ -*-
//
// Package:    TriggerFilter
// Class:      TriggerFilter
// 
/**\class TriggerFilter TriggerFilter.cc TripHto4lep/TriggerFilter/src/TriggerFilter.cc

 Description: Selects events based on trigger rules

 Implementation:
	Any number of Yes and No triggers can be specified. Only those which have prescale=1 will be used. If any No triggers are specified those work
	as veto triggers. If present the event will be discarded (to avoid overlap one PD's Yes list has to be the others No list).
 */
//
// Original Author:  
//         Created:  Mon Oct 25 15:51:47 EEST 2010
// $Id: TriggerFilter.cc,v 1.3 2011/11/23 17:32:25 mario Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

//
// class declaration
//

class TriggerFilter : public edm::EDFilter {
   public:
      explicit TriggerFilter(const edm::ParameterSet&);
      ~TriggerFilter();

   private:
      virtual void beginJob() ;
      virtual bool beginRun(edm::Run&, const edm::EventSetup&);
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
	edm::InputTag trigLabel;
	std::vector<std::string> yesTrig;
	std::vector<std::string> noTrig;
	std::vector<std::string> yesUsed;
	std::vector<std::string> noUsed;
	TH1D* eff;
	bool accept, debug, reloadTriggers;
};

//
// constants, enums and typedefs
//

enum { kAll, kYes, kNo, kPass };

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerFilter::TriggerFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
	trigLabel 	= iConfig.getParameter<edm::InputTag>("trigLabel");
	yesTrig		= iConfig.getParameter<std::vector<std::string> >("yesTrig");
	noTrig		= iConfig.getParameter<std::vector<std::string> >("noTrig");
	debug		= iConfig.getParameter<bool>("debug");	
	reloadTriggers	= true;
}


TriggerFilter::~TriggerFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TriggerFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;
	using namespace pat;
	
	eff->Fill(kAll);
	
	Handle<TriggerEvent> trig;
	iEvent.getByLabel(trigLabel,trig);
	
	if (reloadTriggers) {
 	 	yesUsed.clear();
  		noUsed.clear();
		
		if (debug) 
			for (unsigned int i=0; i<trig->paths()->size(); i++)
				cout << "Path: " << trig->paths()->at(i).name() << endl;
		
  		for (unsigned int j=0; j<trig->paths()->size(); j++) {
  		  for (unsigned int i=0; i<yesTrig.size(); i++) 
  		    if (trig->paths()->at(j).name().find(yesTrig.at(i)) != std::string::npos)
			yesUsed.push_back(trig->paths()->at(j).name());
		  for (unsigned int i=0; i<noTrig.size(); i++) 
  		    if (trig->paths()->at(j).name().find(noTrig.at(i)) != std::string::npos)
			noUsed.push_back(trig->paths()->at(j).name());
  		}
		reloadTriggers = false;
	}
	accept = false;

	if (debug) cout << "Processing Yes triggers" << endl;
	// Go over the Yes list and check if any of the triggers is unprescaled and fired
	for (unsigned int i = 0; i < yesUsed.size(); i++) {
		std::string t = yesUsed[i];
		if (debug) cout << "Path: " << t << " exists?: " << trig->path(t);
		if (trig->path(t)) {
			// Path exists, let's check if it fired and is unscaled
			if (trig->path(t)->wasAccept() && trig->path(t)->prescale() == 1 )
				accept=true;
			if (debug) cout << " accept: " << trig->path(t)->wasAccept() << " prescale: " << trig->path(t)->prescale();
		}
		if (debug) cout << endl;
	}
	
	if (!accept) return false;
	eff->Fill(kYes);

	if (debug) cout << "Processing No triggers" << endl;
	for (unsigned int i = 0; i < noUsed.size(); i++) {
		std::string t = noUsed[i];
		if (debug) cout << "Path: " << t << " exists?: " << trig->path(t);
		if (trig->path(t)) {
			// Path exists, let's check if it fired and is unscaled
			if (trig->path(t)->wasAccept() && trig->path(t)->prescale() == 1 )
				accept=false;
			if (debug) cout << " accept: " << trig->path(t)->wasAccept() << " prescale: " << trig->path(t)->prescale();
		}
		if (debug) cout << endl;
	}
	
	if (!accept) return false;
	eff->Fill(kNo);
	
	eff->Fill(kPass); // Final pass, usually equivalent to previous
	return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
TriggerFilter::beginJob()
{
	edm::Service<TFileService> fs;
	eff = fs->make<TH1D>("eff","Filter efficiency",10,0,10);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerFilter::endJob() {
}

// ---- method called per run -----
bool
TriggerFilter::beginRun(edm::Run &run, const edm::EventSetup &es)
{
  using namespace std;
  if (debug) cout << "Starting new run: " << run.id().run() << endl;
  reloadTriggers=true;
  return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerFilter);
