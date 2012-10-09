import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('out.root')
)

process.load('AnalysisCode.TriggerFilter.triggerfilter_cfi')

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/hdfs/local/mario/singletop/53sync/tbar_tuple.root'
    )
)
process.load('AnalysisCode.SingleTopAnalysis.singletopanalysis_cfi')
#process.stanal.PUveto = cms.bool(False)

process.load('AnalysisCode.SmearedJetProducer.smearedjetproducer_cfi')

process.load('PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi')
process.selectedPatJets.src = cms.InputTag("smearedJets")
process.selectedPatJets.cut = 'userFloat("smearPt") > 40'

process.p = cms.Path(
    process.trig+
    process.smearedJets+
    process.selectedPatJets+
    process.stanal
)
