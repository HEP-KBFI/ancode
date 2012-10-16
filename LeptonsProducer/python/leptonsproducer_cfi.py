import FWCore.ParameterSet.Config as cms

leptons = cms.EDProducer('LeptonsProducer',
    goodMuLab   = cms.InputTag('goodMuons'),
    vetoMuLab   = cms.InputTag('vetoMuons'),
    goodElLab   = cms.InputTag('goodElectrons'),
    vetoElLab   = cms.InputTag('vetoElectrons'),
    pvLab       = cms.InputTag('goodOfflinePrimaryVertices'),
    debug       = cms.bool(False)
)
