import FWCore.ParameterSet.Config as cms

slimGenParticles = cms.EDProducer('SlimGenParticles',
    src=cms.InputTag("genParticles")
)
