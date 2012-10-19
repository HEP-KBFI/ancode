#ifndef AnalysisCode_AnalysisDataFormats_HtRatioFwd_h
#define AnalysisCode_AnalysisDataFormats_HtRatioFwd_h

#include "AnalysisCode/AnalysisDataFormats/interface/HtRatioFwd.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefVector.h"

#include <vector>

/// collection of HtRatio objects
typedef std::vector<HtRatio> HtRatioCollection;

/// persistent reference to a HtRatio object
typedef edm::Ref<HtRatioCollection> HtRatioRef;

/// references to HtRatio collection
typedef edm::RefProd<HtRatioCollection> HtRatioRefProd;

/// vector of references to htRatio objects all in the same collection
typedef edm::RefVector<HtRatioCollection> HtRatioRefVector;

#endif
