import FWCore.ParameterSet.Config as cms

from Validation.RecoVertex.PrimaryVertexAnalyzer4PUSlimmed_cfi import *

hltMultiPVanalysis = vertexAnalysis.clone()
hltMultiPVanalysis.simG4                 = cms.InputTag("g4SimHits")
hltMultiPVanalysis.use_TP_associator     = cms.untracked.bool(False)
hltMultiPVanalysis.verbose               = cms.untracked.bool(False)
hltMultiPVanalysis.sigma_z_match         = cms.untracked.double(3.0)
hltMultiPVanalysis.root_folder           = cms.untracked.string("HLT/Vertexing/ValidationWRTsim")
hltMultiPVanalysis.recoTrackProducer     = cms.untracked.string("hltPixelTracks")
hltMultiPVanalysis.vertexRecoCollections = cms.VInputTag(
    "hltPixelVertices",
    "hltTrimmedPixelVertices"
#    "hltFastPVPixelVertices"
)

hltMultiPVValidation = cms.Sequence( 
  hltMultiPVanalysis
)
