import FWCore.ParameterSet.Config as cms

#--------------------------------------------------------------------------------
# produce data-formats providing information
# about distribution of energy deposits in the event
# with respect to direction of missing Et vector
#--------------------------------------------------------------------------------

neutrinos = cms.EDProducer("NeutrinoProducer",
                          srcMET = cms.InputTag('patMETs'),
                          srcLepton = cms.InputTag('leptons','goodLeptons'),
                          verbosity = cms.untracked.int32(1)
                          )

produceNeutrino = cms.Sequence(neutrinos)
