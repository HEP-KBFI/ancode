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
  const reco::Candidate::LorentzVector& P4Nu() const { return P4Nu_; }


 private:

  /// allow only HtRatioAlgorithm to change values of data-members
   friend class NeutrinoAlgorithm;

  void setmTW(double mTW) { mTW_ = mTW; }
  void setP4Nu(const reco::Candidate::LorentzVector& P4Nu) { P4Nu_ = P4Nu; }

  /// ratio of tau pt and sum of jet pt
  double mTW_;
  reco::Candidate::LorentzVector P4Nu_;

};

#endif
