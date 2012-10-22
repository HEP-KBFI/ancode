#ifndef AnalysisCode_TopProducer_TopCandidateObjectSelector_h
#define AnalysisCode_TopProducer_TopCandidateObjectSelector_h

#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/ObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleElementCollectionSelector.h"

#include "AnalysisCode/AnalysisDataFormats/interface/Neutrino.h"
#include <vector>

typedef SingleObjectSelector<std::vector<Neutrino>,StringCutObjectSelector<Neutrino> > NeutrinoSelector;

#endif
