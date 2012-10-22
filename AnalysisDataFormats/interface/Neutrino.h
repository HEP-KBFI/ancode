#ifndef __AnalysisDataFormats_SingleTopAnalysis_Neutrino_h__
#define __AnalysisDataFormats_SingleTopAnalysis_Neutrino_h__

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/LeafCandidate.h" 


class Neutrino //: public reco::LeafCandidate
{
 public:
  /// constructor 
  explicit Neutrino() {}

  /// destructor
  ~Neutrino() {}
  
  double mTW() const { return mTW_; }
  double PyNu() const { return PyNu_; }
  double PzNu() const { return PzNu_; }
  double ENu() const { return ENu_; }
  const reco::Candidate::LorentzVector& P4Nu() const { return P4Nu_; }


 private:

  /// allow only HtRatioAlgorithm to change values of data-members
   friend class NeutrinoAlgorithm;

  void setPxNu(double mTW) { mTW_ = mTW; }
  void setPyNu(double PyNu) { PyNu_ = PyNu; }
  void setPzNu(double PzNu) { PzNu_ = PzNu; }
  void setENu(double ENu) { ENu_ = ENu; }
  void setP4Nu(const reco::Candidate::LorentzVector& P4Nu) { P4Nu_ = P4Nu; }

  /// ratio of tau pt and sum of jet pt
  double mTW_;
  double PyNu_;
  double PzNu_;
  double ENu_;
  reco::Candidate::LorentzVector P4Nu_;

};

#endif