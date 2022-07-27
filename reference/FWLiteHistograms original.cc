#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TTree.h"
#include "TNtuple.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/HepMCCandidate/interface/PdfInfo.h"

int main(int argc, char* argv[]) 
{
  // define what muon you are using; this is necessary as FWLite is not 
  // capable of reading edm::Views
  using pat::Muon;
  using pat::Electron;
  using pat::Tau;
  using pat::Jet;
  using pat::MET;
  using namespace std;
  using namespace pat;
  using namespace edm;
  using namespace reco;

  // ----------------------------------------------------------------------
  // First Part: 
  //
  //  * enable FWLite 
  //  * book the histograms of interest 
  //  * open the input file
  // ----------------------------------------------------------------------

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  FWLiteEnabler::enable();

  // initialize command line parser
  optutl::CommandLineParser parser ("Analyze FWLite Histograms");

  // set defaults
  parser.integerValue ("maxEvents"  ) = 1000;
  parser.integerValue ("outputEvery") =   10;
  parser.stringValue  ("outputFile" ) = "analyzeFWLiteHistograms.root";
  parser.stringValue  ("outputNtuple" ) = "outputNtuple.root";
  // parse arguments
  parser.parseArguments (argc, argv);
  int maxEvents_ = parser.integerValue("maxEvents");
  unsigned int outputEvery_ = parser.integerValue("outputEvery");
  std::string outputFile_ = parser.stringValue("outputFile");
  std::vector<std::string> inputFiles_ = parser.stringVector("inputFiles");
  std::string outputNtuple_ = parser.stringValue("outputNtuple");
  // book a set of histograms
  fwlite::TFileService fs = fwlite::TFileService(outputFile_);
  TFileDirectory dir = fs.mkdir("analyzeBasicPat");
  
  TH1F* muonPt_  = dir.make<TH1F>("muonPt"  , "pt"  ,   100,   0., 300.);
  TH1F* muonPt_SEL  = dir.make<TH1F>("muonPt_SEL"  , "pt"  ,   100,   0., 300.);
  TH1F* muonEta_ = dir.make<TH1F>("muonEta" , "eta" ,   100,  -3.,   3.);
  TH1F* muonPhi_ = dir.make<TH1F>("muonPhi" , "phi" ,   100,  -5.,   5.);  
  TH1F* muoniso_ = dir.make<TH1F>("muoniso" , "iso_" ,   100,  -5.,   5.);
  TH1F* muoniso_SEL_ = dir.make<TH1F>("muoniso_SEL" , "iso" ,   100,  -5.,   5.);
  TH1F* muonVX_ = dir.make<TH1F>("muonVX" , "vx" ,   100,  -0.5,   0.5);
  TH1F* muonVY_ = dir.make<TH1F>("muonVY" , "vy" ,   100,  -0.5,   0.5);
  TH1F* muonVZ_ = dir.make<TH1F>("muonVZ" , "vz" ,   100,  -30.,   30.);

  TH1F* mumuMass12_= dir.make<TH1F>("mumuMass12", "mass",    90,  60.,  120.);
  TH1F* mumuMass34_= dir.make<TH1F>("mumuMass34", "mass",    90,  60.,  120.);
  TH1F* mumuMass13_= dir.make<TH1F>("mumuMass13", "mass",    90,  60.,  120.);
  TH1F* mumuMass24_= dir.make<TH1F>("mumuMass24", "mass",    90,  60.,  120.);
  TH1F* mumuMass23_= dir.make<TH1F>("mumuMass23", "mass",    90,  60.,  120.);
  TH1F* mumuMass14_= dir.make<TH1F>("mumuMass14", "mass",    90,  60.,  120.);
  TH1F* Nmuons_all_ = dir.make<TH1F>("Nmuons_all", "N",    11,  0.,  11.);
  TH1F* Nmuons_mumuSEL_ = dir.make<TH1F>("Nmuons_mumuSEL", "N",    11,  0.,  11.);
  TH1F* MET_mumuSEL_ = dir.make<TH1F>("MET_mumuSEL", "N",    100,  0.,  2400.);
  TH1F* MET_all_ = dir.make<TH1F>("MET_all", "N",    100,  0.,  300.);
  TH1F* elecPt_  = dir.make<TH1F>("elecPt"  , "pt"  ,   100,   0., 300.);
  TH1F* elecEta_ = dir.make<TH1F>("elecEta" , "eta" ,   100,  -3.,   3.);
  TH1F* elecPhi_ = dir.make<TH1F>("elecPhi" , "phi" ,   100,  -5.,   5.);
  TH1F* eleciso_ = dir.make<TH1F>("eleciso" , "iso_" ,   100,  -5.,   5.);
  TH1F* eleciso_SEL_ = dir.make<TH1F>("eleciso_SEL" , "iso" ,   100,  -5.,   5.);
  TH1F* elecVX_ = dir.make<TH1F>("elecVX" , "vx" ,   100,  -0.5,   0.5);
  TH1F* elecVY_ = dir.make<TH1F>("elecVY" , "vy" ,   100,  -0.5,   0.5);
  TH1F* elecVZ_ = dir.make<TH1F>("elecVZ" , "vz" ,   100,  -30.,   30.);
  TH1F* eeMass_= dir.make<TH1F>("eeMass", "mass",    90,  30.,  120.);
  TH1F* Nelectrons_all_ = dir.make<TH1F>("Nelectrons_all", "N",    11,  0.,  11.);
  TH1F* Nelectrons_eeSEL_ = dir.make<TH1F>("Nelectrons_eeSEL", "N",    11,  0.,  11.);
  TH1F* MET_eeSEL_ = dir.make<TH1F>("MET_eeSEL", "N",    100,  0.,  2400.);
  // TH1F* MET_all_ee_ = dir.make<TH1F>("MET_all_ee", "N",    11,  0.,  11.);
  TH1F* tauPt_  = dir.make<TH1F>("tauPt"  , "pt"  ,   100,   0., 300.);
  TH1F* tauEta_ = dir.make<TH1F>("tauEta" , "eta" ,   100,  -3.,   3.);
  TH1F* tauPhi_ = dir.make<TH1F>("tauPhi" , "phi" ,   100,  -5.,   5.);
  TH1F* tauVX_ = dir.make<TH1F>("tauVX" , "vx" ,   100,  -0.5,   0.5);
  TH1F* tauVY_ = dir.make<TH1F>("tauVY" , "vy" ,   100,  -0.5,   0.5);
  TH1F* ttMass_= dir.make<TH1F>("ttMass", "mass",    90,  30.,  120.);
  TH1F* Ntaus_all_ = dir.make<TH1F>("Ntaus_all", "N",    11,  0.,  11.);
  TH1F* Ntaus_ttSEL_ = dir.make<TH1F>("Ntaus_ttSEL", "N",    11,  0.,  11.);
  TH1F* MET_ttSEL_ = dir.make<TH1F>("MET_ttSEL", "N",    100,  0.,  300.);
  // TH1F* MET_all_tt_ = dir.make<TH1F>("MET_all_tt", "N",    11,  0.,  11.);
  TH1F* jetPt_  = dir.make<TH1F>("jetPt"  , "pt"  ,   100,   0., 300.);
  TH1F* jetEta_ = dir.make<TH1F>("jetEta" , "eta" ,   100,  -3.,   3.);
  TH1F* jetPhi_ = dir.make<TH1F>("jetPhi" , "phi" ,   100,  -5.,   5.);
  TH1F* jetVX_ = dir.make<TH1F>("jetVX" , "vx" ,   100,  -0.5,   0.5);
  TH1F* jetVY_ = dir.make<TH1F>("jetVY" , "vy" ,   100,  -0.5,   0.5);
  TH1F* jjMass_= dir.make<TH1F>("jjMass", "mass",    90,  30.,  120.);
  TH1F* Njets_all_ = dir.make<TH1F>("Njets_all", "N",    11,  0.,  11.);
  TH1F* Njets_jjSEL_ = dir.make<TH1F>("Njets_jjSEL", "N",    11,  0.,  11.);
  TH1F* MET_jjSEL_ = dir.make<TH1F>("MET_jjSEL", "N",    100,  0.,  300.);
  // TH1F* MET_all_jj_ = dir.make<TH1F>("MET_all_jj", "N",    11,  0.,  11.);
/*  TH1F* mcPID = dir.make<TH1F>("mcPID[nMC_]"  , "pdgId"  ,   100,   0., 300.);
  TH1F* mcVtx = dir.make<TH1F>("mcVtx[nMC_]"  , "vx"  ,   100,   0., 300.);
  TH1F* mcVty = dir.make<TH1F>("mcVty[nMC_]"  , "vy"  ,   100,   0., 300.);
  TH1F* mcMass = dir.make<TH1F>("mcMass[nMC_]"  , "mass"  ,   100,   0., 300.);
  TH1F* mcEta = dir.make<TH1F>("mcEta[nMC_]"  , "eta"  ,   100,   0., 300.);
  TH1F* mcPhi = dir.make<TH1F>("mcPhi[nMC_]"  , "phi"  ,   100,   0., 300.);
  TH1F* mcMomPID = dir.make<TH1F>("mcMomPID[nMC_]"  , "pdgId"  ,   100,   0., 300.);
  TH1F* mcMomMass = dir.make<TH1F>("mcMomMass[nMC_]"  , "mass"  ,   100,   0., 300.);
  TH1F* mcMomEta = dir.make<TH1F>("mcMomEta[nMC_]"  , "eta"  ,   100,   0., 300.);
  TH1F* mcMomPhi = dir.make<TH1F>("mcMomPhi[nMC_]"  , "phi"  ,   100,   0., 300.); */
  TH1F* DeltaR_muon_12 = dir.make<TH1F>("DeltaR_Muon_12", "R", 100, 0., 10.);
  TH1F* DeltaR_muon_34 = dir.make<TH1F>("DeltaR_Muon_34", "R", 100, 0., 10.);
  TH1F* DeltaR_muon_13 = dir.make<TH1F>("DeltaR_Muon_13", "R", 100, 0., 10.);
  TH1F* DeltaR_muon_14 = dir.make<TH1F>("DeltaR_Muon_14", "R", 100, 0., 10.);
  TH1F* DeltaR_muon_23 = dir.make<TH1F>("DeltaR_Muon_23", "R", 100, 0., 10.);
  TH1F* DeltaR_muon_24 = dir.make<TH1F>("DeltaR_Muon_24", "R", 100, 0., 10.);
  TH1F* DeltaR_elec_ = dir.make<TH1F>("DeltaR_Elec", "R", 100, 0., 10.);
  TH1F* ZZMass_ = dir.make<TH1F>("ZZmass","N", 100, 0., 300.);
  // const TString* prefix[7]="Ntuple";
  // TFileDirectory ntup = fs.mkdir("ntuple");
  TFile *ofile=new TFile(outputNtuple_.c_str(),"RECREATE");
  // TFile *f = new TFile("NTuple_Filter.root","RECREATE");
  Float_t pt1,eta1,phi1,iso1,vx1,vy1,vz1;
  Float_t pt2,eta2,phi2,iso2,vx2,vy2,vz2;
  Float_t pt3,eta3,phi3,iso3,vx3,vy3,vz3;
  Float_t pt4,eta4,phi4,iso4,vx4,vy4,vz4;
  Float_t deltaR1,deltaR2,deltaR3,deltaR4;
  Float_t mass12,mass34,mass13,mass24,mass14,mass23,massT,missET;
  Int_t Nmu;
//  TNtuple *Muon_Branch12=new TNtuple("Muon_Branch12",
  //                        "Example N-Tuple",
    //                      "pt1:eta1:phi1:iso1:vx1:vy1:vz1:pt2:eta2:phi2:iso2:vx2:vy2:vz2:pt3:eta3:phi3:iso3:vx3:vy3:vz3:pt4:eta4:phi4:iso4:vx4:vy4:vz4:mass12:mass34:massT:Nmu:missET:deltaR1:deltaR2");
  TNtuple *Muon_Branch12=new TNtuple("Muon_Branch12",
                          "Example N-Tuple",
                          "pt1:eta1:phi1:iso1:vx1:vy1:vz1:pt2:eta2:phi2:iso2:vx2:vy2:vz2");
  TNtuple *Muon_Branch34=new TNtuple("Muon_Branch34",
                          "Example N-Tuple",
                          "pt3:eta3:phi3:iso3:vx3:vy3:vz3:pt4:eta4:phi4:iso4:vx4:vy4:vz4");
  TNtuple *Muon_BranchMass1=new TNtuple("Muon_BranchMass1",
                          "Example N-Tuple",
                          "mass14:mass23:massT:Nmu:missET:deltaR1:deltaR2");
  TNtuple *Muon_BranchMass2=new TNtuple("Muon_BranchMass2",
                          "Example N-Tuple",
                          "mass14:mass23:massT:Nmu:missET:deltaR3:deltaR4");
  Int_t Ne;
  TNtuple *Electron_Branch=new TNtuple("Electron_Branch",
                          "Example N-Tuple",
                          "pt1:eta1:phi1:iso1:vx1:vy1:vz1:mass:Ne:missET");
  Int_t Nt;
  TNtuple *Tau_Branch=new TNtuple("Tau_Branch",
                          "Example N-Tuple",
                          "pt1:eta1:phi1:vx1:vy1:mass:Nt:missET");
  Int_t Nj;
  TNtuple *Jet_Branch=new TNtuple("Jet_Branch",
                          "Example N-Tuple",
                          "pt1:eta1:phi1:vx1:vy1:mass:Nj:missET"); 
  // loop the events
  int ievt=0;  
  for(unsigned int iFile=0; iFile<inputFiles_.size(); ++iFile){
    // open input file (can be located on castor)
    TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
    if( inFile ){
      // ----------------------------------------------------------------------
      // Second Part: 
      //
      //  * loop the events in the input file 
      //  * receive the collections of interest via fwlite::Handle
      //  * fill the histograms
      //  * after the loop close the input file
      // ----------------------------------------------------------------------      
      fwlite::Event ev(inFile);
      for(ev.toBegin(); !ev.atEnd(); ++ev, ++ievt){
	edm::EventBase const & event = ev;
	// break loop if maximal number of events is reached 
	if(maxEvents_>0 ? ievt+1>maxEvents_ : false) break;
	// simple event counter
	if(outputEvery_!=0 ? (ievt>0 && ievt%outputEvery_==0) : false) 
	  std::cout << "  processing event: " << ievt << std::endl;
	// Handle to the muon collection
	edm::Handle<std::vector<Muon> > muons;
	event.getByLabel(std::string("slimmedMuons"), muons);
        // Handle to the electron collection
        edm::Handle<std::vector<Electron> > electrons;
        event.getByLabel(std::string("slimmedElectrons"), electrons);
        // Handle to the tau collection
        edm::Handle<std::vector<Tau> > taus;
        event.getByLabel(std::string("slimmedTaus"), taus);
        // Handle to the jet collection
        edm::Handle<std::vector<Jet> > jets;
        event.getByLabel(std::string("slimmedJets"), jets);
        // Handle to the met collection
        edm::Handle<std::vector<MET> > mets;
        event.getByLabel(std::string("slimmedMETs"), mets);
        // Handle to the genparticle collection
     //   edm::Handle<reco::GenParticleCollection> genParticles;
     //   event.getByLabel("genParticles", genParticles);
        Int_t runnum = event.id().run();
        Int_t evnum = event.id().event();
        ev.id().run();
        ev.id().event();
        // FILE *fp = fopen("ntuple.dat","r");
	// loop muon collection and fill histograms
	int n=0;
	for(std::vector<Muon>::const_iterator Nmu1=muons->begin(); Nmu1!=muons->end(); ++Nmu1){
        n++;
        }
        Nmuons_all_->Fill(n);
        MET_all_->Fill((mets->front()).sumEt());
	for(std::vector<Muon>::const_iterator mu1=muons->begin(); mu1!=muons->end(); ++mu1){


	  if( mu1->pt()>20 && fabs(mu1->eta())<2.1 && mu1->isolationR03().sumPt<0.1 ){

	    for(std::vector<Muon>::const_iterator mu2=muons->begin(); mu2!=muons->end(); ++mu2){
              muoniso_->Fill(mu2->isolationR03().sumPt);

              if(mu2>mu1){ // prevent double conting
                for(std::vector<Muon>::const_iterator mu3=muons->begin(); mu3!=muons->end(); ++mu3){
                  if( mu3>mu2 && mu3->pt()>20 && fabs(mu3->eta())<2.1  && mu3->isolationR03().sumPt<0.1 ){
                    muoniso_->Fill( mu3->isolationR03().sumPt );
                    for(std::vector<Muon>::const_iterator mu4=muons->begin(); mu4!=muons->end(); ++mu4){
                      muoniso_->Fill(mu4->isolationR03().sumPt);
                        if(mu4>mu3){
	        	  if( (mu1->charge()*mu2->charge()<0 && mu3->charge()*mu4->charge()<0) || (mu1->charge()*mu3->charge()>0 && mu2->charge()*mu4->charge()>0) || (mu2->charge()*mu3->charge()<0 && mu1->charge()*mu4->charge()<0) ){ // check only muon pairs of unequal charge 
		            if( mu2->pt()>20 && fabs(mu2->eta())<2.1 && mu2->isolationR03().sumPt<0.1 ){
		              mumuMass12_->Fill( (mu1->p4()+mu2->p4()).mass() );
                              mumuMass34_->Fill( (mu3->p4()+mu4->p4()).mass() );
                              mumuMass13_->Fill( (mu1->p4()+mu3->p4()).mass() );
                              mumuMass24_->Fill( (mu2->p4()+mu4->p4()).mass() );
                              mumuMass23_->Fill( (mu2->p4()+mu3->p4()).mass() );
                              mumuMass14_->Fill( (mu1->p4()+mu4->p4()).mass() );
                              if( mu4->pt()>20 && fabs(mu4->eta())<2.1 && mu4->isolationR03().sumPt<0.1){
                              ZZMass_->Fill( (mu1->p4()+mu2->p4()+mu3->p4()+mu4->p4()).mass() );
                              int m=0;
                                for(std::vector<Muon>::const_iterator Nmu1=muons->begin(); Nmu1!=muons->end(); ++Nmu1){
                                  m++;
                                  }
                   		  Nmuons_mumuSEL_->Fill(m);
                    		  muoniso_SEL_->Fill(mu1->isolationR03().sumPt);
                    		  muoniso_SEL_->Fill(mu2->isolationR03().sumPt);
                    		  MET_mumuSEL_->Fill((mets->front()).sumEt());

                    		  Double_t meta1 = mu1->eta();
     		                  Double_t meta2 = mu2->eta();
   		                  Double_t metadiff = meta1-meta2;
    		                  Double_t metadiff2 = metadiff*metadiff;
 		                  Double_t mphi1 = mu1->phi();
               		          Double_t mphi2 = mu2->phi();
       		             	  Double_t mphidiff = mphi1-mphi2;
   		                  Double_t mphidiff2 = mphidiff*mphidiff;

        		          muonPt_ ->Fill( mu1->pt () );
               		     	  muonPt_SEL ->Fill( mu1->pt () );
               		     	  muonEta_->Fill( mu1->eta() );
            		          muonPhi_->Fill( mu1->phi() );
              		      	  muoniso_->Fill( mu1->isolationR03().sumPt );
          		          muonVX_  ->Fill( mu1->vx  () );
       		             	  muonVY_  ->Fill( mu1->vy  () );
               		    	  muonVZ_  ->Fill( mu1->vz  () ); 
                   		  // Muon_Branch->Fill(mu1->pt(),mu1->eta(),mu1->phi(),mu1->isolationR03().sumPt,mu1->vx(),mu1->vy(),mu1->vz(),(mu1->p4()+mu2->p4()).mass(),m,(mets->front()).sumEt());
                              int g=0;
                                for(std::vector<Muon>::const_iterator Nmu2=muons->begin(); Nmu2!=muons->end(); ++Nmu2){
                                  g++;
                                  }
         		          Nmuons_mumuSEL_->Fill(g);
   		                  muoniso_SEL_->Fill(mu3->isolationR03().sumPt);
      		                  muoniso_SEL_->Fill(mu4->isolationR03().sumPt);
  		                  MET_mumuSEL_->Fill((mets->front()).sumEt());
		                  muonPt_ ->Fill( mu3->pt() );
		                  muonPt_SEL ->Fill( mu3->pt () );
		                  muonEta_->Fill( mu3->eta() );
 		                  muonPhi_->Fill( mu3->phi() );
 		                  muoniso_->Fill( mu3->isolationR03().sumPt );
 		                  muonVX_ ->Fill( mu3->vx  () );
 		                  muonVY_ ->Fill( mu3->vy  () );
 		                  muonVZ_ ->Fill( mu3->vz  () );
 		                  Double_t meta12 = mu3->eta();
 		                  Double_t meta22 = mu4->eta();
 		                  Double_t metadiffs = meta12-meta22;
		                  Double_t metadiff2s = metadiffs*metadiffs;
  		                  Double_t mphi12 = mu3->phi();
  		                  Double_t mphi22 = mu4->phi();
		                  Double_t mphidiffs = mphi12-mphi22;
  		                  Double_t mphidiff2s = mphidiffs*mphidiffs;
 		                  Double_t metadiffa = meta1-meta12;
 		                  Double_t metadiff2a = metadiffa*metadiffa;
  		                  Double_t mphidiffa = mphi1-mphi12;
		                  Double_t mphidiff2a = mphidiffa*mphidiffa;
 		                  Double_t metadiffb = meta1-meta22;
		                  Double_t metadiff2b = metadiffb*metadiffb;
 		                  Double_t mphidiffb = mphi1-mphi22;
		                  Double_t mphidiff2b = mphidiffb*mphidiffb;
  		                  Double_t metadiffc = meta2-meta12;
		                  Double_t metadiff2c = metadiffc*metadiffc;
		                  Double_t mphidiffc = mphi2-mphi12;
  		                  Double_t mphidiff2c = mphidiffc*mphidiffc;
		                  Double_t metadiffd = meta2-meta22;
		                  Double_t metadiff2d = metadiffd*metadiffd;
		                  Double_t mphidiffd = mphi2-mphi22;
       			          Double_t mphidiff2d = mphidiffd*mphidiffd;
		                  if ( TMath::Sqrt(metadiff2+mphidiff2)>0.4 && mu1->charge()*mu2->charge()<0 && mu3->charge()*mu4->charge()<0 ){
		                  DeltaR_muon_12->Fill(TMath::Sqrt(metadiff2+mphidiff2));
		                  DeltaR_muon_34->Fill(TMath::Sqrt(metadiff2s+mphidiff2s));
                                  Nmuons_mumuSEL_->Fill(g);
                                  muoniso_SEL_->Fill(mu3->isolationR03().sumPt);
                                  muoniso_SEL_->Fill(mu4->isolationR03().sumPt);
                                  MET_mumuSEL_->Fill((mets->front()).sumEt());
                                  muonPt_ ->Fill( mu3->pt() );
                                  muonEta_->Fill( mu3->eta() );
                                  muonPhi_->Fill( mu3->phi() );
                                  muoniso_->Fill( mu3->isolationR03().sumPt );
                                  muonVX_ ->Fill( mu3->vx  () );
                                  muonVY_ ->Fill( mu3->vy  () );
                                  muonVZ_ ->Fill( mu3->vz  () );
                                  Nmuons_mumuSEL_->Fill(m);
                                  muoniso_SEL_->Fill(mu1->isolationR03().sumPt);
                                  muoniso_SEL_->Fill(mu2->isolationR03().sumPt);
                                  muonPt_ ->Fill( mu1->pt () );
                                  muonPt_SEL ->Fill( mu1->pt () );
                                  muonEta_->Fill( mu1->eta() );
                                  muonPhi_->Fill( mu1->phi() );
                                  muoniso_->Fill( mu1->isolationR03().sumPt );
                                  muonVX_  ->Fill( mu1->vx  () );
                                  muonVY_  ->Fill( mu1->vy  () );
                                  muonVZ_  ->Fill( mu1->vz  () );
                                  muonPt_ ->Fill( mu2->pt () );
                                  muonPt_SEL ->Fill( mu2->pt () );
                                  muonEta_->Fill( mu2->eta() );
                                  muonPhi_->Fill( mu2->phi() );
                                  muoniso_->Fill( mu2->isolationR03().sumPt );
                                  muonVX_  ->Fill( mu2->vx  () );
                                  muonVY_  ->Fill( mu2->vy  () );
                                  muonVZ_  ->Fill( mu2->vz  () );
                                  muonPt_ ->Fill( mu4->pt () );
                                  muonPt_SEL ->Fill( mu4->pt () );
                                  muonEta_->Fill( mu4->eta() );
                                  muonPhi_->Fill( mu4->phi() );
                                  muoniso_->Fill( mu4->isolationR03().sumPt );
                                  muonVX_  ->Fill( mu4->vx  () );
                                  muonVY_  ->Fill( mu4->vy  () );
                                  muonVZ_  ->Fill( mu4->vz  () );


                                  Float_t deltaR1v=TMath::Sqrt(metadiff2+mphidiff2);
                                  Float_t deltaR2v=TMath::Sqrt(metadiff2s+mphidiff2s);
                   //               Muon_Branch12->Fill(mu1->pt(),mu1->eta(),mu1->phi(),mu1->isolationR03().sumPt,mu1->vx(),mu1->vy(),mu1->vz(),mu2->pt(),mu2->eta(),mu2->phi(),mu2->isolationR03().sumPt,mu2->vx(),mu2->vy(),mu2->vz(),mu3->pt(),mu3->eta(),mu3->phi(),mu3->isolationR03().sumPt,mu3->vx(),mu3->vy(),mu3->vz(),mu4->pt(),mu4->eta(),mu4->phi(),mu4->isolationR03().sumPt,mu4->vx(),mu4->vy(),mu4->vz(),(mu1->p4()+mu2->p4()).mass(),(mu3->p4()+mu4->p4()).mass(),(mu1->p4()+mu2->p4()+mu3->p4()+mu4->p4()).mass(),g,(mets->front()).sumEt(),deltaR1v,deltaR2v);
                                  Muon_Branch12->Fill(mu1->pt(),mu1->eta(),mu1->phi(),mu1->isolationR03().sumPt,mu1->vx(),mu1->vy(),mu1->vz(),mu2->pt(),mu2->eta(),mu2->phi(),mu2->isolationR03().sumPt,mu2->vx(),mu2->vy(),mu2->vz());
                                  Muon_Branch34->Fill(mu3->pt(),mu3->eta(),mu3->phi(),mu3->isolationR03().sumPt,mu3->vx(),mu3->vy(),mu3->vz(),mu4->pt(),mu4->eta(),mu4->phi(),mu4->isolationR03().sumPt,mu4->vx(),mu4->vy(),mu4->vz());
                                  Muon_BranchMass1->Fill((mu1->p4()+mu2->p4()).mass(),(mu3->p4()+mu4->p4()).mass(),(mu1->p4()+mu2->p4()+mu3->p4()+mu4->p4()).mass(),g,(mets->front()).sumEt(),deltaR1v,deltaR2v);
		                  }
		                  if ( TMath::Sqrt(metadiff2b+mphidiff2b)>0.4 && mu1->charge()*mu4->charge()<0 && mu2->charge()*mu3->charge()<0 ){
		                  DeltaR_muon_14->Fill(TMath::Sqrt(metadiff2b+mphidiff2b));
		                  DeltaR_muon_23->Fill(TMath::Sqrt(metadiff2c+mphidiff2c));
                                  Nmuons_mumuSEL_->Fill(g);
                                  muoniso_SEL_->Fill(mu3->isolationR03().sumPt);
                                  muoniso_SEL_->Fill(mu4->isolationR03().sumPt);
                                  MET_mumuSEL_->Fill((mets->front()).sumEt());
                                  muonPt_ ->Fill( mu3->pt() );
                                  muonEta_->Fill( mu3->eta() );
                                  muonPhi_->Fill( mu3->phi() );
                                  muoniso_->Fill( mu3->isolationR03().sumPt );
                                  muonVX_ ->Fill( mu3->vx  () );
                                  muonVY_ ->Fill( mu3->vy  () );
                                  muonVZ_ ->Fill( mu3->vz  () );
                                  Nmuons_mumuSEL_->Fill(m);
                                  muoniso_SEL_->Fill(mu1->isolationR03().sumPt);
                                  muoniso_SEL_->Fill(mu2->isolationR03().sumPt);
                                  muonPt_ ->Fill( mu1->pt () );
                                  muonPt_SEL ->Fill( mu1->pt () );
                                  muonEta_->Fill( mu1->eta() );
                                  muonPhi_->Fill( mu1->phi() );
                                  muoniso_->Fill( mu1->isolationR03().sumPt );
                                  muonVX_  ->Fill( mu1->vx  () );
                                  muonVY_  ->Fill( mu1->vy  () );
                                  muonVZ_  ->Fill( mu1->vz  () );
                                  muonPt_ ->Fill( mu2->pt () );
                                  muonPt_SEL ->Fill( mu2->pt () );
                                  muonEta_->Fill( mu2->eta() );
                                  muonPhi_->Fill( mu2->phi() );
                                  muoniso_->Fill( mu2->isolationR03().sumPt );
                                  muonVX_  ->Fill( mu2->vx  () );
                                  muonVY_  ->Fill( mu2->vy  () );
                                  muonVZ_  ->Fill( mu2->vz  () );
                                  muonPt_ ->Fill( mu4->pt () );
                                  muonPt_SEL ->Fill( mu4->pt () );
                                  muonEta_->Fill( mu4->eta() );
                                  muonPhi_->Fill( mu4->phi() );
                                  muoniso_->Fill( mu4->isolationR03().sumPt );
                                  muonVX_  ->Fill( mu4->vx  () );
                                  muonVY_  ->Fill( mu4->vy  () );
                                  muonVZ_  ->Fill( mu4->vz  () );
                                  Float_t deltaR5v=TMath::Sqrt(metadiff2b+mphidiff2b);
                                  Float_t deltaR6v=TMath::Sqrt(metadiff2c+mphidiff2c);
                //                  Muon_Branch56->Fill(mu1->pt(),mu1->eta(),mu1->phi(),mu1->isolationR03().sumPt,mu1->vx(),mu1->vy(),mu1->vz(),mu2->pt(),mu2->eta(),mu2->phi(),mu2->isolationR03().sumPt,mu2->vx(),mu2->vy(),mu2->vz(),mu3->pt(),mu3->eta(),mu3->phi(),mu3->isolationR03().sumPt,mu3->vx(),mu3->vy(),mu3->vz(),mu4->pt(),mu4->eta(),mu4->phi(),mu4->isolationR03().sumPt,mu4->vx(),mu4->vy(),mu4->vz(),(mu1->p4()+mu4->p4()).mass(),(mu2->p4()+mu3->p4()).mass(),(mu1->p4()+mu2->p4()+mu3->p4()+mu4->p4()).mass(),g,(mets->front()).sumEt(),deltaR5v,deltaR6v);
                                  Muon_Branch12->Fill(mu1->pt(),mu1->eta(),mu1->phi(),mu1->isolationR03().sumPt,mu1->vx(),mu1->vy(),mu1->vz(),mu2->pt(),mu2->eta(),mu2->phi(),mu2->isolationR03().sumPt,mu2->vx(),mu2->vy(),mu2->vz());
                                  Muon_Branch34->Fill(mu3->pt(),mu3->eta(),mu3->phi(),mu3->isolationR03().sumPt,mu3->vx(),mu3->vy(),mu3->vz(),mu4->pt(),mu4->eta(),mu4->phi(),mu4->isolationR03().sumPt,mu4->vx(),mu4->vy(),mu4->vz());
                                  Muon_BranchMass2->Fill((mu1->p4()+mu2->p4()).mass(),(mu3->p4()+mu4->p4()).mass(),(mu1->p4()+mu2->p4()+mu3->p4()+mu4->p4()).mass(),g,(mets->front()).sumEt(),deltaR5v,deltaR6v);
		                  }
		                  // Muon_Branch->Fill(mu3->pt(),mu3->eta(),mu3->phi(),mu3->isolationR03().sumPt,mu3->vx(),mu3->vy(),mu3->vz(),(mu3->p4()+mu4->p4()).mass(),g,(mets->front()).sumEt(),deltaR1v,deltaR2v,deltaR3v,deltaR4v,deltaR5v,deltaR6v);
		                  }
		                }
		              }
		            }
		          }
		        }
		      }
		    }

/*            for(std::vector<Muon>::const_iterator mu3=muons->begin(); mu3!=muons->end(); ++mu3){
                if( mu3>mu2 && mu3->pt()>20 && fabs(mu3->eta())<2.1  && mu3->isolationR03().sumPt<0.1 ){
                  muoniso_->Fill( mu3->isolationR03().sumPt );
            	for(std::vector<Muon>::const_iterator mu4=muons->begin(); mu4!=muons->end(); ++mu4){       
                  muoniso_->Fill(mu4->isolationR03().sumPt);
                 if(mu4>mu3){ 
                 if( mu3->charge()*mu4->charge()<0 ){ 
                  if( mu4->pt()>20 && fabs(mu4->eta())<2.1 && mu4->isolationR03().sumPt<0.1){
                    ZZMass_->Fill( (mu1->p4()+mu2->p4()+mu3->p4()+mu4->p4()).mass() );
		    int g=0;
                    for(std::vector<Muon>::const_iterator Nmu2=muons->begin(); Nmu2!=muons->end(); ++Nmu2){
                    g++;
                    }
                    Nmuons_mumuSEL_->Fill(g);
                    muoniso_SEL_->Fill(mu3->isolationR03().sumPt);
                    muoniso_SEL_->Fill(mu4->isolationR03().sumPt);
                    MET_mumuSEL_->Fill((mets->front()).sumEt());
                    muonPt_ ->Fill( mu3->pt() );
                    muonPt_SEL ->Fill( mu3->pt () );
                    muonEta_->Fill( mu3->eta() );
                    muonPhi_->Fill( mu3->phi() );
                    muoniso_->Fill( mu3->isolationR03().sumPt );
                    muonVX_ ->Fill( mu3->vx  () );
                    muonVY_ ->Fill( mu3->vy  () );
                    muonVZ_ ->Fill( mu3->vz  () );
                    Double_t meta12 = mu3->eta();
                    Double_t meta22 = mu4->eta();
                    Double_t metadiffs = meta12-meta22;
                    Double_t metadiff2s = metadiffs*metadiffs;
                    Double_t mphi12 = mu3->phi();
                    Double_t mphi22 = mu4->phi();
                    Double_t mphidiffs = mphi12-mphi22;
                    Double_t mphidiff2s = mphidiffs*mphidiffs;
                    if ( TMath::Sqrt(metadiff2s+mphidiff2s)>0.4 ){
                    DeltaR_muon_->Fill(TMath::Sqrt(metadiff2s+mphidiff2s));
                    }
                  Muon_Branch->Fill(mu3->pt(),mu3->eta(),mu3->phi(),mu3->isolationR03().sumPt,mu3->vx(),mu3->vy(),mu3->vz(),(mu3->p4()+mu4->p4()).mass(),g,(mets->front()).sumEt());
                  } 
                }
              }//mu3>mu2
  	     }}}
	          }
	        }
	      } */  /*mu2>mu1*/
            }
          }
        } 
//fill plots for mu1 and mu2
        int o=0;
        for(std::vector<Electron>::const_iterator Ne1=electrons->begin(); Ne1!=electrons->end(); ++Ne1){
        o++;
        }
        Nelectrons_all_->Fill(o);
        for(std::vector<Electron>::const_iterator e1=electrons->begin(); e1!=electrons->end(); ++e1){
          if( e1->pt()>20 && fabs(e1->eta())<2.1 && e1->dr03TkSumPt()<0.1 ){
            for(std::vector<Electron>::const_iterator e2=electrons->begin(); e2!=electrons->end(); ++e2){
              eleciso_->Fill(e2->dr03TkSumPt());
              if(e2>e1){ // prevent double conting
                if( e1->charge()*e2->charge()<0 ){ // check only muon pairs of unequal charge 
                  if( e2->pt()>20 && fabs(e2->eta())<2.1 && e2->dr03TkSumPt()<0.1 ){
                    eeMass_->Fill( (e1->p4()+e2->p4()).mass() );
                    int p=0;
                    for(std::vector<Electron>::const_iterator Ne1=electrons->begin(); Ne1!=electrons->end(); ++Ne1){
                    p++;
                    }
                    Nelectrons_eeSEL_->Fill(p);
                    eleciso_SEL_->Fill(e1->dr03TkSumPt());
                    eleciso_SEL_->Fill(e2->dr03TkSumPt());
                    MET_eeSEL_->Fill((mets->front()).sumEt());
                    Double_t eeta1 = e1->eta();
                    Double_t eeta2 = e2->eta();
                    Double_t eetadiff = eeta1-eeta2;
                    Double_t eetadiff2 = eetadiff*eetadiff;
                    Double_t ephi1 = e1->phi();
                    Double_t ephi2 = e2->phi();
                    Double_t ephidiff = ephi1-ephi2;
                    Double_t ephidiff2 = ephidiff*ephidiff;
                    elecPt_ ->Fill( e1->pt () );
                    elecEta_->Fill( e1->eta() );
                    elecPhi_->Fill( e1->phi() );
                    eleciso_->Fill( e1->dr03TkSumPt() );
                    elecVX_  ->Fill( e1->vx  () );
                    elecVY_  ->Fill( e1->vy  () );
                    elecVZ_  ->Fill( e1->vz  () );
                    if ( TMath::Sqrt(eetadiff2+ephidiff2)>2.4 ){
                    DeltaR_elec_->Fill(TMath::Sqrt(eetadiff2+ephidiff2));
                    }
                  Electron_Branch->Fill(e1->pt(),e1->eta(),e1->phi(),e1->dr03TkSumPt(),e1->vx(),e1->vy(),e1->vz(),(e1->p4()+e2->p4()).mass(),p,(mets->front()).sumEt());
                  }
                }
              }
            }
          }
        } // End of Electron Loop
        

        int q=0;
        for(std::vector<Tau>::const_iterator Nt1=taus->begin(); Nt1!=taus->end(); ++Nt1){
        q++;
        }
        Ntaus_all_->Fill(q);
        for(std::vector<Tau>::const_iterator t1=taus->begin(); t1!=taus->end(); ++t1){
          if( t1->pt()>20 && fabs(t1->eta())<2.1 ){
            for(std::vector<Tau>::const_iterator t2=taus->begin(); t2!=taus->end(); ++t2){
              if(t2>t1){ // prevent double conting
                if( t1->charge()*t2->charge()<0 ){ // check only tau pairs of unequal charge 
                  if( t2->pt()>20 && fabs(t2->eta())<2.1 ){
                    ttMass_->Fill( (t1->p4()+t2->p4()).mass() );
                    int u=0;
                    for(std::vector<Tau>::const_iterator Nt1=taus->begin(); Nt1!=taus->end(); ++Nt1){
                    u++;
                    }
                    Ntaus_ttSEL_->Fill(q);
                    MET_ttSEL_->Fill((mets->front()).sumEt());
                    tauPt_ ->Fill( t1->pt () );
                    tauEta_->Fill( t1->eta() );
                    tauPhi_->Fill( t1->phi() );
                    tauVX_->Fill( t1->vx  () );
                    tauVY_->Fill( t1->vy  () );
                    Tau_Branch->Fill(t1->pt(),t1->eta(),t1->phi(),t1->vx(),t1->vy(),(t1->p4()+t2->p4()).mass(),u,(mets->front()).sumEt());
                  }
                }
              }
            }
          }
        } // End of Tau Loop
        int r=0;
        for(std::vector<Jet>::const_iterator Nj1=jets->begin(); Nj1!=jets->end(); ++Nj1){
        r++;
        }
        Njets_all_->Fill(r);
        for(std::vector<Jet>::const_iterator j1=jets->begin(); j1!=jets->end(); ++j1){
          if( j1->pt()>20 && fabs(j1->eta())<2.1 ){
            for(std::vector<Jet>::const_iterator j2=jets->begin(); j2!=jets->end(); ++j2){
              if(j2>j1){ // prevent double conting
                if( j1->charge()*j2->charge()<0 ){ // check only jet pairs of unequal charge 
                   if( j2->pt()>20 && fabs(j2->eta())<2.1 ){
                    jjMass_->Fill( (j1->p4()+j2->p4()).mass() );
                    int s=0;
                    for(std::vector<Jet>::const_iterator Nj1=jets->begin(); Nj1!=jets->end(); ++Nj1){
                    s++;
                    }
                    Njets_jjSEL_->Fill(s);
                    MET_jjSEL_->Fill((mets->front()).sumEt());
                    jetPt_ ->Fill( j1->pt () );
                    jetEta_->Fill( j1->eta() );
                    jetPhi_->Fill( j1->phi() );
                    jetVX_  ->Fill( j1->vx  () );
                    jetVY_  ->Fill( j1->vy  () );
                    Jet_Branch->Fill(j1->pt(),j1->eta(),j1->phi(),j1->vx(),j1->vy(),(j1->p4()+j2->p4()).mass(),s,(mets->front()).sumEt());
                  }
                }
              }
            }
          }
        } // End of Jet Loop
        // ev.isRealData();
/*      Int_t runnum = event.id().run();
        Int_t evnum = event.id().event();
        if(!event.isRealData()) {
          if (genParticlesHandle_.isValid() ) {
            for (vector<GenParticle>::const_iterator ip=genParticlesHandle_->begin(); ip!=genParticlesHandle_->end(); ++ip) {
              const Candidate *p = (const Candidate*)&(*ip);
              //find final state muons
              if (ip->status()==1 && fabs(ip->pdgId())==13 ) {
                const Candidate *p = (const Candidate*)&(*ip); 
                for (size_t j=0; j<p->numberOfMothers(); ++j) {
                  mom = p->mother(j);
                  if(fabs(mom->pdgId())==23){
                    mcPID->Fill(p->pdgId());
                    mcMass->Fill(p->mass());
                    mcEta->Fill(p->eta());
                    mcPhi->Fill(p->phi());
                    mcVtx->Fill(p->vx());
                    mcVty->Fill(p->vy());
                    mcMomPID->Fill(mom->pdgId());
                    mcMomMass->Fill(mom->mass());
                    mcMomEta->Fill(mom->eta());
                    mcMomPhi->Fill(mom->phi());
                    p->numberOfMothers();
                  }
                }
              }
              //find final state electrons
              if (ip->status()==1 && fabs(ip->pdgId())==11 ) {
                // const Candidate *p = (const Candidate*)&(*ip);
                for (size_t j=0; j<p->numberOfMothers(); ++j) {
                 mom = p->mother(j);
                  if(fabs(mom->pdgId())==23){
                    mcPID->Fill(p->pdgId());
                    mcMass->Fill(p->mass());
                    mcEta->Fill(p->eta());
                    mcPhi->Fill(p->phi());
                    mcVtx->Fill(p->vx());
                    mcVty->Fill(p->vy());
                    mcMomPID->Fill(mom->pdgId());
                    mcMomMass->Fill(mom->mass());
                    mcMomEta->Fill(mom->eta());
                    mcMomPhi->Fill(mom->phi());
                    p->numberOfMothers();
                  }
                }
              }
              for (size_t k=0; k<p->numberOfDaughters(); ++k) {
                const Candidate *dp = p->daughter(k);
                p->numberOfDaughters();
                if (fabs(dp->pdgId())==11);
              }
            }
          }
        } // End of GenParticle Loop    */  
      }
      ofile->Write();
      ofile->Close();
      // close input file
      inFile->Close();
    }
    // break loop if maximal number of events is reached:
    // this has to be done twice to stop the file loop as well
    if(maxEvents_>0 ? ievt+1>maxEvents_ : false) break;
  }
  return 0;
}
// ev.isRealData();
// if(!ev.isRealData() {}
// ev.id().run();
// ev.id().event();
// edm::Handle<reco::GenParticleCollection> genParticles;
// ev.getByLabel( "generator", genParticles)
// if (genParticlesHandle_.isValid() ) {
// for (vector<GenParticle>::const_iterator ip =
// genParticlesHandle_->begin(); ip !=
// genParticlesHandle_->end(); ++ip) {
// const Candidate *p = (const Candidate*)&(*ip);
// mcPID[nMC_]     = p->pdgId();
// mcVtx[nMC_][0]  = p->vx();
// mcVtx[nMC_][1]  = p->vy();
// mcVtx[nMC_][2]  = p->vz();
// mcPt[nMC_]      = p->pt();
// mcMass[nMC_]    = p->mass();
// mcEta[nMC_]     = p->eta();
// mcPhi[nMC_]     = p->phi();
// p->numberOfMothers()
// for (size_t j=0; j<p->numberOfMothers(); ++j) {
// mom = p->mother(j);
// mcMomPID[nMC_] = mom->pdgId();
// mcMomPt[nMC_] = mom->pt();
// mcMomMass[nMC_] = mom->mass();
// mcMomEta[nMC_] = mom->eta();
// mcMomPhi[nMC_] = mom->phi();
// p->numberOfDaughters()
// for (size_t k=0; k<p->numberOfDaughters(); ++k) {
// const Candidate *dp = p->daughter(k);
// if (fabs(dp->pdgId())==11)

