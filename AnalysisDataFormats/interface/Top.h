#ifndef __AnalysisDataFormats_SingleTopAnalysis_Top_h__
#define __AnalysisDataFormats_SingleTopAnalysis_Top_h__

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/LeafCandidate.h" 


class Top //: public reco::LeafCandidate
{
 public:
  /// constructor 
  explicit Top() {}

  /// destructor
  ~Top() {}
  
  double mTW() const { return mTW_; }
  const reco::Candidate::LorentzVector& P4Nu() const { return P4Nu_; }
  const reco::Candidate::LorentzVector& p4() const { return p4_; }

 private:

  /// allow only TopAlgorithm to change values of data-members
   friend class TopAlgorithm;
   void setmTW(double mTW) { mTW_ = mTW; }
   void setP4Nu(const reco::Candidate::LorentzVector& P4Nu) { P4Nu_ = P4Nu; }
   void setp4(const reco::Candidate::LorentzVector& p4) { p4_ = p4; }

  /// tau 4-vector
   double mTW_;
   reco::Candidate::LorentzVector P4Nu_;
   reco::Candidate::LorentzVector p4_;
};

#endif
