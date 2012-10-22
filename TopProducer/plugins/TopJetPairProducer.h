#ifndef AnalysisCode_TopProducer_TopJetPairProducer_h
#define AnalysisCode_TopProducer_TopJetPairProducer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "AnalysisCode/TopProducer/interface/TopJetPairAlgorithm.h"

class TopJetPairProducer : public edm::EDProducer 
{
 public:

  explicit TopJetPairProducer(const edm::ParameterSet&);
  ~TopJetPairProducer();

  void produce(edm::Event&, const edm::EventSetup&);

 private:

  TopJetPairAlgorithm algorithm_;

  edm::InputTag srcMET_;
  edm::InputTag srcLepton_;
  edm::InputTag srcBJet_;
  edm::InputTag srcLJet_;
};

#endif
