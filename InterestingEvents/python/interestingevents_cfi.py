import FWCore.ParameterSet.Config as cms

interesting = cms.EDFilter('InterestingEvents',
    debug = cms.untracked.bool(False),
    minMuons = cms.untracked.int32(0),
    minElectrons = cms.untracked.int32(0),
    minLeptons = cms.untracked.int32(0),
    minJets = cms.untracked.int32(0),
    muPt = cms.untracked.double(15),
    elPt = cms.untracked.double(15),
    jetPt = cms.untracked.double(30),
    muEta = cms.untracked.double(2.4),
    elEta = cms.untracked.double(2.5),
    jetEta = cms.untracked.double(4.7),
    muLabel = cms.untracked.InputTag('muons'),
    elLabel = cms.untracked.InputTag('gsfElectrons'),
    jetLabel = cms.untracked.InputTag('ak5PFJets')
)
