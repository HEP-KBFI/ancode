import FWCore.ParameterSet.Config as cms

sidebands = cms.EDAnalyzer('SingleTopSidebands',
                           goodLeptons     = cms.InputTag('leptons','goodLeptons'),
                           vetoLeptons     = cms.InputTag('leptons','vetoLeptons'),
                           met             = cms.InputTag('patMETs'),
                           leptonFlavors   = cms.vint32(11)
                           )
