import FWCore.ParameterSet.Config as cms

filtergen = cms.EDFilter('FilterGenEvents',
    genLabel = cms.InputTag('genParticles'),
    zHadronic = cms.bool(False),
    zLeptonic = cms.bool(False),
    hzHadronic = cms.bool(False),
    hzLeptonic = cms.bool(False),
    wHadronic = cms.bool(False),
    wLeptonic = cms.bool(False)
)
