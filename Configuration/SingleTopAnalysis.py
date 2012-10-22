import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('out.root')
)

process.load('AnalysisCode.TriggerFilter.triggerfilter_cfi')

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/hdfs/local/mario/singletop/53sync/tuple_pfele.root'
    )
)
process.load('AnalysisCode.SmearedJetProducer.smearedjetproducer_cfi')
process.smearedJets.debug = cms.bool(True)

process.load('PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi')
process.selectedPatJets.src = cms.InputTag("smearedJets")
process.selectedPatJets.cut = 'userFloat("smearPt") > 40 & userInt("puId") > 0'

process.load('AnalysisCode.LeptonsProducer.leptonsproducer_cfi')
process.leptons.debug = cms.bool(True)

process.load('AnalysisCode.SingleTopFilter.singletopfilter_cfi')

process.lightJet = process.selectedPatJets.clone()
process.lightJet.src=cms.InputTag("selectedPatJets")
process.lightJet.cut = 'bDiscriminator("combinedSecondaryVertexMVABJetTags") < 0.679'

process.bJet = process.lightJet.clone()
process.bJet.cut = 'bDiscriminator("combinedSecondaryVertexMVABJetTags") > 0.679'

process.load("AnalysisCode.Configuration.htRatio_cfi")

process.p = cms.Path(
    process.trig+
    process.smearedJets+
    process.selectedPatJets+
    process.leptons+
    process.stfilt+
    process.lightJet+
    process.bJet
    +process.produceHtRatio
)
