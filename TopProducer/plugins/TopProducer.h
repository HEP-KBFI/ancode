#ifndef AnalysisCode_TopProducer_TopProducer_h
#define AnalysisCode_TopProducer_TopProducer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "AnalysisCode/TopProducer/interface/TopAlgorithm.h"

class TopProducer : public edm::EDProducer 
{
 public:

  explicit TopProducer(const edm::ParameterSet&);
  ~TopProducer();

  void produce(edm::Event&, const edm::EventSetup&);

 private:

  TopAlgorithm algorithm_;

  edm::InputTag srcMET_;
  edm::InputTag srcLepton_;
  edm::InputTag srcBJet_;
};

#endif
