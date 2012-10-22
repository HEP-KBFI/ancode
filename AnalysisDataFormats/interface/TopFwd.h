#ifndef AnalysisCode_AnalysisDataFormats_TopFwd_h
#define AnalysisCode_AnalysisDataFormats_TopFwd_h

#include "AnalysisCode/AnalysisDataFormats/interface/TopFwd.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefVector.h"

#include <vector>

/// collection of Top objects
typedef std::vector<Top> TopCollection;

/// persistent reference to a Top object
typedef edm::Ref<TopCollection> TopRef;

/// references to Top collection
typedef edm::RefProd<TopCollection> TopRefProd;

/// vector of references to top objects all in the same collection
typedef edm::RefVector<TopCollection> TopRefVector;

#endif
