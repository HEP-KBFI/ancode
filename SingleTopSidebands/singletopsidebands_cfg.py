import FWCore.ParameterSet.Config as cms

process = cms.Process("Sidebands")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_7_1_WKs.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_10_1_TdW.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_4_1_0wF.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_12_1_Vb0.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_8_1_3vt.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_6_1_PXR.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_2_1_OkZ.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_15_1_OGt.root"
    
    )
)

process.sidebands = cms.EDAnalyzer('SingleTopSidebands'
)


process.p = cms.Path(process.sidebands)
