// -*- C++ -*-
//
// Package:    SingleTopOptimization
// Class:      SingleTopOptimization
// 
/**\class SingleTopOptimization SingleTopOptimization.cc AnalysisCode/SingleTopOptimization/src/SingleTopOptimization.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Liis Rebane
//         Created:  Sat Oct 27 16:58:56 EEST 2012
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

#include "AnalysisCode/AnalysisDataFormats/interface/TopJetPair.h"
#include "AnalysisCode/AnalysisDataFormats/interface/TopJetPairFwd.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
#include <TMath.h>


//
// class declaration
//

class SingleTopOptimization : public edm::EDAnalyzer {
   public:
      explicit SingleTopOptimization(const edm::ParameterSet&);
      ~SingleTopOptimization();

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
  TH1D *costh, *topMass, *Wmass, *el_g_MVA, *el_g_MVA_EB, *el_g_MVA_EE, *nuEta;
  TH2D *mvaGoodElvsVetoEl;
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
SingleTopOptimization::SingleTopOptimization(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


SingleTopOptimization::~SingleTopOptimization()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
SingleTopOptimization::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   // Good leptons
   Handle<reco::CandidateCollection> leps;
   iEvent.getByLabel("leptons","goodLeptons",leps);
   
   // Top-jet pair objects
   Handle<TopJetPairCollection> topjets;
   iEvent.getByLabel("topJetPairs",topjets);

   // pat electrons
   Handle<pat::ElectronCollection> gEl;
   iEvent.getByLabel("goodElectrons",gEl);

   Handle<pat::ElectronCollection> vEl;
   iEvent.getByLabel("vetoElectrons",vEl);

   //   std::cout<<vEl->size()<<" veto electrons in the event"<<endl;
   //   std::cout<<gEl->size()<<" good electrons in the event"<<endl;
   //   std::cout<<topjets->size()<<" top jet pairs in the event"<<endl;


   //--------------Fill Histograms for good electrons---------------
   if( gEl->size() > 0 ){
     pat::ElectronCollection::const_iterator el = gEl->begin();
     el_g_MVA->Fill(  el->electronID("mvaTrigV0") );
     if( el->isEB() )
       el_g_MVA_EB->Fill( el->electronID("mvaTrigV0") );
     if(el->isEE() )
       el_g_MVA_EE->Fill( el->electronID("mvaTrigV0") );
   }
   


   
   /*  int numVel = 0; //number of veto electrons in the event

   //----for investigating electron mva of veto electrons comment out the veto electron filter in stfilt--------
   if( gEl->size() > 0 ){
     pat::ElectronCollection::const_iterator el = gEl->begin();
     for( int k = 0; k != 19; k++ ){
       if( el->electronID("mvaTrigV0") > 0.1 + k*0.05 ){
         mvaOptGoodEl->Fill(k);
	 for( int j = 0; j != 19; j++ ){
	   numVel = 0;
	   for( pat::ElectronCollection::const_iterator vel = vEl->begin(); vel != vEl->end(); vel++ ){
	     if( vel->electronID("mvaTrigV0") > 0.1 + k*0.05 )
	       numVel++;
	   }
	   if(numVel < 2){ // if electron veto cut passes (commented out in stfilt)
	     mvaGoodElvsVetoEl->Fill(k,j);
	     mvaOptGoodEl->Fill(k);
	     if( k == 0)
	       el_g_MVA->Fill(el->electronID("mvaTrigV0") );
	   }
	 }
       }
     }
   }
	     
   */   
      
         
   //-------------------fill final histograms-----------------------
   if(topjets->size()>0){
     nuEta->Fill(topjets->begin()->p4nu().Eta());
     costh->Fill( topjets->begin()->costh() );
     topMass->Fill(TMath::Sqrt( topjets->begin()->p4top().M2() ) );
     Wmass->Fill(TMath::Sqrt( topjets->begin()->p4W().M2() ) );
   }

}


// ------------ method called once each job just before starting event loop  ------------
void 
SingleTopOptimization::beginJob()
{
  edm::Service<TFileService> fs;
  nuEta = fs->make<TH1D>("nuEta","nu eta",100,-5,5);
  costh = fs->make<TH1D>("costh","Cos(theta*) of lepton and light jet",100,-1,1);
  topMass = fs->make<TH1D>("topMass","Mass of top quark",100,0,500);
  Wmass = fs->make<TH1D>("Wmass","Mass of recontructed W",240,50,110);
  el_g_MVA = fs->make<TH1D>("el_g_MVA","good electron MVA",364,0.1,1.01);
  el_g_MVA_EB = fs->make<TH1D>("el_g_MVA_EB","good electron MVA (barrel)",364,0.1,1.01);
  el_g_MVA_EE = fs->make<TH1D>("el_g_MVA_EE","good electron MVA (endcap)",364,0.1,1.01);

  mvaGoodElvsVetoEl = fs->make<TH2D>("mvaGoodElvsVetoEl","Good electron vs Veto electron mva",19,0,19,19,0,19);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SingleTopOptimization::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
SingleTopOptimization::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SingleTopOptimization::endRun(edm::Run const&, edm::EventSetup const&)
{
}
 
// ------------ method called when starting to processes a luminosity block  ------------
void 
SingleTopOptimization::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SingleTopOptimization::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SingleTopOptimization::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SingleTopOptimization);
