import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        "/store/mc/Summer12_DR53X/WH_ZH_HToZG_M-125_8TeV-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/045160E7-B6F0-E111-A0CB-00215E21D8CA.root",
        "/store/mc/Summer12_DR53X/GluGluToHToZG_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/12C90682-72FA-E111-8A74-00266CFF0AF4.root"
    )
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('out.root')
)

process.genstat = cms.EDAnalyzer('GenStatistics',
        debug = cms.bool(True)
)

process.load("AnalysisCode.InterestingEvents.interestingevents_cfi")
process.interesting.debug = cms.untracked.bool(True)

process.p = cms.Path(process.interesting)
