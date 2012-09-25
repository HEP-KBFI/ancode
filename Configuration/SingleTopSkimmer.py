## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *

# load the PAT config
process.load("PhysicsTools.PatAlgos.patSequences_cff") 

# Import the tools
from PhysicsTools.PatAlgos.tools.pfTools import *

# do we run on MC or Data
isMC = True

# Plug PAT on PFBRECO
jetAlgo="AK5"
usePF2PAT(process,runPF2PAT=True, jetAlgo=jetAlgo, runOnMC=isMC)

# We can switch to GsfElectrons, but supposedly the inefficiency was fixed in 5_3_x
#useGsfElectrons(process,postfix,"03")

# Add electron MVA ID
process.load('EGamma.EGammaAnalysisTools.electronIdMVAProducer_cfi') 
process.eidMVASequence = cms.Sequence(  process.mvaTrigV0 + process.mvaNonTrigV0 )
#Electron ID
process.patElectrons.electronIDSources.mvaTrigV0    = cms.InputTag("mvaTrigV0")
process.patElectrons.electronIDSources.mvaNonTrigV0 = cms.InputTag("mvaNonTrigV0") 
process.patPF2PATSequence.replace( process.patElectrons, process.eidMVASequence * process.patElectrons )

# We should filter for good primary vertices
process.goodOfflinePrimaryVertices = cms.EDFilter("PrimaryVertexObjectFilter",
    filterParams =  cms.PSet(
        minNdof = cms.double( 4. ),
        maxZ    = cms.double( 24. ),
        maxRho  = cms.double( 2. )
    ),
    filter      = cms.bool( True),
    src         = cms.InputTag( 'offlinePrimaryVertices' )
)

# Perform a basic interesting events filter to reduce running time
process.load("AnalysisCode.InterestingEvents.interestingevents_cfi")
process.interesting.minLeptons = cms.untracked.int32(1) # at least one electron or muon
process.interesting.minJets = cms.untracked.int32(2)    # at least 2 jets (b-jet + VBF jet)

# The path that runs through the analysis
process.p = cms.Path(
    process.goodOfflinePrimaryVertices+
    process.interesting+
    getattr(process,"patPF2PATSequence") 
)

if isMC:
    process.GlobalTag.globaltag =  'START53_V7F::All'
else:
    process.GlobalTag.globaltag =  'FT_53_V6C_AN2::All' # NB! Set this per dataset!!!

process.source.fileNames = [
    "/store/mc/Summer12_DR53X/VBF_HToZG_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/2884E8EB-EE01-E211-AF2D-001E67396897.root"
]

process.maxEvents.input = 10
process.out.fileName = 'tuple.root'

process.options.wantSummary = False       ##  (to suppress the long output at the end of the job)    
