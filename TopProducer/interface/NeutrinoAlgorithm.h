#ifndef AnalysisCode_TopProducer_NeutrinoAlgorithm_h
#define AnalysisCode_TopProducer_NeutrinoAlgorithm_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/CandidateFwd.h" 

#include "AnalysisCode/AnalysisDataFormats/interface/Neutrino.h"

#include <TMath.h>

class NeutrinoAlgorithm
{

 public:

  NeutrinoAlgorithm(const edm::ParameterSet&);
  ~NeutrinoAlgorithm();

  Neutrino buildNeutrino(const edm::Ptr<reco::Candidate>&, const edm::Ptr<pat::MET>&);

 private:

  void computeNeutrino(Neutrino&, const edm::Ptr<reco::Candidate>&, const edm::Ptr<pat::MET>&);

  int verbosity_;

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

  double square(double x)
  {
    return x*x;
  }

};

#endif 
