#include "AnalysisCode/TopProducer/interface/TopJetPairAlgorithm.h"
#include <TMath.h>
#include "Math/GenVector/VectorUtil.h"

TopJetPairAlgorithm::TopJetPairAlgorithm(const edm::ParameterSet& cfg)
{
  debug_ = cfg.getUntrackedParameter<int>("debug", 0);
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
  double metPt = metPtr->pt();
  double costh = -2;
  reco::Candidate::LorentzVector p4nu = metPtr->p4(); // neutrino 4-vector
  reco::Candidate::LorentzVector p4top = reco::Candidate::LorentzVector(0,0,0,0); // top 4-vector
  reco::Candidate::LorentzVector p4ljetTopCM = reco::Candidate::LorentzVector(0,0,0,0); // boosted jet 4-vector
  reco::Candidate::LorentzVector p4leptonTopCM = reco::Candidate::LorentzVector(0,0,0,0); // boosted lepton 4-vector

  //-------------Calculate z-component of the neutrino 4-vector--------  
  double PzNu = 0;
  double PzNu1 = 0;
  double PzNu2 = 0;
  double Lambda = mW*mW/2 + (leptonPtr->px()*metPtr->px() + leptonPtr->py()*metPtr->py());
  double D = square(Lambda)*square(leptonPtr->pz())/(square(square(leptonPtr->pt())) ) - (square(leptonPtr->energy())*square(metPtr->pt()) - square(Lambda))/square(leptonPtr->pt());

  if( D > 0 || D == 0 ){
    PzNu1 = Lambda*leptonPtr->pz()/square(leptonPtr->pt()) + TMath::Sqrt(D);
    PzNu2 = Lambda*leptonPtr->pz()/square(leptonPtr->pt()) - TMath::Sqrt(D);

    if( abs(PzNu1) < abs(PzNu2) )//choose the solution with smaller absolute value
      PzNu = PzNu1;
    else
      PzNu = PzNu2;
  }
  
  if( D < 0){
    if (debug_){
      std::cout << "Negative discriminant, rescaling W mass " << std::endl;
      std::cout << "mTW = "<< mTW <<std::endl;
    }
    mW = mTW; //rescale W mass to avoid imaginary solutions
    Lambda = mW*mW/2 + (leptonPtr->px()*metPtr->px() + leptonPtr->py()*metPtr->py());
    D = square(Lambda)*square(leptonPtr->pz())/(square(square(leptonPtr->pt())) ) - (square(leptonPtr->energy())*square(metPtr->pt()) - square(Lambda))/square(leptonPtr->pt()); //For check. should be 0
    PzNu = Lambda*leptonPtr->pz()/square(leptonPtr->pt());
    
    if(debug_)
      std::cout << "new D = "<<D<<std::endl;
  }

  //------------------------Fill neutrino 4-vector---------------------------------

  p4nu.SetPz(PzNu);
  p4nu.SetE( TMath::Sqrt(p4nu.Px()*p4nu.Px() + p4nu.Py()*p4nu.Py() + p4nu.Pz()*p4nu.Pz()) );
    
  //---------------------------reconstruct final observables--------------------

  double mWcomp = compM(leptonPtr->p4(), p4nu); //computed W mass consistency check
  p4top = p4nu + leptonPtr->p4() + bjetPtr->p4(); //reconstruct top candidate

  p4ljetTopCM = ROOT::Math::VectorUtil::boost(ljetPtr->p4(), p4top.BoostToCM());
  p4leptonTopCM = ROOT::Math::VectorUtil::boost(leptonPtr->p4(), p4top.BoostToCM());
  
  costh = ROOT::Math::VectorUtil::CosTheta( p4ljetTopCM, p4leptonTopCM);


  if ( debug_ ) {
    std::cout << "<TopJetPairAlgorithm::computeTopJetPair>:" << std::endl;
    std::cout << " lepton Pt = " << leptonPt << std::endl;
    std::cout << " MET = " << metPt << std::endl;
    std::cout << " mTW = " << mTW << std::endl;
    std::cout << " P4(nu) = " << p4nu <<std::endl;
    std::cout << " P4(top) = " << p4top <<std::endl;
    std::cout << " P4(boosted lepton) = " << p4leptonTopCM <<std::endl;
    std::cout << " P4(boosted jet) = " << p4ljetTopCM <<std::endl;
    std::cout << "cos theta = " << costh << std::endl;
    std::cout << " W mass computed = " << mWcomp <<std::endl;
  }
  topJetPair.setp4nu(p4nu);
  topJetPair.setmTW(mTW);
  topJetPair.setcosth(costh);
  topJetPair.setp4top(p4top);
  topJetPair.setp4ljetTopCM(p4ljetTopCM);
  topJetPair.setp4leptonTopCM(p4leptonTopCM);

}
