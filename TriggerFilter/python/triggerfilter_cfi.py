import FWCore.ParameterSet.Config as cms

trig = cms.EDFilter('TriggerFilter',
	trigLabel	= cms.InputTag("patTriggerEvent"),
	yesTrig		= cms.vstring( 	"HLT_IsoMu24_eta2p1_v" ),
	noTrig		= cms.vstring(''),
	debug		= cms.bool(False)
)

