import FWCore.ParameterSet.Config as cms

stanal = cms.EDAnalyzer('SingleTopAnalysis',
    goodMuons       = cms.InputTag('goodMuons'),
    vetoMuons       = cms.InputTag('vetoMuons'),
    goodElectrons   = cms.InputTag('goodElectrons'),
    vetoElectrons   = cms.InputTag('vetoElectrons'),
    jets            = cms.InputTag('selectedPatJets'),
    met             = cms.InputTag('patMETs'),
    vertex          = cms.InputTag('offlinePrimaryVertices'),
    bTagger         = cms.string("combinedSecondaryVertexMVABJetTags"),
    bTagCut         = cms.double(0.679),
    debug           = cms.bool(True),
    PUveto          = cms.bool(True)
)
