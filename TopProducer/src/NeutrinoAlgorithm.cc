#include "AnalysisCode/TopProducer/interface/NeutrinoAlgorithm.h"
#include <TMath.h>

NeutrinoAlgorithm::NeutrinoAlgorithm(const edm::ParameterSet& cfg)
{
  verbosity_ = cfg.getUntrackedParameter<int>("verbosity", 0);
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
  double mW = 80.385;
  double mTW = compMt(leptonPtr->p4(), metPtr->px(), metPtr->py());
  double leptonPt = leptonPtr->pt();
  double metPt = metPtr->pt();
  reco::Candidate::LorentzVector P4Nu = metPtr->p4();


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
    if (verbosity_){
      std::cout << "Negative discriminant, rescaling W mass " << std::endl;
      std::cout << "mTW = "<< mTW <<std::endl;
    }
    mW = mTW; //rescale W mass to avoid imaginary solutions
    Lambda = mW*mW/2 + (leptonPtr->px()*metPtr->px() + leptonPtr->py()*metPtr->py());
    D = square(Lambda)*square(leptonPtr->pz())/(square(square(leptonPtr->pt())) ) - (square(leptonPtr->energy())*square(metPtr->pt()) - square(Lambda))/square(leptonPtr->pt()); //For check. should be 0
    PzNu = Lambda*leptonPtr->pz()/square(leptonPtr->pt());
    
    if(verbosity_)
      std::cout << "new D = "<<D<<std::endl;
  }

  //------------------------Fill neutrino 4-vector----------------------------
  P4Nu.SetPz(PzNu);
  P4Nu.SetE( TMath::Sqrt(P4Nu.Px()*P4Nu.Px() + P4Nu.Py()*P4Nu.Py() + P4Nu.Pz()*P4Nu.Pz()) );
  
  double mWcomp = compM(leptonPtr->p4(), P4Nu); //computed W mass consistency check
  
  //---------------------------------------------------------------------  
  if ( verbosity_ ) {
    std::cout << "<NeutrinoAlgorithm::computeNeutrino>:" << std::endl;
    std::cout << " lepton Pt = " << leptonPt << std::endl;
    std::cout << " MET = " << metPt << std::endl;
    std::cout << " mTW = " << mTW << std::endl;
    std::cout << " P4(nu) = " << P4Nu <<std::endl;
    std::cout << " W mass computed = " << mWcomp <<std::endl;
  }
  neutrino.setP4Nu(P4Nu);
}
