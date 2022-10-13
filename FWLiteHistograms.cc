//--Developed by Ryan Hoang
//-------------------------
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h" 
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/HepMCCandidate/interface/PdfInfo.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
#include "PhysicsTools/HepMCCandAlgos/interface/GenParticlesHelper.h"

#include "TTree.h"
#include "TNtuple.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

using namespace std;
using namespace edm;

//template <typename T>
using pat::Muon;

string highestPtCombination(float mmPt, float eePt, float emPt) {
  string result = "";
  if(mmPt > eePt && mmPt > emPt) {
    result = "mm";
  }
  else if(eePt > mmPt && eePt > emPt) {
    result = "ee";
  }
  else if(emPt > mmPt && emPt > eePt) {
    result = "em";
  }
  
  if(mmPt == eePt && mmPt == emPt) {
    result = "invalid";
  }
  return result; 
}

Double_t deltaRvalue(Double_t eta1, Double_t eta2, Double_t phi1, Double_t phi2) {
  Double_t etadiff = eta1 - eta2;
  Double_t etadiff2 = etadiff * etadiff;
  Double_t phidiff = phi1 - phi2;
  Double_t phidiff2 = phidiff * phidiff;

  return TMath::Sqrt(etadiff2 + phidiff2);
}

int main(int argc, char* argv[]) {
  // define what particle you are using; this is necessary as FWLite is not capable of reading edm::Views
  //-- bring whole std class into the scope
  using namespace std;
  using namespace edm;
  using namespace reco;
  using namespace pat;

  using pat::Muon;
  using pat::Electron;
  using pat::Tau;
  using pat::Jet;
  using pat::MET;

  int num0 = 0;
  int num1 = 0;

  int eenum0 = 0;
  int eenum1 = 0;

  int mm = 0;
  int ee = 0;
  int em = 0;
  int invalid = 0;

  int bFound = 0;

  int matched = 0;
  int matchedInLoop = 0;

  int wMother = 0;

  int muoGenJet = 0;
  int muojet = 0;
  
  // ---------------------upcoming-----------------------------------------
  //  * enable FWLite 
  //  * book the histograms of interest 
  //  * open the input file
  // ----------------------------------------------------------------------

  //-- loading framework libraries 
  gSystem->Load("libFWCoreFWLite");
  FWLiteEnabler::enable();
  //---------
  // :: used to access var/func inside a class 
  // FWLiteEnabler::enable()
  // class --------- function
  //-------

  //-- init command line parser 
  optutl::CommandLineParser parser ("Analyze FWLite Histograms");

  //-- set default values 
  parser.integerValue("maxEvents") = 1000;
  parser.integerValue("outputEvery") = 10;
  parser.stringValue("outputFile") = "analyzeFWLiteHistograms.root";
  //parser.stringValue("outputNtuple") = "outputNtuple.root";

  //-- parser arguments 
  parser.parseArguments(argc, argv);
  int maxEvents_ = parser.integerValue("maxEvents");
  unsigned int outputEvery_ = parser.integerValue("outputEvery");
  string outputFile_ = parser.stringValue("outputFile");
  vector<string> inputFiles_ = parser.stringVector("inputFiles");
  string outputNtuple_ = parser.stringValue("outputNtuple");

  //-- book a set of histograms 
  fwlite::TFileService fs = fwlite::TFileService(outputFile_);
  TFileDirectory dir = fs.mkdir("analyzeBasicPat");

  //-- numbers are subjected to change 
  //----------------------------object----property---buckets--start--end
  TH1F* muonPt_ = dir.make<TH1F>("muonPt", "pt", 100, 0., 300.);
  TH1F* muonEta_ = dir.make<TH1F>("muonEta", "eta", 100,  -3.,  3.);
  TH1F* muonPhi_ = dir.make<TH1F>("muonPhi", "phi", 100,  -5.,  5.);  
  TH1F* muoniso_ = dir.make<TH1F>("muoniso", "iso_", 100,  -5., 5.);
  TH1F* muoniso_SEL_ = dir.make<TH1F>("muoniso_SEL", "iso", 100, -5., 5.);
  TH1F* muonVX_ = dir.make<TH1F>("muonVX", "vx",  100,  -0.5,  0.5);
  TH1F* muonVY_ = dir.make<TH1F>("muonVY", "vy",  100,  -0.5,  0.5);
  TH1F* muonVZ_ = dir.make<TH1F>("muonVZ", "vz",  100,  -30.,  30.);

  TH1F* Nmuons_all_ = dir.make<TH1F>("Nmuons_all", "N",   11,  0.,  11.);
  TH1F* Nmuons_mumuSEL_ = dir.make<TH1F>("Nmuons_mumuSEL", "N", 11,  0.,  11.);
  TH1F* MET_mumuSEL_ = dir.make<TH1F>("MET_mumuSEL", "N", 100, 0., 2400.);
  //TH1F* MET_all_ = dir.make<TH1F>("MET_all", "N", 100, 0., 300.);

  //--electron
  TH1F* elecPt_  = dir.make<TH1F>("elecPt", "pt",   100,   0., 300.);
  TH1F* elecEta_ = dir.make<TH1F>("elecEta", "eta", 100,  -3., 3.);
  TH1F* elecPhi_ = dir.make<TH1F>("elecPhi", "phi", 100,  -5., 5.);
  TH1F* eleciso_ = dir.make<TH1F>("eleciso", "iso_", 100, -5., 5.);
  //TH1F* eleciso_SEL_ = dir.make<TH1F>("eleciso_SEL", "iso", 100, -5., 5.);
  TH1F* elecVX_ = dir.make<TH1F>("elecVX", "vx", 100,  -0.5, 0.5);
  TH1F* elecVY_ = dir.make<TH1F>("elecVY", "vy", 100,  -0.5, 0.5);
  TH1F* elecVZ_ = dir.make<TH1F>("elecVZ", "vz", 100,  -30., 30.);
  //TH1F* eeMass_= dir.make<TH1F>("eeMass", "mass", 90,   30., 120.);
  TH1F* Nelectrons_all_ = dir.make<TH1F>("Nelectrons_all", "N", 11, 0., 11.);
  TH1F* Nelectrons_eeSEL_ = dir.make<TH1F>("Nelectrons_eeSEL", "N", 11,  0.,  11.);
  TH1F* MET_eeSEL_ = dir.make<TH1F>("MET_eeSEL", "N", 100, 0., 2400.);

  //--electron Muon 
  TH1F* elec_muonPt_ = dir.make<TH1F>("elec_muonPt", "pt", 100, 0., 300.);
  //TH1F* elec_muonPt_SEL = dir.make<TH1F>("elec_muonPt_SEL", "pt", 100, 0., 300.);
  TH1F* elec_muonEta_ = dir.make<TH1F>("elec_muonEta", "eta", 100,  -3.,  3.);
  TH1F* elec_muonPhi_ = dir.make<TH1F>("elec_muonPhi", "phi", 100,  -5.,  5.);  
  //TH1F* elec_muoniso_ = dir.make<TH1F>("elec_muoniso", "iso_", 100,  -5., 5.);
  //TH1F* elec_muoniso_SEL_ = dir.make<TH1F>("elec_muoniso_SEL", "iso", 100, -5., 5.);
  TH1F* elec_muonVX_ = dir.make<TH1F>("elec_muonVX", "vx",  100,  -0.5,  0.5);
  TH1F* elec_muonVY_ = dir.make<TH1F>("elec_muonVY", "vy",  100,  -0.5,  0.5);
  TH1F* elec_muonVZ_ = dir.make<TH1F>("elec_muonVZ", "vz",  100,  -30.,  30.);
  TH1F* MET_emuSEL_  = dir.make<TH1F>("MET_emuSEL", "N",    100,  0.,  2400.);

  //-- Test sorting algorithm 
  //TH1F* isSortMuon_ = dir.make<TH1F>("isSortMuon", "Muon?", 2, 0., 2.);
  //TH1F* isSortElectron_ = dir.make<TH1F>("isSortElectron", "Electron?", 2, 0., 2.);

  //--muon before the selection
  TH1F* before_muonPt_ = dir.make<TH1F>("before_muonPt", "pt", 100, 0., 300.);
  TH1F* before_muonEta_ = dir.make<TH1F>("before_muonEta", "eta", 100,  -3.,  3.);
  TH1F* before_muonPhi_ = dir.make<TH1F>("before_muonPhi", "phi", 100,  -5.,  5.);  
  TH1F* before_muonVX_ = dir.make<TH1F>("before_muonVX", "vx",  100,  -0.5,  0.5);
  TH1F* before_muonVY_ = dir.make<TH1F>("before_muonVY", "vy",  100,  -0.5,  0.5);
  TH1F* before_muonVZ_ = dir.make<TH1F>("before_muonVZ", "vz",  100,  -30.,  30.);

  //--Jet
  TH1F* jetPt_ = dir.make<TH1F>("jetPt", "pt", 100, 0., 300.);
  TH1F* jetEta_ = dir.make<TH1F>("jetEta", "eta", 100,  -3.,  3.);
  TH1F* jetPhi_ = dir.make<TH1F>("jetPhi", "phi", 100,  -5.,  5.);  
  TH1F* jetVX_ = dir.make<TH1F>("jetVX", "vx",  100,  -0.5,  0.5);
  TH1F* jetVY_ = dir.make<TH1F>("jetVY", "vy",  100,  -0.5,  0.5);
  TH1F* jetVZ_ = dir.make<TH1F>("jetVZ", "vz",  100,  -30.,  30.);
  TH1F* Njets_all_ = dir.make<TH1F>("Njets_all_", "Njets", 11, 0., 11.); 

  //--AK8 Jets
  TH1F* AK8_jetPt_  = dir.make<TH1F>("AK8_jetPt", "pt",   100,   0., 300.);
  TH1F* AK8_jetEta_ = dir.make<TH1F>("AK8_jetEta", "eta", 100,  -3.,   3.);
  TH1F* AK8_jetPhi_  = dir.make<TH1F>("AK8_jetPhi", "phi",  100, -5., 5.);
  TH1F* AK8_jetVX_ = dir.make<TH1F>("AK8_jetVX", "vx",  100,  -0.5,  0.5);
  TH1F* AK8_jetVY_ = dir.make<TH1F>("AK8_jetVY", "vy",  100,  -0.5,  0.5);
  TH1F* AK8_jetVZ_ = dir.make<TH1F>("AK8_jetVZ", "vz",  100,  -0.5,  0.5);
  TH1F* AK8_Njets_all_ = dir.make<TH1F>("AK8_Njets_all_", "AK8_Njets", 11, 0., 11.);
  //--
  TH1F* AK8_Njets_ee_ = dir.make<TH1F>("AK8_Njets_ee_", "AK8_Njets_ee", 11, 0., 11.);
  TH1F* AK8_Njets_mm_ = dir.make<TH1F>("AK8_Njets_mm_", "AK8_Njets_mm", 11, 0., 11.);
  TH1F* AK8_Njets_em_ = dir.make<TH1F>("AK8_Njets_em_", "AK8_Njets_em", 11, 0., 11.);

  TH1F* DeltaR_elec_ = dir.make<TH1F>("DeltaR_Elec", "R", 100, 0., 10.);
  TH1F* DeltaR_muon_ = dir.make<TH1F>("DeltaR_Muon", "R", 100, 0., 10.);

  TH1F* N_Gen_b_ = dir.make<TH1F>("Generator_b", "number", 15, 0., 15.);

  //--2D plot
  TH2F* MET_eeSel_Jet_ = dir.make<TH2F>("MET_eeSel_Jet_", "eeMET_Njets", 100,  0.,  2500., 11, 0 , 11);
  TH2F* MET_mumuSel_Jet_ = dir.make<TH2F>("MET_mumuSel_Jet_", "mumuMET_Njets", 100,  0.,  2500., 11, 0 , 11);  

  //-NTuple file/branches
  TFile* ofile = new TFile(outputNtuple_.c_str(),"RECREATE");

  Int_t Nee;
  TNtuple* ee_Branch = new TNtuple("ee_Branch", "Example N-Tuple", 
  "pt1:eta1:phi1:vx1:vy1:pt2:eta2:phi2:vx2:vy2:Nj:Nak8j:missET");

  Int_t Nmm;
  TNtuple* mm_Branch = new TNtuple("mm_Branch", "Example N-Tuple",
  "pt1:eta1:phi1:vx1:vy1:pt2:eta2:phi2:vx2:vy2:Nj:Nak8j:missET");

  Int_t Nem;
  TNtuple* em_Branch = new TNtuple("em_Branch", "Example N-Tuple",
  "pt1:eta1:phi1:vx1:vy1:pt2:eta2:phi2:vx2:vy2:Nj:Nak8j:missET");

  //--Implement b-tagging
  // enum Flavour {
  //   ALL_JETS = 0,
  //   UDSG_JETS,
  //   C_JETS,
  //   B_JETS,
  //   NONID_JETS,
  //   N_JET_TYPES
  // };

  //TH1* flavours_;

  // struct Plots {
  //   TH1 *discrTC, *discrSSV, *discrCSV;
  // } plots_[N_JET_TYPES];
  //--

  //-- loop through the events 
  int ievt = 0;
  for(unsigned int iFile = 0; iFile < inputFiles_.size(); iFile++) {
    //-- open input file (can be located on castor)
    TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    if(inFile) {
      // ----------------------------------------------------------
      // Second Part: 
      //
      //  * loop the events in the input file 
      //  * receive the collections of interest via fwlite::Handle
      //  * fill the histograms
      //  * after the loop close the input file
      // -----------------------------------------------------------
      fwlite::Event ev(inFile);

      for(ev.toBegin(); !ev.atEnd(); ++ev, ++ievt) {
        // int& -> reference assign value
        EventBase const& event = ev;

        //--break loop if maximal number of events is reached 
        if(maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false) break;
        //--simple event counter
        if(outputEvery_ != 0 ? (ievt > 0 && ievt % outputEvery_ == 0) : false) {
          cout << " processing event: " << ievt << endl;
        }
        //-- Handle particle collection
        Handle<vector<Muon>> muons;
        event.getByLabel(string("slimmedMuons"), muons);

        Handle<vector<Electron>> electrons;
        event.getByLabel(string("slimmedElectrons"), electrons);

        Handle<vector<Jet>> jets;
        event.getByLabel(string("slimmedJets"), jets);

        Handle<vector<Jet>> AK8jets;
        event.getByLabel(string("slimmedJetsAK8"), AK8jets);

        //-- met?
        Handle<vector<MET>> mets;
        event.getByLabel(string("slimmedMETs"), mets);

        // Handle to the genparticle collection
        Handle<vector<GenParticle>> genParticles;
        event.getByLabel(string("prunedGenParticles"), genParticles);

        Int_t runnum = event.id().run();
        Int_t evnum = event.id().event();
        ev.id().run();
        ev.id().event();

        //--loop MUON collection and fill histograms 
        int n_muons = 0;
        int diMuon = 0;

        //-- b in an event
        int b = 0;
        int b_pair = 0;

        //-- gen b in an event 
        int gen_b = 0;

        //-- selected object for NTuple
        vector<Muon>::const_iterator smu1;
	      vector<Muon>::const_iterator smu2;
	      vector<Electron>::const_iterator se1;
	      vector<Electron>::const_iterator se2;
      	vector<Muon>::const_iterator smu;
	      vector<Electron>::const_iterator se;

        for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
          if(abs(jet->hadronFlavour()) == 5) {
            b++;
          }
        }
        bFound += b; 

        for(vector<Jet>::const_iterator jet1 = jets->begin(); jet1 != jets->end(); jet1++) {
          for(vector<Jet>::const_iterator jet2 = jets->begin(); jet2 != jets->end(); jet2++) {
            if(jet2 > jet1) {
              //-- b-tag
              if(abs(jet1->hadronFlavour()) == 5 && abs(jet2->hadronFlavour()) == 5) {
                //--opposite charge
                if(jet1->charge() * jet2->charge() < 0 || b > 1) {
                  b_pair++;
                }
              }
            }
          }
        }

        //--at least 2 b tag w/ opposite sign  
        if(true) {//b_pair > 0) {
          float mmSumPt = -666.0;
          for(vector<Muon>::const_iterator mu1 = muons->begin(); mu1 != muons->end(); mu1++) {
            //--plotting
            before_muonPt_->Fill(mu1->pt());
            before_muonEta_->Fill(mu1->eta());
            before_muonPhi_->Fill(mu1->phi());	
            before_muonVX_->Fill(mu1->vx());
            before_muonVY_->Fill(mu1->vy());
            before_muonVZ_->Fill(mu1->vz());
          }
          
          int n_ak8_mm = 0;
          //-- get 2 highest pt and oposite charges 
          for(vector<Muon>::const_iterator mu1 = muons->begin(); mu1 != muons->end(); mu1++) {
            //-- high Pt
            if(mu1->pt() > 20 && fabs(mu1->eta()) < 2.4 && mu1->isolationR03().sumPt < 0.1) { 
              n_muons++;
              for(vector<Muon>::const_iterator mu2 = muons->begin(); mu2 != muons->end(); mu2++) {
                //-- next index
                if(mu2 > mu1) {
                  if(mu2->pt() > 20 && fabs(mu2->eta()) < 2.4 && mu2->isolationR03().sumPt < 0.1) { 
                    //--check sort 
                    if(mu1->pt() > mu2->pt()) {
                      num0++;
                    }
                    else {
                      num1++;
                    }
                    //-- opposite charge
                    if(mu1->charge() * mu2->charge() < 0) {
                      Double_t deltaR = deltaRvalue(mu1->eta(), mu2->eta(), mu1->phi(), mu2->phi());
                      if(deltaR > 0.3) {
                        //-- vs jet pat delta R
                        for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
                        Double_t muon1jet = deltaRvalue(mu1->eta(), jet->eta(), mu1->phi(), jet->phi());
                        Double_t muon2jet = deltaRvalue(mu2->eta(), jet->eta(), mu2->phi(), jet->phi());

                        //-- cut that matched 
                          if(muon1jet > 0.2 && muon2jet > 0.2) {
                            //muojet++;
                            DeltaR_muon_->Fill(deltaR);

                            diMuon++;
                          
                            muonPt_->Fill(mu1->pt());
                            muonEta_->Fill(mu1->eta());
                            muonPhi_->Fill(mu1->phi());	
                            muonVX_->Fill(mu1->vx());
                            muonVY_->Fill(mu1->vy());
                            muonVZ_->Fill(mu1->vz());

                            muonPt_->Fill(mu2->pt());
                            muonEta_->Fill(mu2->eta());
                            muonPhi_->Fill(mu2->phi());	
                            muonVX_->Fill(mu2->vx());
                            muonVY_->Fill(mu2->vy());
                            muonVZ_->Fill(mu2->vz());

                            MET_mumuSEL_->Fill((mets->front()).sumEt());


                            smu1 = mu1;
                            smu2 = mu2;

                            mmSumPt = mu1->pt() + mu2->pt();

                            for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
                              if(jet->pt() > 20 && fabs(jet->eta()) < 2.4) {
                                n_ak8_mm++;
                              }
                            }
                            AK8_Njets_mm_->Fill(n_ak8_mm);

                            for (vector<GenParticle>::const_iterator gp = genParticles->begin(); gp != genParticles->end(); ++gp) {
                              const Candidate *p = (const Candidate*)&(*gp);
                              //-- vs muon gen delta R
                              if(abs(p->pdgId()) == 13) {

                                Double_t x = deltaRvalue(mu1->eta(), p->eta(), mu1->phi(), p->phi());
                                Double_t y = deltaRvalue(mu2->eta(), p->eta(), mu2->phi(), p->phi());

                                if(x < 0.15) {
                                  matchedInLoop++;
                                }
                                if(y < 0.15) {
                                  matchedInLoop++;
                                }
                              }
                            }
                            break;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          Nmuons_all_->Fill(n_muons);
          Nmuons_mumuSEL_->Fill(diMuon);
          

          //-- loop ELECTRON collections
          int n_electrons = 0;
          int diElectron = 0;
          int n_ak8_ee = 0;

          float eeSumPt = -666.0;
          for(vector<Electron>::const_iterator e1 = electrons->begin(); e1 != electrons->end(); e1++) {
            //-- high pt 
            if(e1->pt() > 20 && fabs(e1->eta()) < 2.4 && e1->dr03TkSumPt() < 0.1) { 
              for(vector<Electron>::const_iterator e2 = electrons->begin(); e2 != electrons->end(); e2++) {
                //--next index 
                if(e2 > e1) {
                  if(e2->pt() > 20 && fabs(e2->eta()) < 2.4 && e2->dr03TkSumPt() < 0.1) {
                    //--check sort 
                    if(e1->pt() > e2->pt()) {
                      eenum0++;
                    }
                    else {
                      eenum1++;
                    }
                    //--check opposite charge 
                    if(e1->charge() * e2->charge() < 0) {
                      Double_t deltaR = deltaRvalue(e1->eta(), e2->eta(), e1->phi(), e2->phi());
                      if(deltaR > 0.3) {
                        //-- vs jet pat delta R
                        for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
                          Double_t e1jet = deltaRvalue(e1->eta(), jet->eta(), e1->phi(), jet->phi());
                          Double_t e2jet = deltaRvalue(e2->eta(), jet->eta(), e2->phi(), jet->phi());
                          if(e1jet > 0.2 && e2jet > 0.2) {
                            diElectron++;

                            elecPt_->Fill(e1->pt());
                            elecEta_->Fill(e1->eta());
                            elecPhi_->Fill(e1->phi());	
                            elecVX_->Fill(e1->vx());
                            elecVY_->Fill(e1->vy());
                            elecVZ_->Fill(e1->vz());
                            eleciso_->Fill(e1->dr03TkSumPt());
                                  
                            elecPt_->Fill(e2->pt());
                            elecEta_->Fill(e2->eta());
                            elecPhi_->Fill(e2->phi());	
                            elecVX_->Fill(e2->vx());
                            elecVY_->Fill(e2->vy());
                            elecVZ_->Fill(e2->vz());
                            eleciso_->Fill(e2->dr03TkSumPt());

                            MET_eeSEL_->Fill((mets->front()).sumEt());


                            se1 = e1;
                            se2 = e2;

                            eeSumPt = e1->pt() + e2->pt();

                            Double_t del = deltaRvalue(e1->eta(), e2->eta(), e1->phi(), e2->phi());

                            for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
                              if(jet->pt() > 20 && fabs(jet->eta()) < 2.4) {
                                n_ak8_ee++;
                              }
                            }
                            AK8_Njets_ee_->Fill(n_ak8_ee);
                            MET_eeSel_Jet_->Fill((mets->front()).sumEt(), n_ak8_ee);

                            if(del > 2.4) {
                              DeltaR_elec_->Fill(del);
                            }
                            break;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          Nelectrons_all_->Fill(n_electrons);
          Nelectrons_eeSEL_->Fill(diElectron);
          
          
          //-- loop electron and muon collection 
          int diElecMuon = 0;
          float emSumPt = -666.0;
          int n_ak8_em = 0;
          for(vector<Electron>::const_iterator e = electrons->begin(); e != electrons->end(); e++) {
            //-- high pt 
            if(e->pt() > 20 && fabs(e->eta()) < 2.4 && e->dr03TkSumPt() < 0.1) { 
              //--check muon
              for(vector<Muon>::const_iterator mu = muons->begin(); mu != muons->end(); mu++) {
                //--high Pt
                if(mu->pt() > 20 && fabs(mu->eta()) < 2.4 && mu->isolationR03().sumPt < 0.1) {
                  //--check opposite charge 
                  if(e->charge() * mu->charge() < 0) {
                    //-- cut things in the same direction as the jets
                    for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
                      Double_t muonjet = deltaRvalue(mu->eta(), jet->eta(), mu->phi(), jet->phi());
                      if(muonjet > 0.2) {
                        diElecMuon++;

                        elec_muonPt_->Fill(e->pt());
                        elec_muonEta_->Fill(e->eta());
                        elec_muonPhi_->Fill(e->phi());	
                        elec_muonVX_->Fill(e->vx());
                        elec_muonVY_->Fill(e->vy());
                        elec_muonVZ_->Fill(e->vz());

                        elec_muonPt_->Fill(mu->pt());
                        elec_muonEta_->Fill(mu->eta());
                        elec_muonPhi_->Fill(mu->phi());	
                        elec_muonVX_->Fill(mu->vx());
                        elec_muonVY_->Fill(mu->vy());
                        elec_muonVZ_->Fill(mu->vz());
                        
                        MET_emuSEL_->Fill((mets->front()).sumEt());

                        smu = mu;
                        se = e;
                        
                        emSumPt = e->pt() + mu->pt();

                        for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
                          if(jet->pt() > 20 && fabs(jet->eta()) < 2.4) {
                            n_ak8_em++;
                          }
                        }
                        AK8_Njets_em_->Fill(n_ak8_em);
                        
                        break;
                      }
                    }
                  }
                }
              }
            }
          }
          

          //--JET LOOP
          int n_jets = 0;
          for(vector<Jet>::const_iterator j = jets->begin(); j != jets->end(); j++) {
            if(j->pt() > 20 && fabs(j->eta()) < 2.4) {
              n_jets++;

              jetPt_->Fill(j->pt());
              jetEta_->Fill(j->eta());
              jetPhi_->Fill(j->phi());
              jetVX_->Fill(j->vx());
              jetVY_->Fill(j->vy());
              jetVZ_->Fill(j->vz());
            }
          }
          Njets_all_->Fill(n_jets);

          //-- AK8 LOOP
          int n_ak8 = 0;
          for(vector<Jet>::const_iterator ak8j1 = jets->begin(); ak8j1 != jets->end(); ak8j1++) {
            if(ak8j1->pt() > 20 && fabs(ak8j1->eta()) < 2.4) {
              n_ak8++;

              AK8_jetPt_->Fill(ak8j1->pt ());
              AK8_jetEta_->Fill(ak8j1->eta());
              AK8_jetPhi_->Fill(ak8j1->phi());
              AK8_jetVX_->Fill(ak8j1->vx());
              AK8_jetVY_->Fill(ak8j1->vy());
              AK8_jetVZ_->Fill(ak8j1->vz());
              
            }
          }
          AK8_Njets_all_->Fill(n_ak8);

          //-- B TAGGING
          // book histograms for all jet flavours
          //for(vector<Jet>::const_iterator jet = jets->begin(); jet != jets->end(); jet++) {
            //--only look at jets that pass the pt and eta cut
            //if(jet->pt() < 30 && abs(jet->eta()) > 2.4) {
              //continue;
              //if(abs(jet->hadronFlavour()) == 5) {
              //  bFound++;
              //}
            //}

            // Flavour flavour;
            // //-- find out the jet flavour (differ between quark and anti quark)
            // switch(abs(jet->partonFlavour())) {
            //   case 1:
            //   case 2:
            //   case 3:
            //   case 21:
            //     flavour = UDSG_JETS;
            //     break;
            //   case 4:
            //     flavour = C_JETS;
            //     break;
            //   case 5:
            //     flavour = B_JETS;
            //     break;
            //   default:
            //     flavour = NONID_JETS;
            // }

            //-- simply count the number of accepted jets 
            // flavours_->Fill(ALL_JETS);
            // flavours_->Fill(flavour);
            
            // cout << "ALL JETS : " << ALL_JETS << endl;
            // cout << "FLAVOUR : " << flavour << endl;

            // double discrTC = jet->bDiscriminator("trackCountingHighEffBJetTags");
            // double discrSSV = jet->bDiscriminator("simpleSecondaryVertexBJetTags");
            // double discrCSV = jet->bDiscriminator("combinedSecondaryVertexBJetTags");

            // cout << "discrTC = " << discrTC << endl;
            // cout << "discrSSV = " << discrSSV << endl;
            // cout << "discrCSV = " << discrCSV << endl;

          //}

          //- find b in generator
          // for (vector<GenParticle>::const_iterator gp = genParticles->begin(); gp != genParticles->end(); ++gp) {
          //   const Candidate *p = (const Candidate*)&(*gp);
            
          //   if(p->pdgId() == 5 || p->pdgId() == -5) {
          //     bFound++;
          //   }
          // }

          //--2D plot
          // for(vector<Electron>::const_iterator e = electrons->begin(); e != electrons->end(); e++) {
          //   //-- high pt
          //   if(e->pt() > 20 && fabs(e->eta()) < 2.4 && e->dr03TkSumPt() < 0.1) {
          //     //--check muon
          //     for(vector<Muon>::const_iterator mu = muons->begin(); mu != muons->end(); mu++) {
          //       //--high Pt
          //       if(mu->pt() > 20 && fabs(mu->eta()) < 2.4 && mu->isolationR03().sumPt < 0.1) {
          //         //--Check Jets
          //         int n_jet = 0;
          //         for(vector<Jet>::const_iterator j1 = jets->begin(); j1 != jets->end(); j1++){
          //           if(j1->pt() > 20 && fabs(j1->eta()) < 2.4){
          //             n_jet++;
          //           }
          //           MET_eeSel_Jet_->Fill((mets->front()).sumEt(), n_jet);
          //           MET_mumuSel_Jet_->Fill((mets->front()).sumEt(), n_jet);
          //         }
          //       }
          //     }
          //   }
          // }

          //-- for MCTruthDeltaRMatcher muons
          for (vector<GenParticle>::const_iterator gp = genParticles->begin(); gp != genParticles->end(); ++gp) {
            const Candidate *p = (const Candidate*)&(*gp); 
            //-- muons
            if(p->pdgId() == 13) {
              const Candidate *mom = p->mother();
              if(abs(mom->pdgId()) == 24) {
                wMother++;
              }
            }
          }
          
          // loop tyhorugh 2 hiest pat and compare them to get the angle between 1 vs gen particle (same type) if the angle smaller than 0.2 -> matched and then find their parent W or not?
          //-- highest ee, m , em event
          string highest = highestPtCombination(mmSumPt, eeSumPt, emSumPt);
          if(highest == "mm") {
            mm++;
            mm_Branch->Fill(smu1->pt(),smu1->eta(),smu1->phi(),smu1->vx(),smu1->vy(),smu2->pt(),smu2->eta(),smu2->phi(),smu2->vx(),smu2->vy(),n_jets,n_ak8_mm,(mets->front()).sumEt());
          }
          else if(highest == "ee") {
            ee++;
            ee_Branch->Fill(se1->pt(),se1->eta(),se1->phi(),se1->vx(),se1->vy(),se2->pt(),se2->eta(),se2->phi(),se2->vx(),se2->vy(),n_jets,n_ak8_ee,(mets->front()).sumEt());
          }
          else if(highest == "em") {
            em++;
            em_Branch->Fill(se->pt(),se->eta(),se->phi(),se->vx(),se->vy(),smu->pt(),smu->eta(),smu->phi(),smu->vx(),smu->vy(),n_jets,n_ak8_em,(mets->front()).sumEt());    
          }
          else if(highest == "invalid") {
            invalid++;
          }

          if(highest != "invalid") {
            for (vector<GenParticle>::const_iterator gp = genParticles->begin(); gp != genParticles->end(); ++gp) {
            const Candidate *p = (const Candidate*)&(*gp);
            
              if(p->pdgId() == 5 || p->pdgId() == -5) {
                //bFound++;
                gen_b++;
              }
              N_Gen_b_->Fill(gen_b);
            }
          }
        }
      }
      ofile->Write();
      ofile->Close();
      //--close input file
      inFile->Close();
    }
    //--break loop if maximal number of events is reached 
    //--this has to be done twice to stop the file loop
    if(maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false) break;
  }
  cout << "Number of 0 as for muon (sorted high-low):  " << num0 << endl;
  cout << "Number of 1 as for muon (sorted low-high):  " << num1 << endl;

  cout << "Number of 0 as for electron (sorted high-low): " << eenum0 << endl;
  cout << "Number of 1 as for electron (sorted low-high): " << eenum1 << endl;

  cout << "--------" << endl;

  cout << "Total Events: " << ievt << endl;
  cout << "Total Survived Events: " << mm + ee + em << endl;

  cout << "--------" << endl;

  cout << "Number of mm events: " << mm << endl;
  cout << "Number of ee events: " << ee << endl;
  cout << "Number of em events: " << em << endl;
  cout << "Number of invalid events: " << invalid << endl;

  cout << "--------" << endl;

  cout << "Number of b found: " << bFound << endl;

 // cout << "Number of b minus: " << btest << endl;

 // cout << "Matched Muons: " << matched << endl;

  cout << "Matched Muons in loop : " << matchedInLoop << endl;

  cout << "--------" << endl;

  cout << "Number of W mother from muons: " << wMother << endl;

  // cout << "Muon Gen Jet delta R: " << muoGenJet << endl;

  // cout << "Muon Jet delta R:" << muojet << endl;

  return 0;
}

