#ifndef AnalysisCode_TopProducer_HtRatioAlgorithm_h
#define AnalysisCode_TopProducer_HtRatioAlgorithm_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "AnalysisCode/AnalysisDataFormats/interface/HtRatio.h"

class HtRatioAlgorithm
{
  typedef edm::View<pat::Jet> jetCollectionType;

 public:

  HtRatioAlgorithm(const edm::ParameterSet&);
  ~HtRatioAlgorithm();

  HtRatio buildHtRatio(const edm::Ptr<pat::Tau>&, const jetCollectionType&);

 private:

  void computeHtRatio(HtRatio&, const edm::Ptr<pat::Tau>&, const jetCollectionType&);

  int verbosity_;
};

#endif 
