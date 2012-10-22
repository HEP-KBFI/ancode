import FWCore.ParameterSet.Config as cms

#--------------------------------------------------------------------------------
# produce data-formats providing information
# about distribution of energy deposits in the event
# with respect to direction of missing Et vector
#--------------------------------------------------------------------------------

neutrinos = cms.EDProducer("NeutrinoProducer",
                          srcMET = cms.InputTag('patMETs'),
                          srcLepton = cms.InputTag('leptons','goodLeptons'),
                          debug = cms.untracked.int32(1)
                          )

selectedW = cms.EDFilter("NeutrinoSelector",
                         src = cms.InputTag("neutrinos"),
                         cut = cms.string('mTW() > 50'),
                         filter = cms.bool(False)
                         )


produceNeutrino = cms.Sequence(neutrinos)
selectW = cms.Sequence(selectedW)
