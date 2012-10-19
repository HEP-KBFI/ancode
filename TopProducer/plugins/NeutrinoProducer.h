#ifndef AnalysisCode_TopProducer_NeutrinoProducer_h
#define AnalysisCode_TopProducer_NeutrinoProducer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "AnalysisCode/TopProducer/interface/NeutrinoAlgorithm.h"

class NeutrinoProducer : public edm::EDProducer 
{
 public:

  explicit NeutrinoProducer(const edm::ParameterSet&);
  ~NeutrinoProducer();

  void produce(edm::Event&, const edm::EventSetup&);

 private:

  NeutrinoAlgorithm algorithm_;

  edm::InputTag srcMET_;
  edm::InputTag srcLepton_;

};

#endif
