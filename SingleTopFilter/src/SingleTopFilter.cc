// -*- C++ -*-
//
// Package:    SingleTopFilter
// Class:      SingleTopFilter
// 
/**\class SingleTopFilter SingleTopFilter.cc AnalysisCode/SingleTopFilter/src/SingleTopFilter.cc

 Description: Filter events based on single top reference selection

 Implementation:
     The selection is based on requiring exactly one lepton, two jets of which one is b-tagged and passing W mass constraint. The steps will be
     logged for efficiency in a histogram
*/
//
// Original Author:  Mario Kadastik
//         Created:  Thu Oct 18 11:22:04 EEST 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Objects for analysis
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

// Services for histogramming and trees
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
//
//
// class declaration
//

class SingleTopFilter : public edm::EDFilter {
   public:
      explicit SingleTopFilter(const edm::ParameterSet&);
      ~SingleTopFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      bool debug;
      edm::InputTag goodLepLab, vetoLepLab, jetLab, metLab;
      std::string bTagger, selection;
      double bTagCut;
      TH1D *cflow, *mtWmet, *met, *mtWmet_f, *met_f,*leadJetPt, *nextJetPt, *leadJetEta, *nextJetEta;
      TH1F *leadJetSPt, *nextJetSPt, *leadJetPUmva, *nextJetPUmva, *vetoJetPUmva, *vetoJetRMS, *bJetSPt, *lJetSPt, *lJetRMS;
      TH1I *numJets, *numJetsLB;
      std::vector<int> lepFlavors;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
SingleTopFilter::SingleTopFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   debug      = iConfig.getParameter<bool>("debug");
   goodLepLab = iConfig.getParameter<edm::InputTag>("goodLeptons");
   vetoLepLab = iConfig.getParameter<edm::InputTag>("vetoLeptons");
   jetLab     = iConfig.getParameter<edm::InputTag>("jets");
   metLab     = iConfig.getParameter<edm::InputTag>("met");
   bTagger    = iConfig.getParameter<std::string>("bTagger");
   selection  = iConfig.getParameter<std::string>("selection");  
   bTagCut    = iConfig.getParameter<double>("bTagCut");
   lepFlavors = iConfig.getParameter<std::vector<int> >("leptonFlavors");
}


SingleTopFilter::~SingleTopFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
SingleTopFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace pat;

   int ev = iEvent.id().event();
   // Let's count all events
   cflow->Fill(0);

   // Let's start with good leptons
   Handle<reco::CandidateCollection> leps;
   iEvent.getByLabel(goodLepLab,leps);

   Handle<reco::CandidateCollection> veto;
   iEvent.getByLabel(vetoLepLab,veto);

   Handle<JetCollection> jets;
   iEvent.getByLabel(jetLab,jets);

   Handle<METCollection> mets;
   iEvent.getByLabel(metLab,mets);

   if (leps->size() != 1) return false;
   if (debug)
     for (reco::CandidateCollection::const_iterator it = leps->begin(); it != leps->end(); it++)
       cout << "Lepton: " << it->pdgId() << " pt = " << it->pt() << endl;

   // Let's check if the flavor matches that of allowed flavors too                                                                                                                           
   int pid = abs(leps->begin()->pdgId());
   bool pass = false;
   for (unsigned int i = 0; i<lepFlavors.size(); i++)
     if (pid == lepFlavors[i]) pass=true;

   if (!pass) return false;
   cflow->Fill(1); // Passed single good lepton cut                                                                                                                                           
   if (debug) cout << "Step 1 pass: " << ev << endl;


   if( selection == "TOP-12-011"){
     bool muveto = false;
     bool elveto = false;
     
     for (reco::CandidateCollection::const_iterator it = veto->begin(); it != veto->end(); it++) {
       if (abs(it->pdgId()) == 11) elveto = true;
       if (abs(it->pdgId()) == 13) muveto = true;
     }
     
     if (muveto) return false;
     cflow->Fill(2); // Passed muon veto cut     

     if (elveto) return false;
     cflow->Fill(3); // Passed also electron veto cut   

     Handle<JetCollection> ljets;
     iEvent.getByLabel("lightJet",ljets);

     Handle<JetCollection> bjets;
     iEvent.getByLabel("bJet",bjets);

     int i = 0;
     for (JetCollection::const_iterator it = jets->begin(); it != jets->end(); it++){
       if(i == 0){
         leadJetPt->Fill( it->pt() );
	 leadJetEta->Fill( it->eta() );
	 leadJetPUmva->Fill( it->userFloat("puMVA") );
       }
       if(i == 1){
         nextJetPt->Fill( it->pt() );
	 nextJetEta->Fill( it->eta() );
	 nextJetPUmva->Fill( it->userFloat("puMVA") );
       }
       if(i > 1){
	 vetoJetPUmva->Fill( it->userFloat("puMVA") );
	 vetoJetRMS->Fill( it->userFloat("RMS") );
       }
       i++;
     }
     numJets->Fill(i);
     numJetsLB->Fill( bjets->size() + ljets->size() );

     //     for(JetCollection::const_iterator it = ljets->begin(); it != ljets->end(); it++)
     //  cout<<"pt = "<<it->userFloat("smearPt")<<", phi = "<<it->phi()<<", eta = "<<it->eta()<<endl;

     //--------------exactly 1 b-jet existence----------------------------                                                                                                                             
     if ( bjets->size() != 1 ) return false;
     cflow->Fill(4);
     bJetSPt->Fill( bjets->begin()->userFloat("smearPt") );

     //----------------2 jets with leading jet pt > 60----------------------
     if( ljets->size() + bjets->size() != 2 || ( ljets->begin()->userFloat("smearPt") < 60  && bjets->begin()->userFloat("smearPt") < 60 ) ) return false;
     cflow->Fill(5); // Passed jet counting and leading jet cut                

     lJetSPt->Fill( ljets->begin()->userFloat("smearPt") );
     lJetRMS->Fill( ljets->begin()->userFloat("RMS") );

     if(ljets->begin()->userFloat("smearPt") > bjets->begin()->userFloat("smearPt") ){
       leadJetSPt->Fill( ljets->begin()->userFloat("smearPt") );
       nextJetSPt->Fill( bjets->begin()->userFloat("smearPt") );
     }
     else{
       leadJetSPt->Fill( bjets->begin()->userFloat("smearPt") );
       nextJetSPt->Fill( ljets->begin()->userFloat("smearPt") );
     }
     //-------------------------- W mT -------------------------
     double mt = 0;
     double mx = mets->begin()->px();
     double my = mets->begin()->py();
     double mett = mets->begin()->pt();

     double lepx = leps->begin()->px();
     double lepy = leps->begin()->py();
     double leppt = leps->begin()->pt();

     mt = sqrt( pow(leppt+mett,2) - pow(lepx+mx,2) - pow(lepy+my,2) );

     mtWmet->Fill( mt );
     met->Fill( mets->begin()->pt() );

     if( mt < 40 ) return false;
     cflow->Fill(6);

     met_f->Fill( mets->begin()->pt() );                                                                                                                                           
     mtWmet_f->Fill(mt);

     // pat electrons                                                                                                                                                                                                           
     Handle<pat::ElectronCollection> gEl;
     iEvent.getByLabel("goodElectrons",gEl);
     if(gEl->size() < 1 ){
       return false;
       cout<<"last selection not applied, there are no good electrons"<<endl;
     }

     if( gEl->begin()->electronID("mvaTrigV0") > 0.98 && gEl->begin()->userFloat("rhoCorrRelIso") < 0.1 )  cflow->Fill(7);

     return true;     
   }


   if( selection == "sync"){

     // Next let's read the veto collection and see if there are any muons/electrons to veto the event
     bool muveto = false;
     bool elveto = false;
      
     for (reco::CandidateCollection::const_iterator it = veto->begin(); it != veto->end(); it++) {
       if (abs(it->pdgId()) == 11) elveto = true;
       if (abs(it->pdgId()) == 13) muveto = true;
     }
     
     if (muveto) return false;
     cflow->Fill(2); // Passed muon veto cut
     if (debug) cout << "Step 2 pass: " << ev << endl;
     
     if (elveto) return false;
     cflow->Fill(3); // Passed also electron veto cut
     if (debug) cout << "Step 3 pass: " << ev << endl;
     
     // Let's turn to jets
     if (jets->size() != 2) return false;
     cflow->Fill(4); // Passed jet counting cut
     if (debug) cout << "Step 4 pass: " << ev << endl;
     
     // Now W mass constraint
     double mt = 0;
     double mx = mets->begin()->px();
     double my = mets->begin()->py();
     double met = mets->begin()->pt();
     
     double lepx = leps->begin()->px();
     double lepy = leps->begin()->py();
     double leppt = leps->begin()->pt();
     
     mt = sqrt( pow(leppt+met,2) - pow(lepx+mx,2) - pow(lepy+my,2) );

     if (debug) cout << "Mt calc: mx=" << mx << " my=" << my << " met=" << met << " px=" << lepx << " py=" << lepy << " pt=" << leppt << " mt=" << mt << endl;
     
     if (mt < 40) return false;
     cflow->Fill(5);
     if (debug) cout << "Step 5 pass: " << ev << endl;
     
     // And finally, do we have exactly one b-jet?
     int nBjet = 0;
     for (JetCollection::const_iterator it = jets->begin(); it != jets->end(); it++)
       if (it->bDiscriminator(bTagger) > bTagCut) 
	 nBjet++;
     
     if (nBjet != 1) return false;
     cflow->Fill(6); // Final passing count
     if (debug) cout << "Step 6 pass: " << ev << endl;
     
     return true;
   }

   else{
     edm::LogWarning ("SingleTopFilter") << "Choose a valid selection path. Options: 'sync', 'TOP-12-011' ";
     return false;
   }

}

// ------------ method called once each job just before starting event loop  ------------
void 
SingleTopFilter::beginJob()
{
  edm::Service<TFileService> fs;
  cflow = fs->make<TH1D>("cflow","Cut flow for sync",10,0,10);

  leadJetEta = fs->make<TH1D>("leadJetEta","lead jet eta",300,-5.2,5.2);
  nextJetEta = fs->make<TH1D>("nextJetEta","lead jet eta",300,-5.2,5.2);
  leadJetPt = fs->make<TH1D>("leadJetPt","lead jet pt",500,0,500);
  nextJetPt = fs->make<TH1D>("2ndJetPt","2nd jet pt",500,0,500); 

  leadJetSPt = fs->make<TH1F>("leadJetSPt","lead jet smeared pt",500,0,500);
  nextJetSPt = fs->make<TH1F>("2ndJetSPt","2nd jet smeared pt",500,0,500);

  bJetSPt = fs->make<TH1F>("bJetSPt","b-jet smeared pt",500,0,500);
  lJetSPt = fs->make<TH1F>("lJetSPt","light jet smeared pt",500,0,500);
  lJetRMS = fs->make<TH1F>("lJetRMS","light jet RMS",200,0,0.1);

  leadJetPUmva = fs->make<TH1F>("leadJetPUmva","lead jet pu mva",200,0,1);
  nextJetPUmva = fs->make<TH1F>("nextJetPUmva","next jet pu mva",200,0,1);
  vetoJetPUmva = fs->make<TH1F>("vetoJetPUmva","veto jet pu mva",200,0,1);
  vetoJetRMS = fs->make<TH1F>("vetoJetRMS","veto jet pu mva",500,0,1);

  numJets = fs->make<TH1I>("numJets","num jets",10,0,10);   
  numJetsLB = fs->make<TH1I>("numJetsLB","num jets",10,0,10); 

  mtWmet = fs->make<TH1D>("mtWmet","MtW from met",500,0,500); 
  met = fs->make<TH1D>("met","MET",500,0,500);
  mtWmet_f = fs->make<TH1D>("mtWmet_f","MtW from met",500,0,500);
  met_f = fs->make<TH1D>("met_f","MET",500,0,500);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
SingleTopFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
SingleTopFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
SingleTopFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
SingleTopFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
SingleTopFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SingleTopFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(SingleTopFilter);
