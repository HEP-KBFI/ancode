import FWCore.ParameterSet.Config as cms

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('optHistograms_data_aug06.root')
)

process.load('AnalysisCode.TriggerFilter.triggerfilter_cfi')

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#-----------------Tbar-----------
#    "file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-step1-synced/4abb869c2c9729b82d5a6bb08525e8d2/tuple_41_1_1gl.root",
#    "file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-step1-synced/4abb869c2c9729b82d5a6bb08525e8d2/tuple_42_1_GR2.root",
#    "file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-step1-synced/4abb869c2c9729b82d5a6bb08525e8d2/tuple_105_1_y8h.root"
#----------data aug06-----------
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_7_1_WKs.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_10_1_TdW.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_4_1_0wF.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_12_1_Vb0.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_8_1_3vt.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_6_1_PXR.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_2_1_OkZ.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_15_1_OGt.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_14_1_EX2.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_16_1_m8z.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_1_1_D47.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_3_1_JOm.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_5_1_XDV.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_9_1_CP.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_11_1_BW5.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_13_1_C30.root",
#    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-aug06-v1/2c6a66df74a4534e1b9bb81eadd2b5a7/tuple_17_1_Doq.root"
#----------data jul13A---------------
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_100_1_RT6.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_101_1_l49.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_102_1_8Tn.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_103_1_9fR.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_104_2_ZZF.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_105_1_lZk.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_107_2_dxA.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_108_1_XsT.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_109_1_XIU.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_10_1_zS5.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_110_1_HiW.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_111_1_6lc.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_112_1_zLj.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_113_1_3Pf.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_114_1_kC4.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_115_1_Rnk.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_116_1_PTI.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_117_1_TNT.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_118_1_27Q.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_119_1_epB.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_11_1_qjo.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_120_1_cGd.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_121_1_68J.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_122_1_41U.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_123_2_lQ3.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_124_1_bMx.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_125_1_Crt.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_126_1_EuI.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_127_1_q3M.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_128_1_mYt.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_129_1_0h0.root",
    "file:/hdfs/cms/store/user/mario/SingleElectron/Summer12-SingleTop-first-jul13-runA-v1/9476e6c01f0636717be2e9d2519307ba/tuple_12_1_OVM.root",

#"file:/hdfs/cms/store/user/mario/QCD_Pt_170_250_BCtoE_TuneZ2star_8TeV_pythia6/Summer12-stop-step1-synced/4abb869c2c9729b82d5a6bb08525e8d2/tuple_100_1_W6c.root",

#--------------------------------vanad------------------------------------------
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_801_1_3b1.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_802_1_q7T.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_803_1_Opu.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_804_1_mF9.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_805_1_g8X.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_806_1_fPK.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_807_1_7BN.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_808_1_V4W.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_809_1_6WN.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_80_1_HS6.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_810_1_os9.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_811_1_bMs.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_812_1_g86.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_813_1_EfY.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_814_1_vBe.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_815_1_MF7.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_816_1_MJ8.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_817_1_8ax.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_818_1_K1g.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_819_1_bGN.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_81_1_UAp.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_820_1_mRZ.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_821_1_c2U.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_822_1_sw7.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_823_1_Aar.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_824_1_JOu.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_825_1_AGP.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_826_1_3lX.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_827_1_kDf.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_828_1_rb6.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_829_1_tGs.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_82_1_sFG.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_830_1_CE0.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_831_1_H0k.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_832_1_dMv.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_833_1_7Ke.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_834_1_3p0.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_835_1_Ewk.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_836_1_Y7r.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_837_1_X81.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_96_1_zdy.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_97_1_v3J.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_98_1_Dng.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_99_1_cJA.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_9_1_iDk.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_359_2_FTu.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_35_1_kDA.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_360_2_BKu.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_361_2_zIr.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_362_2_Epp.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_363_2_Hg6.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_364_2_zvn.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_365_2_7In.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_366_1_tFw.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_367_2_6k9.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_368_1_L4y.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_369_2_Ncn.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_36_1_n87.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_370_1_MTl.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_371_2_0Z4.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_372_2_IMN.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_373_2_JXS.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_374_2_0RM.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_375_1_7RF.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_376_2_4mO.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_377_2_cKj.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_378_2_9bZ.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_379_1_fYM.root",
#"file:/hdfs/cms/store/user/mario/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/Summer12-stop-pfele-step1/08612d4202e480038f4d455e921715e5/tuple_37_1_Y52.root"
    )
)
process.load('AnalysisCode.SmearedJetProducer.smearedjetproducer_cfi')
process.smearedJets.debug = cms.bool(False)

process.load('AnalysisCode.LeptonsProducer.leptonsproducer_cfi')
process.leptons.goodElMvaEB = cms.double(0.5)
process.leptons.goodElMvaEE = cms.double(0.5)
process.leptons.goodElRelIso = cms.double(0.1)
process.leptons.goodElPtMax = cms.double(10000)
process.leptons.vetoElMva = cms.double(0.1)
process.leptons.vetoElRelIso = cms.double(0.15)
process.leptons.debug = cms.bool(False)

process.load('AnalysisCode.SingleTopFilter.singletopfilter_cfi')
process.stfilt.debug = cms.bool(False)
process.stfilt.selection = cms.string("TOP-12-011")
process.stfilt.leptonFlavors = cms.vint32(11)
process.stfilt.leadJetPt = cms.double(40)
process.stfilt.mtW = cms.double(0)
process.stfilt.metCut = cms.double(45)

process.load('PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi')
process.selectedPatJets.src = cms.InputTag("smearedJets")
process.selectedPatJets.cut = 'userFloat("smearPt") > 40 & eta < 4.5'

process.lightJet = process.selectedPatJets.clone()
process.lightJet.src=cms.InputTag("selectedPatJets")
#process.lightJet.cut = 'bDiscriminator("combinedSecondaryVertexMVABJetTags") < 0.679 & userFloat("RMS") < 0.025'
process.lightJet.cut = 'bDiscriminator("trackCountingHighPurBJetTags") < 3.41 & userFloat("RMS") < 0.025'


process.bJet = process.lightJet.clone()
#process.bJet.cut = 'bDiscriminator("combinedSecondaryVertexMVABJetTags") > 0.679'
process.bJet.cut = 'bDiscriminator("trackCountingHighPurBJetTags") > 3.41'

process.load('AnalysisCode.SingleTopSidebands.singletopsidebands_cfi')

#------------------------Skim for min 1 good photon (no iso required)--------------------------------
process.photonCounter = cms.EDFilter("CandViewCountFilter",
                                     src = cms.InputTag("bJet"),
                                     minNumber = cms.uint32(1)
                                     )

process.load("AnalysisCode.TopProducer.topJetPair_cfi")
process.topJetPairs.debug = cms.untracked.int32(0)
process.load("AnalysisCode.TopProducer.neutrino_cfi")
process.neutrinos.debug = cms.untracked.int32(0)

process.load("AnalysisCode.SingleTopFilter.singletopfilter_cfi")

process.demo = cms.EDAnalyzer('SingleTopOptimization')
 
process.printEventContent = cms.EDAnalyzer("EventContentAnalyzer")

process.p = cms.Path(
    process.trigEle+
#    process.printEventContent+    # dump of event content after PAT-tuple production
    process.smearedJets
    +process.selectedPatJets
    +process.lightJet
    +process.bJet
    +process.leptons
    +process.produceTopJetPairs
    +process.produceNeutrinos
    +process.sidebands
    +process.stfilt
    +process.demo
#    +process.trigEleAll
#    +process.trigEle
)
