#ifndef __AnalysisDataFormats_SingleTopAnalysis_TopJetPair_h__
#define __AnalysisDataFormats_SingleTopAnalysis_TopJetPair_h__

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/Candidate/interface/LeafCandidate.h" 


class TopJetPair //: public reco::LeafCandidate
{
 public:
  /// constructor 
  explicit TopJetPair() {}

  /// destructor
  ~TopJetPair() {}
  
  double costh() const { return costh_; }
  double mTW() const { return mTW_; }
  double met() const { return met_; }
  const reco::Candidate::LorentzVector& p4W() const { return p4W_; }
  const reco::Candidate::LorentzVector& p4nu() const { return p4nu_; }
  const reco::Candidate::LorentzVector& p4top() const { return p4top_; }
  const reco::Candidate::LorentzVector& p4ljetTopCM() const { return p4ljetTopCM_; }
  const reco::Candidate::LorentzVector& p4leptonTopCM() const { return p4leptonTopCM_; }

 private:

  /// allow only TopJetPairAlgorithm to change values of data-members
   friend class TopJetPairAlgorithm;
   void setmTW(double mTW) {mTW_ = mTW; }
   void setmet(double met) {met_ = met; }
   void setp4W(const reco::Candidate::LorentzVector& p4W) { p4W_ = p4W; }
   void setcosth(double costh) { costh_ = costh; }
   void setp4nu(const reco::Candidate::LorentzVector& p4nu) { p4nu_ = p4nu; }
   void setp4top(const reco::Candidate::LorentzVector& p4top) { p4top_ = p4top; }
   void setp4ljetTopCM(const reco::Candidate::LorentzVector& p4ljetTopCM) { p4ljetTopCM_ = p4ljetTopCM; }
   void setp4leptonTopCM(const reco::Candidate::LorentzVector& p4leptonTopCM) { p4leptonTopCM_ = p4leptonTopCM; }


   double mTW_;
   double costh_;
   double met_;
   reco::Candidate::LorentzVector p4W_; 
   reco::Candidate::LorentzVector p4nu_;
   reco::Candidate::LorentzVector p4top_;
   reco::Candidate::LorentzVector p4ljetTopCM_;
   reco::Candidate::LorentzVector p4leptonTopCM_;
};

#endif
