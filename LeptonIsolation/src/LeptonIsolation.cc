// -*- C++ -*-
//
// Package:    LeptonIsolation
// Class:      LeptonIsolation
// 
/**\class LeptonIsolation LeptonIsolation.cc AnalysisCode/LeptonIsolation/src/LeptonIsolation.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Mario Kadastik
//         Created:  Tue Sep 25 21:04:26 EEST 2012
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

//
// class declaration
//
template <typename T>
class LeptonIsolation : public edm::EDProducer {
   public:
      explicit LeptonIsolation(const edm::ParameterSet&);
      ~LeptonIsolation();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      int getEtaBin(double);

      // ----------member data ---------------------------
     edm::InputTag leptonSource;
     edm::InputTag rhoSource;
     const static double elEffArea[7];
     const static double muEffArea[6];
     bool debug;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//
// Effective areas with consequtive |eta| bins with boundaries at: 1, 1.5, 2, 2.2, 2.3, 2.4 and >2.4
template <typename T>
const double LeptonIsolation<T>::elEffArea[] = { 0.19, 0.25, 0.12, 0.21, 0.27, 0.44, 0.52};

template <typename T>
const double LeptonIsolation<T>::muEffArea[] = { 0.674, 0.565, 0.442, 0.515, 0.821, 0.66 };

//
// constructors and destructor
//
template <typename T>
LeptonIsolation<T>::LeptonIsolation(const edm::ParameterSet& iConfig)
{
   //register your products
   produces<std::vector<T> >();

   //now do what ever other initialization is needed
   leptonSource = iConfig.getParameter<edm::InputTag>("src");
   rhoSource = iConfig.getParameter<edm::InputTag>("rho");
   debug = iConfig.getUntrackedParameter<bool>("debug",false);

}


template <typename T>
LeptonIsolation<T>::~LeptonIsolation()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

template <typename T>
int LeptonIsolation<T>::getEtaBin(double eta) {
  if (eta < 1.0) return 0;
  if (eta < 1.5) return 1;
  if (eta < 2.0) return 2;
  if (eta < 2.2) return 3;
  if (eta < 2.3) return 4;
  if (eta < 2.4) return 5;
  return 6;
}

// ------------ method called to produce the data  ------------
template <typename T>
void
LeptonIsolation<T>::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace pat;
   using namespace std;

   // Read the lepton collection and rho value from event
   Handle<vector<T> > lep;
   iEvent.getByLabel(leptonSource,lep);

   Handle<double> rho;
   iEvent.getByLabel(rhoSource,rho);

   // Prepare output collection that will contain the leptons with updated isolation
   std::auto_ptr<std::vector<T> > out(new std::vector<T>(*lep));

   for (auto& lepton : *out) {
     double eta = fabs(lepton.eta());
     int pid = abs(lepton.pdgId());
     double ea = 0;
     int bin = 0;
     if (pid == 11) {
       eta = fabs(lepton.superCluster()->eta());
       bin = getEtaBin(eta);
       ea = elEffArea[bin];
     };
     if (pid == 13) {
       bin = getEtaBin(eta);
       ea = muEffArea[bin];
     };
     double isoRho = ( lepton.chargedHadronIso() + max(0., lepton.neutralHadronIso() + lepton.photonIso() - ea*(*rho) ) ) / lepton.pt();
     double isoDBeta = ( lepton.chargedHadronIso() + max(0., lepton.neutralHadronIso() + lepton.photonIso() - 0.5*lepton.puChargedHadronIso()) ) / lepton.pt();
     if (debug) cout << "Iso prod: pid=" << pid << " eta=" << eta << " bin=" << bin << " ea=" << ea << " isoRho=" << isoRho << " isoDBeta=" << isoDBeta << endl;
     lepton.addUserFloat("deltaBetaCorrRelIso", isoDBeta);
     lepton.addUserFloat("rhoCorrRelIso", isoRho);
   }

   // Put the updated objects back into event content
   iEvent.put(out);
}

// ------------ method called once each job just before starting event loop  ------------
template <typename T>
void 
LeptonIsolation<T>::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
template <typename T>
void 
LeptonIsolation<T>::endJob() {
}

// ------------ method called when starting to processes a run  ------------
template <typename T>
void 
LeptonIsolation<T>::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
template <typename T>
void 
LeptonIsolation<T>::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
template <typename T>
void 
LeptonIsolation<T>::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
template <typename T>
void 
LeptonIsolation<T>::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
template <typename T>
void
LeptonIsolation<T>::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
typedef LeptonIsolation<pat::Muon> MuonIsolationProducer;
typedef LeptonIsolation<pat::Electron> ElectronIsolationProducer;
DEFINE_FWK_MODULE(MuonIsolationProducer);
DEFINE_FWK_MODULE(ElectronIsolationProducer);
