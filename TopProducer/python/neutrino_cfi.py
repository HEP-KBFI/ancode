import FWCore.ParameterSet.Config as cms

#--------------------------------------------------------------------------------
# produce data-formats providing information
# about distribution of energy deposits in the event
# with respect to direction of missing Et vector
#--------------------------------------------------------------------------------

neutrinos = cms.EDProducer("NeutrinoProducer",
                           srcMET = cms.InputTag('patMETs'),
                           srcLepton = cms.InputTag('leptons','goodLeptons'),
                           debug = cms.untracked.int32(1),
                           nuComputation = cms.untracked.int32(1)  # 1 - always modify full 4vector with cubic solution. 2 - modify full 4vector only in case of imaginary solution of pz
                           )

selectedW = cms.EDFilter("NeutrinoSelector",
                         src = cms.InputTag("neutrinos"),
                         cut = cms.string('mTW() > 50'),
                         filter = cms.bool(False)
                         )


produceNeutrinos = cms.Sequence(neutrinos)
selectW = cms.Sequence(selectedW)
