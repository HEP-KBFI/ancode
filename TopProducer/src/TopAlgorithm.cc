#include "AnalysisCode/TopProducer/interface/TopAlgorithm.h"
#include <TMath.h>

TopAlgorithm::TopAlgorithm(const edm::ParameterSet& cfg)
{
  debug_ = cfg.getUntrackedParameter<int>("debug", 0);
}

TopAlgorithm::~TopAlgorithm() 
{
}

Top TopAlgorithm::buildTop(const edm::Ptr<reco::Candidate>& leptonPtr, const edm::Ptr<pat::MET>& metPtr, const edm::Ptr<pat::Jet>& bjetPtr)
{
  Top top;

  computeTop(top, leptonPtr, metPtr, bjetPtr);

  return top;
}

void TopAlgorithm::computeTop(Top& top,
			      const edm::Ptr<reco::Candidate>& leptonPtr, const edm::Ptr<pat::MET>& metPtr, const edm::Ptr<pat::Jet>& bjetPtr)
{
  double mW = 80.385;
  double mTW = compMt(leptonPtr->p4(), metPtr->px(), metPtr->py());
  double leptonPt = leptonPtr->pt();
  double metPt = metPtr->pt();
  reco::Candidate::LorentzVector P4Nu = metPtr->p4(); // neutrino 4-vector
  reco::Candidate::LorentzVector p4 = reco::Candidate::LorentzVector(0,0,0,0); // top 4-vector

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

  //------------------------Fill neutrino 4-vector----------------------------
  P4Nu.SetPz(PzNu);
  P4Nu.SetE( TMath::Sqrt(P4Nu.Px()*P4Nu.Px() + P4Nu.Py()*P4Nu.Py() + P4Nu.Pz()*P4Nu.Pz()) );
  
  double mWcomp = compM(leptonPtr->p4(), P4Nu); //computed W mass consistency check
  
  //------------------------Reconstruct top 4-vector------------------------  
  
  p4 = P4Nu + leptonPtr->p4() + bjetPtr->p4();

  if ( debug_ ) {
    std::cout << "<NeutrinoAlgorithm::computeNeutrino>:" << std::endl;
    std::cout << " lepton Pt = " << leptonPt << std::endl;
    std::cout << " MET = " << metPt << std::endl;
    std::cout << " mTW = " << mTW << std::endl;
    std::cout << " P4(nu) = " << P4Nu <<std::endl;
    std::cout << " P4(top) = " << p4 <<std::endl;
    std::cout << " W mass computed = " << mWcomp <<std::endl;
  }
  top.setP4Nu(P4Nu);
  top.setmTW(mTW);
  top.setp4(p4);
}
