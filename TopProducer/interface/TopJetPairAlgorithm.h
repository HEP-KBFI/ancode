#ifndef AnalysisCode_TopProducer_TopJetPairAlgorithm_h
#define AnalysisCode_TopProducer_TopJetPairAlgorithm_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/CandidateFwd.h" 

#include "AnalysisCode/AnalysisDataFormats/interface/TopJetPair.h"

#include <TMath.h>

class TopJetPairAlgorithm
{

 public:
  
  TopJetPairAlgorithm(const edm::ParameterSet&);
  ~TopJetPairAlgorithm();
  
  TopJetPair buildTopJetPair(const edm::Ptr<reco::Candidate>&, const edm::Ptr<pat::MET>&, const edm::Ptr<pat::Jet>&, const edm::Ptr<pat::Jet>& );
  
 private:
  
  void computeTopJetPair(TopJetPair&, const edm::Ptr<reco::Candidate>&, const edm::Ptr<pat::MET>&, const edm::Ptr<pat::Jet>&, const edm::Ptr<pat::Jet>& );

  int debug_;

  double compMt(const reco::Candidate::LorentzVector& lepton,double metPx, double metPy)
  {
    double px = lepton.px() + metPx;
    double py = lepton.py() + metPy;
    double et = lepton.Et() + TMath::Sqrt(metPx*metPx + metPy*metPy);
    double mt2 = et*et - (px*px + py*py);
    if ( mt2 < 0 ) {
      edm::LogWarning ("compMt") << " mt2 = " << mt2 << " must not be negative !!";
      return 0.;
    }
    return TMath::Sqrt(mt2);
  }

  double compM(const reco::Candidate::LorentzVector& lepton, const reco::Candidate::LorentzVector& neutrino)
  {
    double px = lepton.px() + neutrino.px();
    double py = lepton.py() + neutrino.py();
    double pz = lepton.pz() + neutrino.pz();
    double e = lepton.energy() + neutrino.energy();
    double m2 = e*e - (px*px + py*py + pz*pz);
    if ( m2 < 0 ) {
      edm::LogWarning ("compM") << " m2 = " << m2 << " must not be negative !!";
      return 0.;
    }
    return TMath::Sqrt(m2);
  }

  double square(double x)
  {
    return x*x;
  }

  double cubeRoot(double x)
  {
    if (x < 0)
      return -pow(-x, 1./3);
    else
      return pow(x, 1./3);
  }
  
  
  reco::Candidate::LorentzVector compNuP4(const reco::Candidate::LorentzVector& lep, const reco::Candidate::LorentzVector& met)
  {
    //extract z component of a neutrino by fixing the W mass to PDG value                                                                                                                                                             
    double pxL = lep.px();
    double pyL = lep.py();
    double pzL = lep.pz();
    double pTL = lep.pt();
    double El = lep.energy();
    double mW = 80.385;
    reco::Candidate::LorentzVector p4nu = met;
    double px=met.px(); double py=met.py(); 
    double pz=0;

    double L = square(mW)/2 + (pxL*met.px() + pyL*met.py());
    double D = L*L - square(pTL)*square(met.pt());

    //------------------ if pz (nu) is real p3(nu) = (MET, pz)-------------------------------
    if( D > 0 || D==0){ 
      if(debug_)
	std::cout<< "Real z, compute new pz"<<std::endl; 
      double pz1 = 0, pz2 = 0;
      pz1 = L*pzL/square(pTL) + El/square(pTL)*TMath::Sqrt(D);
      pz2 = L*pzL/square(pTL) - El/square(pTL)*TMath::Sqrt(D);
      if ( abs(pz1) < abs(pz2) ) //choose the solution of smaller absolute value
	pz = pz1;
      else
	pz = pz2;
    }
    //---------------imaginary solution of pz -> set D=0, find pz and modify px, py to satisfy mW = PDG-----------------
    if( D < 0 ){ 
      if( debug_ )
	std::cout<<"Imaginary z, find px, py, pz"<<std::endl;
      pz = L*pzL/square(pTL);
           
      double a = square(lep.pt());
      double b = 3*mW*lep.pt()*lep.py();
      double c = square(mW)*( square(lep.pt()) + 2*square(lep.py()) ) - 4*pow(lep.px(),2)*( met.px()*lep.px() + met.py()*lep.py() );
      double d = mW*lep.pt()*( square(mW)*lep.py() - 4*met.py()*square(lep.px()) );

      const double coef1[4] = {d,c,b,a};
      double z1 = 0, z2 = 0, z3=0; //initialize solutions to cubic equation
      
      //---------------------Solve cubic equation for y = a(x) + sqrt(b(x))--------------------------------
      //Solving cubic equation for y = a(x) - sqrt(b(x)): TMath::RootsCubic({-d,c,-b,a},z1,z2,z3) gives equivalent px, py;
      
      TMath::RootsCubic(coef1,z1,z2,z3);
      px = ( square( z1 ) - square( mW )) / ( 4*lep.px() );
      py = ( square( mW )*lep.py() + 2*lep.px()*lep.py()*px + mW*lep.pt()*z1 ) / ( 2*square( lep.px() ) );
	
      if(debug_){
	std::cout<<"one real solution"<<std::endl;
	std::cout<<"z1 = "<< z1 <<std::endl;
	std::cout<<"px = "<< px <<", py = "<< py <<std::endl;
      }

      if( !TMath::RootsCubic(coef1,z1,z2,z3) ){ //three real roots
	std::cout<<"WARNING: THREE REAL SOLUTIONS! Use only z1"<<std::endl;
	std::cout<<"z1 = "<< z1 << ", z2 = "<< z2 << ", z3 = "<< z3 <<std::endl;
      }
    }

    //-------------------------fill neutrino 4-vector----------------------------------
    p4nu.SetPx(px);
    p4nu.SetPy(py);
    p4nu.SetPz(pz);
    p4nu.SetE(TMath::Sqrt( px*px + py*py + pz*pz) );

    return p4nu;
  }

};
  

#endif 
