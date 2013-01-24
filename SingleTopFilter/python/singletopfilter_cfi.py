import FWCore.ParameterSet.Config as cms

stfilt = cms.EDFilter('SingleTopFilter',
    goodLeptons     = cms.InputTag('leptons','goodLeptons'),
    vetoLeptons     = cms.InputTag('leptons','vetoLeptons'),
    leptonFlavors   = cms.vint32(11,13),
    jets            = cms.InputTag('selectedPatJets'),
    met             = cms.InputTag('patMETs'),
    bTagger         = cms.string("combinedSecondaryVertexMVABJetTags"),
    bTagCut         = cms.double(0.679),
    leadJetPt       = cms.double(40),
    mtW             = cms.double(0),
    metCut          = cms.double(45),
    debug           = cms.bool(True),
    selection       = cms.string("sync")
)
