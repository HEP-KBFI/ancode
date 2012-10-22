#include "AnalysisCode/AnalysisDataFormats/interface/Top.h"
#include "AnalysisCode/AnalysisDataFormats/interface/TopFwd.h"
#include "AnalysisCode/TopProducer/plugins/TopProducer.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h" 
#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "AnalysisCode/TopProducer/interface/FetchCollection.h"

TopProducer::TopProducer(const edm::ParameterSet& cfg)
  : algorithm_(cfg)
{
  srcLepton_ = cfg.getParameter<edm::InputTag>("srcLepton");
  srcMET_ = cfg.getParameter<edm::InputTag>("srcMET");
  srcBJet_ = cfg.getParameter<edm::InputTag>("srcBJet");
  
  produces<TopCollection>("");
}

TopProducer::~TopProducer()
{
  //--- nothing to be done yet...
}

void TopProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  typedef edm::View<pat::MET> MEtView;
  edm::Handle<MEtView> metCollection;
  pf::fetchCollection(metCollection, srcMET_, evt);

  typedef edm::View<reco::Candidate> leptonCollectionType;
  edm::Handle<leptonCollectionType> leptonCollection;
  pf::fetchCollection(leptonCollection, srcLepton_, evt);
  
  typedef edm::View<pat::Jet> bjetCollectionType;
  edm::Handle<bjetCollectionType> bjetCollection;
  pf::fetchCollection(bjetCollection, srcBJet_, evt);


  //--- check that there is exactly one MET object in the event----//                                                                                                                                     
  if ( metCollection->size() == 1 ) {edm::Ptr<pat::MET> metPtr = metCollection->ptrAt(0);}
  else {
    edm::LogError ("produce")
      << " Found " << metCollection->size() << " MET objects in collection = " << srcMET_;
    return;
  }

  //-------Check whether there are more than one top candidates in the event---------//
  if ( bjetCollection->size() > 1 || leptonCollection->size() > 1 )
    edm::LogWarning ("produce")
      << "Found " << bjetCollection->size() << " bjets and " << leptonCollection->size() << " leptons. "<< bjetCollection->size()*leptonCollection->size() << " top candidates are reconstructed.";

  std::auto_ptr<TopCollection> topCollection(new TopCollection());

  for ( unsigned iLepton = 0, numLeptons = leptonCollection->size(); iLepton < numLeptons; ++iLepton )
    for (unsigned iBjet = 0, numBjets = bjetCollection->size(); iBjet < numBjets; ++iBjet ){    
      edm::Ptr<reco::Candidate> leptonPtr = leptonCollection->ptrAt(iLepton);
      edm::Ptr<pat::MET> metPtr = metCollection->ptrAt(0);
      edm::Ptr<pat::Jet> bjetPtr = bjetCollection->ptrAt(iBjet);
      
      Top top = algorithm_.buildTop(leptonPtr, metPtr, bjetPtr);
      topCollection->push_back(top);
    }
 
  evt.put(topCollection);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(TopProducer);
