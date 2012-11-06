import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('optHistograms.root')
)

process.load('AnalysisCode.TriggerFilter.triggerfilter_cfi')

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/hdfs/local/mario/singletop/53sync/tuple_pfele.root'
    )
)
process.load('AnalysisCode.SmearedJetProducer.smearedjetproducer_cfi')
process.smearedJets.debug = cms.bool(False)

process.load('PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi')
process.selectedPatJets.src = cms.InputTag("smearedJets")
process.selectedPatJets.cut = 'userFloat("smearPt") > 40 & userInt("puId") > 0 & userInt("RMS") < 0.025'

process.load('AnalysisCode.LeptonsProducer.leptonsproducer_cfi')
#process.leptons.debug = cms.bool(True)

process.load('AnalysisCode.SingleTopFilter.singletopfilter_cfi')
process.stfilt.debug = cms.bool(False)
process.stfilt.selection = cms.string("sync") #("TOP-12-011")

process.lightJet = process.selectedPatJets.clone()
process.lightJet.src=cms.InputTag("selectedPatJets")
process.lightJet.cut = 'bDiscriminator("combinedSecondaryVertexMVABJetTags") < 0.679'

process.bJet = process.lightJet.clone()
process.bJet.cut = 'bDiscriminator("combinedSecondaryVertexMVABJetTags") > 0.679'

#------------------------Skim for min 1 good photon (no iso required)--------------------------------
process.photonCounter = cms.EDFilter("CandViewCountFilter",
                                     src = cms.InputTag("bJet"),
                                     minNumber = cms.uint32(1)
                                     )

process.load("AnalysisCode.TopProducer.topJetPair_cfi")
process.topJetPairs.debug = cms.untracked.int32(0)

process.load("AnalysisCode.SingleTopFilter.singletopfilter_cfi")

process.demo = cms.EDAnalyzer('SingleTopOptimization')
 
process.printEventContent = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(
#    process.trig+
#    process.printEventContent    # dump of event content after PAT-tuple production
    process.smearedJets
    +process.selectedPatJets
    +process.leptons
    +process.lightJet
    +process.bJet
    +process.stfilt
    +process.produceTopJetPairs
    +process.demo
#    +process.selectW


)
