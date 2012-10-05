import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('out.root')
)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/hdfs/local/mario/singletop/53sync/tbar_tuple.root'
    )
)

process.load('AnalysisCode.SingleTopAnalysis.singletopanalysis_cfi')

process.p = cms.Path(process.stanal)
