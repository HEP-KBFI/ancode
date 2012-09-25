## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

# Define identification cuts
from PhysicsTools.PatAlgos.tools.pfTools import *
usePFIso( process )

# Let's do some MET corrections stuff
process.load("JetMETCorrections.Type1MET.pfMETCorrections_cff")

switchToPFMET( process, input=cms.InputTag('pfType1CorrectedMet') )

from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
                    cms.InputTag('ak5PFJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5PF', ['L2Relative', 'L3Absolute']),  
                    doType1MET       = True,            
                    genJetCollection = cms.InputTag("ak5GenJets")
                    ) 

# Choose selectors 
from Selections import *
process.selectedPatMuons.cut="pt>20 & abs(eta)<2.1 & "+tightMuonCut+" & "+tightMuonIsoCut
process.selectedPatElectrons.cut = "pt>30 & abs(eta)<2.5 & "+tightEleCut+" & "+tightEleIsoCut
process.selectedPatJets.cut = "pt>30 & "+looseJetCut

# Create VETO collections
process.vetoSelectedPatMuons = process.selectedPatMuons.clone()
process.vetoSelectedPatMuons.cut = "pt>10 & abs(eta)<2.5 & "+looseMuonCut+" & "+looseMuonIsoCut
process.vetoSelectedPatElectrons = process.selectedPatElectrons.clone()
process.vetoSelectedPatElectrons.cut = "pt>15 & abs(eta)<2.5 & "+looseEleCut+" & "+looseEleIsoCut

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('out.root')
)
process.skimmer = cms.EDFilter('Skimmer',
        debug = cms.bool(False),
        maxJets = cms.int32(99)
      )

process.jetanal = cms.EDAnalyzer('JetStatistics',
        debug = cms.bool(False)
      )

process.jetanallep = cms.EDAnalyzer('JetStatistics',
        debug = cms.bool(False)
      )

# Required filters
process.noscraping = cms.EDFilter("FilterOutScraping",
          applyfilter = cms.untracked.bool(True),
          debugOn = cms.untracked.bool(False),
          numtrack = cms.untracked.uint32(10),
          thresh = cms.untracked.double(0.25)
          )

process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
          vertexCollection = cms.InputTag('offlinePrimaryVertices'),
          minimumNDOF = cms.uint32(4),
          maxAbsZ = cms.double(24), 
          maxd0 = cms.double(2) 
          )

process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')

# load the PU JetID sequence
process.load("CMGTools.External.pujetidsequence_cff")
process.puJetId.jets=cms.InputTag('cleanPatJets')
process.puJetMva.jets=cms.InputTag('cleanPatJets')

## let it run
process.p = cms.Path(
    process.noscraping*
    process.primaryVertexFilter*
    process.HBHENoiseFilter*
    process.producePFMETCorrections*
    process.patDefaultSequence*
    process.vetoSelectedPatMuons*
    process.vetoSelectedPatElectrons*
    process.puJetIdSqeuence*
    process.jetanal*
    process.skimmer*
    process.jetanallep
    )

process.GlobalTag.globaltag =  'START52_V9::All'    ##  (according to https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions)
process.source.fileNames = [          ##
                            "/store/mc/Summer12/Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S7_START52_V9-v1/0000/04C623F1-7C8E-E111-8F67-00261894390A.root"
                           ]                                     ##  (e.g. 'file:AOD.root')
process.maxEvents.input = 500         ##  (e.g. -1 to run on all events)
process.out.fileName = 'tuple.root'            ##  (e.g. 'myTuple.root')
# keep the PU JetID products
process.out.outputCommands.extend(["keep *_puJetId_*_*", # input variables
                    "keep *_puJetMva_*_*" # final MVAs and working point flags
                   ])
#process.out.outputCommands+=cms.untracked.vstring("keep *_loose*")
print process.out.outputCommands
#process.out.outputCommands = cms.untracked.vstring('drop *')
process.options.wantSummary = False       ##  (to suppress the long output at the end of the job)    
