import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:tuple.root'
    )
)

process.load('AnalysisCode.FilterGenEvents.filtergenevents_cfi')
#process.filtergen.genLabel = cms.InputTag('slimGenParticles')
process.filtergen.hzHadronic = cms.bool(True)

process.demo = cms.EDAnalyzer('DumpTriggerStatistics',
        trigLabel=cms.InputTag("patTriggerEvent")
)

process.p = cms.Path(process.filtergen+process.demo)