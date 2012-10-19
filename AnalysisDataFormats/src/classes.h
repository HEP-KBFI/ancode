
#include "AnalysisCode/AnalysisDataFormats/interface/HtRatio.h"
#include "AnalysisCode/AnalysisDataFormats/interface/HtRatioFwd.h"

#include "AnalysisCode/AnalysisDataFormats/interface/Neutrino.h"
#include "AnalysisCode/AnalysisDataFormats/interface/NeutrinoFwd.h"

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


    /// create dictionaries for 
    ///  o edm::Ptr<reco::CaloJet>
    ///  o edm::Ptr<reco::PFJet>
    /// as these dictionaries are not yet created in DataFormats/JetReco/src/classes.h
    edm::Ptr<reco::CaloJet> dummyCaloJetPtr;
    edm::Ptr<reco::PFJet> dummyPFJetPtr;
    std::vector<edm::Ptr<reco::Jet> > dummyJetPtrCollection;

    /// create dictionaries for
    ///  o edm::Ptr<reco::GenParticle>
    /// as these dictionaries are not yet created in DataFormats/HepMCCandidate/src/classes.h
    edm::Ptr<reco::GenParticle> dummyGenParticlePtr;

    /// create dictionaries for
    ///  o edm::Ptr<reco::Track>
    ///  o edm::Ptr<reco::GsfTrack>
    /// as these dictionaries are not yet created in DataFormats/TrackReco/src/classes.h (DataFormats/GsfTrackReco/src/classes.h)
    edm::Ptr<reco::Track> dummyTrackPtr;
    edm::Ptr<reco::GsfTrack> dummyGsfTrackPtr;
    
    HtRatio dummyHtRatio;
    edm::Wrapper<HtRatio> dymmyHtRatioWrapper;
    HtRatioCollection dummyHtRatioCollection;
    edm::Wrapper<HtRatioCollection> dummyHtRatioCollectionWrapper;
 
    
    Neutrino dummyNeutrino;
    edm::Wrapper<Neutrino> dymmyNeutrinoWrapper;
    NeutrinoCollection dummyNeutrinoCollection;
    edm::Wrapper<NeutrinoCollection> dummyNeutrinoCollectionWrapper;
    ///  edm::Ptr<Neutrino> dummyNeutrinoPtr;


  };
}
