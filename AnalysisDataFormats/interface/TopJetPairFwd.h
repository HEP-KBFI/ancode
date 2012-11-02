#ifndef AnalysisCode_AnalysisDataFormats_TopJetPairFwd_h
#define AnalysisCode_AnalysisDataFormats_TopJetPairFwd_h

#include "AnalysisCode/AnalysisDataFormats/interface/TopJetPairFwd.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefVector.h"

#include <vector>

/// collection of Top objects
typedef std::vector<TopJetPair> TopJetPairCollection;

/// persistent reference to a Top object
typedef edm::Ref<TopJetPairCollection> TopJetPairRef;

/// references to Top collection
typedef edm::RefProd<TopJetPairCollection> TopJetPairRefProd;

/// vector of references to top objects all in the same collection
typedef edm::RefVector<TopJetPairCollection> TopJetPairRefVector;

#endif
