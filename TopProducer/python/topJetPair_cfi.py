import FWCore.ParameterSet.Config as cms

#--------------------------------------------------------------------------------
# produce data-formats providing information
# about distribution of energy deposits in the event
# with respect to direction of missing Et vector
#--------------------------------------------------------------------------------

topJetPairs = cms.EDProducer("TopJetPairProducer",
                      srcMET = cms.InputTag('patMETs'),
                      srcLepton = cms.InputTag('leptons','goodLeptons'),
                      srcBJet = cms.InputTag('bJet'),
                      srcLJet = cms.InputTag('lightJet'),
                      nuComputation = cms.untracked.int32(1), # 1 - always modify full 4vector with cubic solution. 2 - modify full 4vector only in case of imaginary solution of pz
                      debug = cms.untracked.int32(1)
                      )

produceTopJetPairs = cms.Sequence(topJetPairs)
