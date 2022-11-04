from WMCore.Configuration import Configuration

config = Configuration()

config.section_("General")
config.General.requestName = 'CMSDAS_Data_analysis_TT_2_test'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'slimMiniAOD_data_MuEle_cfg.py'


config.section_("Data")
config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_CMSDAS_Data_analysis_TT_2_test'

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'