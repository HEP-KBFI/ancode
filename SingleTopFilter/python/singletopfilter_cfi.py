import FWCore.ParameterSet.Config as cms

stfilt = cms.EDFilter('SingleTopFilter',
    goodLeptons     = cms.InputTag('leptons','goodLeptons'),
    vetoLeptons     = cms.InputTag('leptons','vetoLeptons'),
    jets            = cms.InputTag('selectedPatJets'),
    met             = cms.InputTag('patMETs'),
    bTagger         = cms.string("combinedSecondaryVertexMVABJetTags"),
    bTagCut         = cms.double(0.679),
    debug           = cms.bool(True)
)
