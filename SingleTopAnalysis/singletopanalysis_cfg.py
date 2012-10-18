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
        'file:/hdfs/local/mario/singletop/53sync/tuple_gsfele.root'
      #  'file:/hdfs/local/mario/singletop/53sync/tbar_tuple_sync2.root'
      #  'file:../Configuration/tuple.root'
    )
)
process.load('AnalysisCode.SingleTopAnalysis.singletopanalysis_cfi')
#process.stanal.PUveto = cms.bool(False)

process.load('AnalysisCode.SmearedJetProducer.smearedjetproducer_cfi')
process.smearedJets.debug = cms.bool(True)

process.load('PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi')
process.selectedPatJets.src = cms.InputTag("smearedJets")
process.selectedPatJets.cut = 'userFloat("smearPt") > 40 & userInt("puId") > 0'

process.load('AnalysisCode.LeptonsProducer.leptonsproducer_cfi')
process.leptons.debug = cms.bool(True)

process.dumpContent = cms.EDAnalyzer('EventContentAnalyzer')

process.goodOfflinePrimaryVertices = cms.EDFilter("PrimaryVertexObjectFilter",
    filterParams =  cms.PSet(
        minNdof = cms.double( 4. ),
        maxZ    = cms.double( 24. ),
        maxRho  = cms.double( 2. )
    ),
    filter      = cms.bool( True),
    src         = cms.InputTag( 'offlinePrimaryVertices' )
)

process.p = cms.Path(
    process.trig+
    process.goodOfflinePrimaryVertices+
    process.smearedJets+
    process.selectedPatJets+
    process.leptons+
    process.stanal
)
