#ifndef AnalysisCode_AnalysisDataFormats_NeutrinoFwd_h
#define AnalysisCode_AnalysisDataFormats_NeutrinoFwd_h

#include "AnalysisCode/AnalysisDataFormats/interface/NeutrinoFwd.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/RefVector.h"

#include <vector>

/// collection of Neutrino objects
typedef std::vector<Neutrino> NeutrinoCollection;

/// persistent reference to a Neutrino object
typedef edm::Ref<NeutrinoCollection> NeutrinoRef;

/// references to Neutrino collection
typedef edm::RefProd<NeutrinoCollection> NeutrinoRefProd;

/// vector of references to Neutrino objects all in the same collection
typedef edm::RefVector<NeutrinoCollection> NeutrinoRefVector;

#endif
