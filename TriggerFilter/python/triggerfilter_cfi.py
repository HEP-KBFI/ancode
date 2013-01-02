import FWCore.ParameterSet.Config as cms

trigMuAll = cms.EDFilter('TriggerFilter',
	trigLabel	= cms.InputTag("patTriggerEvent"),
	yesTrig		= cms.vstring( 	"HLT_IsoMu24_eta2p1_v", "HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v" ),
	noTrig		= cms.vstring(),
	debug		= cms.bool(False)
)

trigMuBtag = cms.EDFilter('TriggerFilter',
	trigLabel	= cms.InputTag("patTriggerEvent"),
	yesTrig		= cms.vstring( 	"HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v" ),
	noTrig		= cms.vstring(),
	debug		= cms.bool(False)
)

trigMu = cms.EDFilter('TriggerFilter',
	trigLabel	= cms.InputTag("patTriggerEvent"),
	yesTrig		= cms.vstring( 	"HLT_IsoMu24_eta2p1_v" ),
	noTrig		= cms.vstring(),
	debug		= cms.bool(False)
)

trigEleAll = cms.EDFilter('TriggerFilter',
	trigLabel	= cms.InputTag("patTriggerEvent"),
	yesTrig		= cms.vstring( 	"HLT_Ele27_WP80_v", "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_BTagIPIter_v" ),
	noTrig		= cms.vstring(),
	debug		= cms.bool(False)
)

trigEleBtag = cms.EDFilter('TriggerFilter',
	trigLabel	= cms.InputTag("patTriggerEvent"),
	yesTrig		= cms.vstring( 	"HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_BTagIPIter_v" ),
	noTrig		= cms.vstring(),
	debug		= cms.bool(False)
)

trigEle = cms.EDFilter('TriggerFilter',
	trigLabel	= cms.InputTag("patTriggerEvent"),
	yesTrig		= cms.vstring( 	"HLT_Ele27_WP80_v" ),
	noTrig		= cms.vstring(),
	debug		= cms.bool(False)
)

trig = cms.EDFilter('TriggerFilter',
    trigLabel   = cms.InputTag("patTriggerEvent"),
    yesTrig     = cms.vstring(  
        "HLT_Ele27_WP80_v", 
        "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_BTagIPIter_v", 
        "HLT_IsoMu24_eta2p1_v", 
        "HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v"
    ),
    noTrig      = cms.vstring(),
    debug       = cms.bool(False)
)

trigDiMu = cms.EDFilter('TriggerFilter',
    trigLabel   = cms.InputTag("patTriggerEvent"),
    yesTrig     = cms.vstring( "HLT_Mu17_Mu8_v"),
    noTrig      = cms.vstring(),
    debug       = cms.bool(False)
)
