#ifndef AnalysisCode_TopProducer_TopAlgorithm_h
#define AnalysisCode_TopProducer_TopAlgorithm_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/CandidateFwd.h" 

#include "AnalysisCode/AnalysisDataFormats/interface/Top.h"

#include <TMath.h>

class TopAlgorithm
{

 public:
  
  TopAlgorithm(const edm::ParameterSet&);
  ~TopAlgorithm();
  
  Top buildTop(const edm::Ptr<reco::Candidate>&, const edm::Ptr<pat::MET>&, const edm::Ptr<pat::Jet>&);
  
 private:
  
  void computeTop(Top&, const edm::Ptr<reco::Candidate>&, const edm::Ptr<pat::MET>&, const edm::Ptr<pat::Jet>&);

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

};

#endif 
