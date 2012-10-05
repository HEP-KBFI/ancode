import FWCore.ParameterSet.Config as cms

stanal = cms.EDAnalyzer('SingleTopAnalysis',
    goodMuons       = cms.InputTag('goodMuons'),
    vetoMuons       = cms.InputTag('vetoMuons'),
    goodElectrons   = cms.InputTag('goodElectrons'),
    vetoElectrons   = cms.InputTag('vetoElectrons'),
    jets            = cms.InputTag('selectedPatJets'),
    met             = cms.InputTag('patMETs'),
    vertex          = cms.InputTag('offlinePrimaryVertices'),
    debug           = cms.bool(True)
)
