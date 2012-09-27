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
process.interesting.elPt = cms.untracked.double(30)     # minimal pT of electron
process.interesting.muPt = cms.untracked.double(20)     # minimal pT of electron

# Object selections are defined here
goodElectron = 'abs(eta)<2.5'

goodSignalElectron = goodElectron
goodSignalElectron += '&& pt > 30'
goodSignalElectron += '&& passConversionVeto'
goodSignalElectron += '&& dB<0.02'
goodSignalElectron += '&& !(1.4442 < abs(superCluster.eta) < 1.5660)'
goodSignalElectron += '&& gsfTrack.trackerExpectedHitsInner.numberOfHits <=0'
goodSignalElectron += '&& electronID("mvaTrigV0") > 0.1'
goodSignalElectron += '&& userFloat("rhoCorrRelIso") < 0.2'

goodVetoElectron = goodElectron
goodVetoElectron += '&& pt > 20'
goodVetoElectron += '&& electronID("mvaTrigV0") > 0.1'
goodVetoElectron += '&& userFloat("rhoCorrRelIso") < 0.3'

process.electronsWithIsolation = cms.EDProducer('ElectronIsolationProducer',
        src=cms.InputTag('selectedPatElectrons'),
        rho=cms.InputTag("kt6PFJets", "rho"),
        debug=cms.untracked.bool(True)
)

process.goodElectrons = process.selectedPatElectrons.clone(
    src='electronsWithIsolation',
    cut=goodSignalElectron
)

process.vetoElectrons = process.goodElectrons.clone(
    cut=goodVetoElectron
)

# Muon selection
process.pfIsolatedMuons.isolationCut = cms.double( 0.5 ) # this isn't PU corrected so needs to be looser

goodMuon = 'isPFMuon'

goodVetoMuon = goodMuon
goodVetoMuon += ' && abs(eta) < 2.4'
goodVetoMuon += ' && (isGlobalMuon || isTrackerMuon)'
goodVetoMuon += ' && pt > 10'
goodVetoMuon += ' && userFloat("rhoCorrRelIso") < 0.2'

goodSignalMuon = goodMuon
goodSignalMuon += ' && isGlobalMuon'
goodSignalMuon += ' && pt > 26'
goodSignalMuon += ' && abs(eta)<2.1'
goodSignalMuon += ' && normChi2 < 10'
goodSignalMuon += ' && track.hitPattern.trackerLayersWithMeasurement > 5'
goodSignalMuon += ' && globalTrack.hitPattern.numberOfValidMuonHits > 0'
goodSignalMuon += ' && dB < 0.2'
goodSignalMuon += ' && innerTrack.hitPattern.numberOfValidPixelHits > 0'
goodSignalMuon += ' && numberOfMatchedStations > 1'
goodSignalMuon += ' && userFloat("rhoCorrRelIso") < 0.12'

process.muonsWithIsolation = cms.EDProducer('MuonIsolationProducer',
        src=cms.InputTag('selectedPatMuons'),
        rho=cms.InputTag("kt6PFJets", "rho"),
        debug=cms.untracked.bool(True)
)

process.goodMuons = process.selectedPatMuons.clone(
    src='muonsWithIsolation',
    cut=goodSignalMuon
)

process.vetoMuons = process.goodMuons.clone(
    cut=goodVetoMuon
)

# Jet quality cuts
goodJet = 'pt>40'
goodJet += ' && abs(eta) < 4.7'
goodJet += ' && numberOfDaughters>1'
goodJet += ' && neutralHadronEnergyFraction<0.99'
goodJet += ' && neutralEmEnergyFraction<0.99'
goodJet += ' && (abs(eta) > 2.4 | (chargedEmEnergyFraction<0.99 && chargedHadronEnergyFraction>0 && chargedMultiplicity>0))'

process.selectedPatJets.cut = goodJet

# load the PU JetID sequence
process.load("CMGTools.External.pujetidsequence_cff")

# Trim down the genParticles collection
process.load("AnalysisCode.SlimGenParticles.slimgenparticles_cfi")

# The path that runs through the analysis
process.p = cms.Path(
    process.goodOfflinePrimaryVertices+
    process.interesting+
    getattr(process,"patPF2PATSequence")+
    process.electronsWithIsolation+
    process.goodElectrons+
    process.vetoElectrons+
    process.muonsWithIsolation+
    process.goodMuons+
    process.vetoMuons+
    process.puJetIdSqeuence+
    process.slimGenParticles
)

if isMC:
    process.GlobalTag.globaltag =  'START53_V7F::All'
else:
    process.GlobalTag.globaltag =  'FT_53_V6C_AN2::All' # NB! Set this per dataset!!!

process.source.fileNames = [
    "/store/mc/Summer12_DR53X/VBF_HToZG_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7A-v1/0000/2884E8EB-EE01-E211-AF2D-001E67396897.root"
]

process.maxEvents.input = 50
process.out.fileName = 'tuple.root'
process.out.outputCommands += [
    "keep *_vetoElectrons*_*_*",
    "keep *_goodElectrons*_*_*",
    "keep *_vetoMuons*_*_*",
    "keep *_goodMuons*_*_*",
    "keep *_puJetId_*_*",
    "keep *_puJetMva_*_*",
    "keep *_slimGenParticles_*_*",
    "keep *_offlinePrimaryVertices_*_*"
]

process.options.wantSummary = False       ##  (to suppress the long output at the end of the job)    
