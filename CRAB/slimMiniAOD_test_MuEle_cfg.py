## import skeleton process

import FWCore.ParameterSet.Config as cms

process = cms.Process("DAS")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",

    fileNames = cms.untracked.vstring('root://cmsxrootd-site.fnal.gov//store/mc/RunIISpring15DR74/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v3/10000/009D49A5-7314-E511-84EF-0025905A605E.root')
)

process.out = cms.OutputModule("PoolOutputModule",

    fileName = cms.untracked.string('slimMiniAOD_crabtest1_MuEle.root'),

outputCommands = cms.untracked.vstring(['drop *', 'keep *_prunedGenParticles__*', 'keep *_slimmedMuons__*', 'keep *_slimmedMETs__*','keep *_slimmedTaus__*', 'keep *_slimmedJets__*', 'keep *_slimmedJetsAK8__*', 'keep *_slimmedElectrons__*'])
)
process.end = cms.EndPath(process.out)