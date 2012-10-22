import FWCore.ParameterSet.Config as cms

costheta = cms.EDAnalyzer('CosTheta',
    lepton      = cms.InputTag('leptons','goodLeptons'),
    neutrino    = cms.InputTag('neutrinos'),
    bjet        = cms.InputTag('bJet'),
    lightJet    = cms.InputTag('lightJet'),
    debug       = cms.bool(False)
)
