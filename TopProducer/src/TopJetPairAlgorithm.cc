#include "AnalysisCode/TopProducer/interface/TopJetPairAlgorithm.h"
#include <TMath.h>
#include "Math/GenVector/VectorUtil.h"

TopJetPairAlgorithm::TopJetPairAlgorithm(const edm::ParameterSet& cfg)
{
  debug_ = cfg.getUntrackedParameter<int>("debug", 0);
  nuComputation_ = cfg.getUntrackedParameter<int>("nuComputation", 1);
}

TopJetPairAlgorithm::~TopJetPairAlgorithm() 
{
}

TopJetPair TopJetPairAlgorithm::buildTopJetPair(const edm::Ptr<reco::Candidate>& leptonPtr, const edm::Ptr<pat::MET>& metPtr, const edm::Ptr<pat::Jet>& bjetPtr, const edm::Ptr<pat::Jet>& ljetPtr)
{
  TopJetPair topJetPair;

  computeTopJetPair(topJetPair, leptonPtr, metPtr, bjetPtr, ljetPtr);

  return topJetPair;
}

void TopJetPairAlgorithm::computeTopJetPair(TopJetPair& topJetPair,
					    const edm::Ptr<reco::Candidate>& leptonPtr, const edm::Ptr<pat::MET>& metPtr, const edm::Ptr<pat::Jet>& bjetPtr, const edm::Ptr<pat::Jet>& ljetPtr)
{
  double mW = 80.385;
  double mTW = compMt(leptonPtr->p4(), metPtr->px(), metPtr->py());
  double leptonPt = leptonPtr->pt();
  double costh = -2;
  reco::Candidate::LorentzVector p4nu = metPtr->p4(); // neutrino 4-vector
  reco::Candidate::LorentzVector p4top = reco::Candidate::LorentzVector(0,0,0,0); // top 4-vector
  reco::Candidate::LorentzVector p4ljetTopCM = reco::Candidate::LorentzVector(0,0,0,0); // boosted jet 4-vector
  reco::Candidate::LorentzVector p4leptonTopCM = reco::Candidate::LorentzVector(0,0,0,0); // boosted lepton 4-vector

  p4nu = compNuP4( leptonPtr->p4(),metPtr->p4() ); //fill neutrino 4-vector
    
  reco::Candidate::LorentzVector p4W = p4nu + leptonPtr->p4();
  //---------------------------reconstruct final observables--------------------

  double mWcomp = compM(leptonPtr->p4(), p4nu); //computed W mass consistency check
  p4top = p4nu + leptonPtr->p4() + bjetPtr->p4(); //reconstruct top candidate

  p4ljetTopCM = ROOT::Math::VectorUtil::boost(ljetPtr->p4(), p4top.BoostToCM());
  p4leptonTopCM = ROOT::Math::VectorUtil::boost(leptonPtr->p4(), p4top.BoostToCM());
  
  costh = ROOT::Math::VectorUtil::CosTheta( p4ljetTopCM, p4leptonTopCM);


  if ( debug_ ) {
    std::cout << "<TopJetPairAlgorithm::computeTopJetPair>:" << std::endl;
    std::cout << " lepton Pt = " << leptonPt << std::endl;
    std::cout << " mTW = " << mTW << std::endl;
    std::cout<<" p4(MET) = "<<metPtr->p4() <<std::endl;
    std::cout << " P4(nu) = " << p4nu <<std::endl;
    std::cout << " P4(top) = " << p4top <<std::endl;
    std::cout << " P4(boosted lepton) = " << p4leptonTopCM <<std::endl;
    std::cout << " P4(boosted jet) = " << p4ljetTopCM <<std::endl;
    std::cout << "cos theta = " << costh << std::endl;
    std::cout << " W mass computed = " << mWcomp <<", W mass (PDG) = "<< mW <<std::endl;
  }
  topJetPair.setp4nu(p4nu);
  topJetPair.setp4W(p4W);
  topJetPair.setcosth(costh);
  topJetPair.setp4top(p4top);
  topJetPair.setp4ljetTopCM(p4ljetTopCM);
  topJetPair.setp4leptonTopCM(p4leptonTopCM);

}
