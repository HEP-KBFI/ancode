// -*- C++ -*-
//
// Package:    CosTheta
// Class:      CosTheta
// 
/**\class CosTheta CosTheta.cc AnalysisCode/CosTheta/src/CosTheta.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Mario Kadastik
//         Created:  Mon Oct 22 16:33:19 EEST 2012
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
#include "AnalysisCode/AnalysisDataFormats/interface/Neutrino.h"
#include "AnalysisCode/AnalysisDataFormats/interface/NeutrinoFwd.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "Math/GenVector/VectorUtil.h"
//
// class declaration
//

class CosTheta : public edm::EDAnalyzer {
   public:
      explicit CosTheta(const edm::ParameterSet&);
      ~CosTheta();

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
      edm::InputTag lepLab, nuLab, bLab, ljLab;
      bool debug;
      TH1D *costh, *topMass;
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
CosTheta::CosTheta(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  lepLab = iConfig.getParameter<edm::InputTag>("lepton");
  nuLab = iConfig.getParameter<edm::InputTag>("neutrino");
  bLab = iConfig.getParameter<edm::InputTag>("bjet");
  ljLab = iConfig.getParameter<edm::InputTag>("lightJet");
  debug = iConfig.getParameter<bool>("debug");
}


CosTheta::~CosTheta()
{
}


//
// member functions
//

// ------------ method called for each event  ------------
void
CosTheta::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace ROOT::Math;

   // Read in the collections
   Handle<reco::CandidateCollection> leps;
   iEvent.getByLabel(lepLab,leps);

   Handle<NeutrinoCollection> nus;
   iEvent.getByLabel(nuLab,nus);

   Handle<pat::JetCollection> bjets;
   iEvent.getByLabel(bLab,bjets);

   Handle<pat::JetCollection> ljets;
   iEvent.getByLabel(ljLab,ljets);

   reco::Candidate::LorentzVector top(0,0,0,0);
   top = leps->begin()->p4() + nus->begin()->P4Nu() + bjets->begin()->p4();

   costh->Fill(VectorUtil::CosTheta(VectorUtil::boost(leps->begin()->p4(),top.BoostToCM()),VectorUtil::boost(ljets->begin()->p4(),top.BoostToCM())));
   topMass->Fill(top.M());
}


// ------------ method called once each job just before starting event loop  ------------
void 
CosTheta::beginJob()
{
  edm::Service<TFileService> fs;
  costh = fs->make<TH1D>("costh","Cos(th*) of lepton and light-jet",200,-1,1);
  topMass = fs->make<TH1D>("topMass","Mass of top quark",300,0,300);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CosTheta::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
CosTheta::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
CosTheta::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
CosTheta::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
CosTheta::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CosTheta::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CosTheta);
