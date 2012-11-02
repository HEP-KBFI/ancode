
#include "AnalysisCode/AnalysisDataFormats/interface/Neutrino.h"
#include "AnalysisCode/AnalysisDataFormats/interface/NeutrinoFwd.h"

#include "AnalysisCode/AnalysisDataFormats/interface/Top.h"
#include "AnalysisCode/AnalysisDataFormats/interface/TopFwd.h"

#include "AnalysisCode/AnalysisDataFormats/interface/TopJetPair.h"
#include "AnalysisCode/AnalysisDataFormats/interface/TopJetPairFwd.h"

#include "DataFormats/Common/interface/AssociationVector.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Common/interface/OwnVector.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"


#include "DataFormats/VertexReco/interface/Vertex.h"

namespace {
  struct AnalysisDataFormats_TauAnalysis_dictionary {
    
    TopJetPair dummyTopJetPair;
    edm::Wrapper<TopJetPair> dymmyTopJetPairWrapper;
    TopJetPairCollection dummyTopJetPairCollection;
    edm::Wrapper<TopJetPairCollection> dummyTopJetPairCollectionWrapper;

    Top dummyTop;
    edm::Wrapper<Top> dymmyTopWrapper;
    TopCollection dummyTopCollection;
    edm::Wrapper<TopCollection> dummyTopCollectionWrapper;
       
    Neutrino dummyNeutrino;
    edm::Wrapper<Neutrino> dymmyNeutrinoWrapper;
    NeutrinoCollection dummyNeutrinoCollection;
    edm::Wrapper<NeutrinoCollection> dummyNeutrinoCollectionWrapper;
    ///  edm::Ptr<Neutrino> dummyNeutrinoPtr;


  };
}
