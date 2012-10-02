Analysis code repository that is supposed to contain multiple analysis from KBFI group

Right now tested on CMSSW_5_3_4, but the following needs to be done as well:

1) PAT current recepy from: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATReleaseNotes52X#V08_09_37
2) Pileup Jet ID: cvs co -r V00-02-10 -d CMGTools/External UserCode/CMG/CMGTools/External
3) EGamma ID for MVA: 
cvs co -r V00-00-13 -d EGamma/EGammaAnalysisTools UserCode/EGamma/EGammaAnalysisTools
         cd EGamma/EGammaAnalysisTools/data
         cat download.url | xargs wget

Note, I have used a newer tag due to PF isolation studies:
cvs co -r V00-00-21 -d EGamma/EGammaAnalysisTools UserCode/EGamma/EGammaAnalysisTools
cvs up -r 1.13 EGamma/EGammaAnalysisTools/interface/PFIsolationEstimator.h
cvs up -r 1.20 EGamma/EGammaAnalysisTools/src/PFIsolationEstimator.cc

