import FWCore.ParameterSet.Config as cms

#--------------------------------------------------------------------------------
# produce data-formats providing information
# about distribution of energy deposits in the event
# with respect to direction of missing Et vector
#--------------------------------------------------------------------------------

tops = cms.EDProducer("TopProducer",
                      srcMET = cms.InputTag('patMETs'),
                      srcLepton = cms.InputTag('leptons','goodLeptons'),
 #                     srcJet = cms.InputTag('selectedPatJets'),
                      srcBJet = cms.InputTag('bJet'),
                      debug = cms.untracked.int32(1)
                      )

produceTop = cms.Sequence(tops)
