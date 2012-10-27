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
                      debug = cms.untracked.int32(0)
                      )

produceTopJetPairs = cms.Sequence(topJetPairs)
