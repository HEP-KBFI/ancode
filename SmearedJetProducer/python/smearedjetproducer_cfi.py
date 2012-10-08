import FWCore.ParameterSet.Config as cms

smearedJets = cms.EDProducer('SmearedJetProducer',
    inLabel = cms.InputTag("patJets"),
    etaBins = cms.vdouble(0.5, 1.1, 1.7, 2.3, 5.0),
    factors = cms.vdouble(1.052, 1.057, 1.096, 1.134, 1.288)
)
