import FWCore.ParameterSet.Config as cms

leptons = cms.EDProducer('LeptonsProducer',
    goodMuLab   = cms.InputTag('goodMuons'),
    vetoMuLab   = cms.InputTag('vetoMuons'),
    goodElLab   = cms.InputTag('goodElectrons'),
    goodElMvaEB = cms.double(0.98),
    goodElMvaEE = cms.double(0.98),
    goodElRelIso = cms.double(0.1),
    goodElPtMax = cms.double(100),
    vetoElLab   = cms.InputTag('vetoElectrons'),
    pvLab       = cms.InputTag('goodOfflinePrimaryVertices'),
    debug       = cms.bool(False)
)
