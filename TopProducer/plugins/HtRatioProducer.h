#ifndef AnalysisCode_TopProducer_HtRatioProducer_h
#define AnalysisCode_TopProducer_HtRatioProducer_h

/** \class HtRatioProducer
 *
 *
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "AnalysisCode/TopProducer/interface/HtRatioAlgorithm.h"

class HtRatioProducer : public edm::EDProducer 
{
 public:

  explicit HtRatioProducer(const edm::ParameterSet&);
  ~HtRatioProducer();

  void produce(edm::Event&, const edm::EventSetup&);

 private:

  HtRatioAlgorithm algorithm_;

  edm::InputTag srcJet_;
  edm::InputTag srcTau_;

};

#endif
