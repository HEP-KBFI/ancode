#include "AnalysisCode/TopProducer/interface/NeutrinoAlgorithm.h"
#include <TMath.h>

NeutrinoAlgorithm::NeutrinoAlgorithm(const edm::ParameterSet& cfg)
{
  debug_ = cfg.getUntrackedParameter<int>("debug", 0);
  nuComputation_ = cfg.getUntrackedParameter<int>("nuComputation", 1);
}

NeutrinoAlgorithm::~NeutrinoAlgorithm() 
{
  //--- nothing to be done HtRatio...
}

Neutrino NeutrinoAlgorithm::buildNeutrino(const edm::Ptr<reco::Candidate>& leptonPtr, const edm::Ptr<pat::MET>& metPtr)
{
  Neutrino neutrino;

  computeNeutrino(neutrino, leptonPtr, metPtr);

  return neutrino;
}

void NeutrinoAlgorithm::computeNeutrino(Neutrino& neutrino,
					const edm::Ptr<reco::Candidate>& leptonPtr, const edm::Ptr<pat::MET>& metPtr)
{
  double mTW = compMt(leptonPtr->p4(), metPtr->px(), metPtr->py());
  double leptonPt = leptonPtr->pt();

  reco::Candidate::LorentzVector p4nu = metPtr->p4(); // neutrino 4-vector

  p4nu = compNuP4( leptonPtr->p4(),metPtr->p4() ); //fill neutrino 4-vector
    
  //---------------------------reconstruct final observables--------------------


  if ( debug_ ) {
    std::cout << "<TopJetPairAlgorithm::computeTopJetPair>:" << std::endl;
    std::cout << " lepton Pt = " << leptonPt << std::endl;
    std::cout << " mTW = " << mTW << std::endl;
    std::cout<<" p4(MET) = "<<metPtr->p4() <<std::endl;
    std::cout << " P4(nu) = " << p4nu <<std::endl;
  }

  neutrino.setP4Nu(p4nu);
  neutrino.setmTW(mTW);
}
