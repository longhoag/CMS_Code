//--all input, wo diagrams, ee mm em branches, unify variables, all data sets, not normalize


void filler(TH1F* hpt1, const char * title) {
   hpt1->SetFillColor(kBlue);
   hpt1->GetXaxis()->SetTitle(title);
   hpt1->GetYaxis()->SetTitle("Events");
   hpt1->Draw("hist");
}

void signalStyling(TH1F* hist) {
   hist->SetLineColor(kRed);
   hist->SetFillStyle(3008);  
   hist->SetFillColor(kRed);
}

void backgroundStyling(TH1F* hist) {
   hist->SetLineColor(kBlue);
   hist->SetFillStyle(3008);  
   hist->SetFillColor(kBlue);
}

void appliedtesting(Int_t ntrain = 100) {
   const char* fname = "outputNtuple_tt.root";
   const char* fname2 = "outputNtuple_DY.root";
   const char* fname3 = "outputNtuple_wz.root";
   const char* fname4 = "outputNtuple_zz.root";
   const char* fname5 = "outputNtuple_ww.root";

   TFile* input = 0;
   TFile* input2 = 0;
   TFile* input3 = 0;
   TFile* input4 = 0;
   TFile* input5 = 0;

   if(!gSystem->AccessPathName(fname) && !gSystem->AccessPathName(fname2)) {
      input = TFile::Open(fname);
      input2 = TFile::Open(fname2);
      input3 = TFile::Open(fname3);
      input4 = TFile::Open(fname4);
      input5 = TFile::Open(fname5);
   }
   else {
      printf("Cannot find the file");
      return;
   }
//
   TTree* ee_Branch = (TTree*) input->Get("ee_Branch");
   TTree* eeb_Branch = (TTree*) input2->Get("ee_Branch");
   TTree* eeb2_Branch = (TTree*) input3->Get("ee_Branch");
   TTree* eeb3_Branch = (TTree*) input4->Get("ee_Branch");
   TTree* eeb4_Branch = (TTree*) input5->Get("ee_Branch");

   TTree* mm_Branch = (TTree*) input->Get("mm_Branch");
   TTree* mmb_Branch = (TTree*) input2->Get("mm_Branch");
   TTree* mmb2_Branch = (TTree*) input3->Get("mm_Branch");
   TTree* mmb3_Branch = (TTree*) input4->Get("mm_Branch");
   TTree* mmb4_Branch = (TTree*) input5->Get("mm_Branch");

   TTree* em_Branch = (TTree*) input->Get("em_Branch");
   TTree* emb_Branch = (TTree*) input2->Get("em_Branch");
   TTree* emb2_Branch = (TTree*) input3->Get("em_Branch");
   TTree* emb3_Branch = (TTree*) input4->Get("em_Branch");
   TTree* emb4_Branch = (TTree*) input5->Get("em_Branch");


   TFile* ofile = new TFile("output_ML","RECREATE");
   TTree *simu = new TTree("MonteCarlo", "Filtered Monte Carlo Events");

   //--ee
   Float_t pt1_ee, eta1_ee, phi1_ee, vx1_ee, vy1_ee;
   Float_t pt2_ee, eta2_ee, phi2_ee, vx2_ee, vy2_ee;
   Float_t Nj_ee, Nak8j_ee, missET_ee;


   //--mm
   Float_t pt1_mm, eta1_mm, phi1_mm, vx1_mm, vy1_mm;
   Float_t pt2_mm, eta2_mm, phi2_mm, vx2_mm, vy2_mm;
   Float_t Nj_mm, Nak8j_mm, missET_mm;

   //--em
   Float_t pt1_em, eta1_em, phi1_em, vx1_em, vy1_em;
   Float_t pt2_em, eta2_em, phi2_em, vx2_em, vy2_em;
   Float_t Nj_em, Nak8j_em, missET_em;

   Float_t Nmu, type;

//-- set branches

//--ee,eeb
   ee_Branch->SetBranchAddress("pt1",  &pt1_ee);
   ee_Branch->SetBranchAddress("eta1", &eta1_ee);
   ee_Branch->SetBranchAddress("phi1", &phi1_ee);
   ee_Branch->SetBranchAddress("vx1",  &vx1_ee);
   ee_Branch->SetBranchAddress("vy1",  &vy1_ee);
   ee_Branch->SetBranchAddress("pt2",  &pt2_ee);
   ee_Branch->SetBranchAddress("eta2", &eta2_ee);
   ee_Branch->SetBranchAddress("phi2", &phi2_ee);
   ee_Branch->SetBranchAddress("vx2",  &vx2_ee);
   ee_Branch->SetBranchAddress("vy2",  &vy2_ee);
   ee_Branch->SetBranchAddress("Nj",   &Nj_ee);
   ee_Branch->SetBranchAddress("Nak8j",&Nak8j_ee);
   ee_Branch->SetBranchAddress("missET",&missET_ee);

   eeb_Branch->SetBranchAddress("pt1",  &pt1_ee);
   eeb_Branch->SetBranchAddress("eta1", &eta1_ee);
   eeb_Branch->SetBranchAddress("phi1", &phi1_ee);
   eeb_Branch->SetBranchAddress("vx1",  &vx1_ee);
   eeb_Branch->SetBranchAddress("vy1",  &vy1_ee);
   eeb_Branch->SetBranchAddress("pt2",  &pt2_ee);
   eeb_Branch->SetBranchAddress("eta2", &eta2_ee);
   eeb_Branch->SetBranchAddress("phi2", &phi2_ee);
   eeb_Branch->SetBranchAddress("vx2",  &vx2_ee);
   eeb_Branch->SetBranchAddress("vy2",  &vy2_ee);
   eeb_Branch->SetBranchAddress("Nj",   &Nj_ee);
   eeb_Branch->SetBranchAddress("Nak8j",&Nak8j_ee);
   eeb_Branch->SetBranchAddress("missET",&missET_ee);

   eeb2_Branch->SetBranchAddress("pt1",  &pt1_ee);
   eeb2_Branch->SetBranchAddress("eta1", &eta1_ee);
   eeb2_Branch->SetBranchAddress("phi1", &phi1_ee);
   eeb2_Branch->SetBranchAddress("vx1",  &vx1_ee);
   eeb2_Branch->SetBranchAddress("vy1",  &vy1_ee);
   eeb2_Branch->SetBranchAddress("pt2",  &pt2_ee);
   eeb2_Branch->SetBranchAddress("eta2", &eta2_ee);
   eeb2_Branch->SetBranchAddress("phi2", &phi2_ee);
   eeb2_Branch->SetBranchAddress("vx2",  &vx2_ee);
   eeb2_Branch->SetBranchAddress("vy2",  &vy2_ee);
   eeb2_Branch->SetBranchAddress("Nj",   &Nj_ee);
   eeb2_Branch->SetBranchAddress("Nak8j",&Nak8j_ee);
   eeb2_Branch->SetBranchAddress("missET",&missET_ee);

   eeb3_Branch->SetBranchAddress("pt1",  &pt1_ee);
   eeb3_Branch->SetBranchAddress("eta1", &eta1_ee);
   eeb3_Branch->SetBranchAddress("phi1", &phi1_ee);
   eeb3_Branch->SetBranchAddress("vx1",  &vx1_ee);
   eeb3_Branch->SetBranchAddress("vy1",  &vy1_ee);
   eeb3_Branch->SetBranchAddress("pt2",  &pt2_ee);
   eeb3_Branch->SetBranchAddress("eta2", &eta2_ee);
   eeb3_Branch->SetBranchAddress("phi2", &phi2_ee);
   eeb3_Branch->SetBranchAddress("vx2",  &vx2_ee);
   eeb3_Branch->SetBranchAddress("vy2",  &vy2_ee);
   eeb3_Branch->SetBranchAddress("Nj",   &Nj_ee);
   eeb3_Branch->SetBranchAddress("Nak8j",&Nak8j_ee);
   eeb3_Branch->SetBranchAddress("missET",&missET_ee);

   eeb4_Branch->SetBranchAddress("pt1",  &pt1_ee);
   eeb4_Branch->SetBranchAddress("eta1", &eta1_ee);
   eeb4_Branch->SetBranchAddress("phi1", &phi1_ee);
   eeb4_Branch->SetBranchAddress("vx1",  &vx1_ee);
   eeb4_Branch->SetBranchAddress("vy1",  &vy1_ee);
   eeb4_Branch->SetBranchAddress("pt2",  &pt2_ee);
   eeb4_Branch->SetBranchAddress("eta2", &eta2_ee);
   eeb4_Branch->SetBranchAddress("phi2", &phi2_ee);
   eeb4_Branch->SetBranchAddress("vx2",  &vx2_ee);
   eeb4_Branch->SetBranchAddress("vy2",  &vy2_ee);
   eeb4_Branch->SetBranchAddress("Nj",   &Nj_ee);
   eeb4_Branch->SetBranchAddress("Nak8j",&Nak8j_ee);
   eeb4_Branch->SetBranchAddress("missET",&missET_ee);
//
   mm_Branch->SetBranchAddress("pt1",  &pt1_mm);
   mm_Branch->SetBranchAddress("eta1", &eta1_mm);
   mm_Branch->SetBranchAddress("phi1", &phi1_mm);
   mm_Branch->SetBranchAddress("vx1",  &vx1_mm);
   mm_Branch->SetBranchAddress("vy1",  &vy1_mm);
   mm_Branch->SetBranchAddress("pt2",  &pt2_mm);
   mm_Branch->SetBranchAddress("eta2", &eta2_mm);
   mm_Branch->SetBranchAddress("phi2", &phi2_mm);
   mm_Branch->SetBranchAddress("vx2",  &vx2_mm);
   mm_Branch->SetBranchAddress("vy2",  &vy2_mm);
   mm_Branch->SetBranchAddress("Nj",   &Nj_mm);
   mm_Branch->SetBranchAddress("Nak8j",&Nak8j_mm);
   mm_Branch->SetBranchAddress("missET",&missET_mm);

   mmb_Branch->SetBranchAddress("pt1",  &pt1_mm);
   mmb_Branch->SetBranchAddress("eta1", &eta1_mm);
   mmb_Branch->SetBranchAddress("phi1", &phi1_mm);
   mmb_Branch->SetBranchAddress("vx1",  &vx1_mm);
   mmb_Branch->SetBranchAddress("vy1",  &vy1_mm);
   mmb_Branch->SetBranchAddress("pt2",  &pt2_mm);
   mmb_Branch->SetBranchAddress("eta2", &eta2_mm);
   mmb_Branch->SetBranchAddress("phi2", &phi2_mm);
   mmb_Branch->SetBranchAddress("vx2",  &vx2_mm);
   mmb_Branch->SetBranchAddress("vy2",  &vy2_mm);
   mmb_Branch->SetBranchAddress("Nj",   &Nj_mm);
   mmb_Branch->SetBranchAddress("Nak8j",&Nak8j_mm);
   mmb_Branch->SetBranchAddress("missET",&missET_mm);

   mmb2_Branch->SetBranchAddress("pt1",  &pt1_mm);
   mmb2_Branch->SetBranchAddress("eta1", &eta1_mm);
   mmb2_Branch->SetBranchAddress("phi1", &phi1_mm);
   mmb2_Branch->SetBranchAddress("vx1",  &vx1_mm);
   mmb2_Branch->SetBranchAddress("vy1",  &vy1_mm);
   mmb2_Branch->SetBranchAddress("pt2",  &pt2_mm);
   mmb2_Branch->SetBranchAddress("eta2", &eta2_mm);
   mmb2_Branch->SetBranchAddress("phi2", &phi2_mm);
   mmb2_Branch->SetBranchAddress("vx2",  &vx2_mm);
   mmb2_Branch->SetBranchAddress("vy2",  &vy2_mm);
   mmb2_Branch->SetBranchAddress("Nj",   &Nj_mm);
   mmb2_Branch->SetBranchAddress("Nak8j",&Nak8j_mm);
   mmb2_Branch->SetBranchAddress("missET",&missET_mm);

   mmb3_Branch->SetBranchAddress("pt1",  &pt1_mm);
   mmb3_Branch->SetBranchAddress("eta1", &eta1_mm);
   mmb3_Branch->SetBranchAddress("phi1", &phi1_mm);
   mmb3_Branch->SetBranchAddress("vx1",  &vx1_mm);
   mmb3_Branch->SetBranchAddress("vy1",  &vy1_mm);
   mmb3_Branch->SetBranchAddress("pt2",  &pt2_mm);
   mmb3_Branch->SetBranchAddress("eta2", &eta2_mm);
   mmb3_Branch->SetBranchAddress("phi2", &phi2_mm);
   mmb3_Branch->SetBranchAddress("vx2",  &vx2_mm);
   mmb3_Branch->SetBranchAddress("vy2",  &vy2_mm);
   mmb3_Branch->SetBranchAddress("Nj",   &Nj_mm);
   mmb3_Branch->SetBranchAddress("Nak8j",&Nak8j_mm);
   mmb3_Branch->SetBranchAddress("missET",&missET_mm);

   mmb4_Branch->SetBranchAddress("pt1",  &pt1_mm);
   mmb4_Branch->SetBranchAddress("eta1", &eta1_mm);
   mmb4_Branch->SetBranchAddress("phi1", &phi1_mm);
   mmb4_Branch->SetBranchAddress("vx1",  &vx1_mm);
   mmb4_Branch->SetBranchAddress("vy1",  &vy1_mm);
   mmb4_Branch->SetBranchAddress("pt2",  &pt2_mm);
   mmb4_Branch->SetBranchAddress("eta2", &eta2_mm);
   mmb4_Branch->SetBranchAddress("phi2", &phi2_mm);
   mmb4_Branch->SetBranchAddress("vx2",  &vx2_mm);
   mmb4_Branch->SetBranchAddress("vy2",  &vy2_mm);
   mmb4_Branch->SetBranchAddress("Nj",   &Nj_mm);
   mmb4_Branch->SetBranchAddress("Nak8j",&Nak8j_mm);
   mmb4_Branch->SetBranchAddress("missET",&missET_mm);


//--em,emb
   em_Branch->SetBranchAddress("pt1",  &pt1_em);
   em_Branch->SetBranchAddress("eta1", &eta1_em);
   em_Branch->SetBranchAddress("phi1", &phi1_em);
   em_Branch->SetBranchAddress("vx1",  &vx1_em);
   em_Branch->SetBranchAddress("vy1",  &vy1_em);
   em_Branch->SetBranchAddress("pt2",  &pt2_em);
   em_Branch->SetBranchAddress("eta2", &eta2_em);
   em_Branch->SetBranchAddress("phi2", &phi2_em);
   em_Branch->SetBranchAddress("vx2",  &vx2_em);
   em_Branch->SetBranchAddress("vy2",  &vy2_em);
   em_Branch->SetBranchAddress("Nj",   &Nj_em);
   em_Branch->SetBranchAddress("Nak8j",&Nak8j_em);
   em_Branch->SetBranchAddress("missET",&missET_em);

   emb_Branch->SetBranchAddress("pt1",  &pt1_em);
   emb_Branch->SetBranchAddress("eta1", &eta1_em);
   emb_Branch->SetBranchAddress("phi1", &phi1_em);
   emb_Branch->SetBranchAddress("vx1",  &vx1_em);
   emb_Branch->SetBranchAddress("vy1",  &vy1_em);
   emb_Branch->SetBranchAddress("pt2",  &pt2_em);
   emb_Branch->SetBranchAddress("eta2", &eta2_em);
   emb_Branch->SetBranchAddress("phi2", &phi2_em);
   emb_Branch->SetBranchAddress("vx2",  &vx2_em);
   emb_Branch->SetBranchAddress("vy2",  &vy2_em);
   emb_Branch->SetBranchAddress("Nj",   &Nj_em);
   emb_Branch->SetBranchAddress("Nak8j",&Nak8j_em);
   emb_Branch->SetBranchAddress("missET",&missET_em);

   emb2_Branch->SetBranchAddress("pt1",  &pt1_em);
   emb2_Branch->SetBranchAddress("eta1", &eta1_em);
   emb2_Branch->SetBranchAddress("phi1", &phi1_em);
   emb2_Branch->SetBranchAddress("vx1",  &vx1_em);
   emb2_Branch->SetBranchAddress("vy1",  &vy1_em);
   emb2_Branch->SetBranchAddress("pt2",  &pt2_em);
   emb2_Branch->SetBranchAddress("eta2", &eta2_em);
   emb2_Branch->SetBranchAddress("phi2", &phi2_em);
   emb2_Branch->SetBranchAddress("vx2",  &vx2_em);
   emb2_Branch->SetBranchAddress("vy2",  &vy2_em);
   emb2_Branch->SetBranchAddress("Nj",   &Nj_em);
   emb2_Branch->SetBranchAddress("Nak8j",&Nak8j_em);
   emb2_Branch->SetBranchAddress("missET",&missET_em);

   emb3_Branch->SetBranchAddress("pt1",  &pt1_em);
   emb3_Branch->SetBranchAddress("eta1", &eta1_em);
   emb3_Branch->SetBranchAddress("phi1", &phi1_em);
   emb3_Branch->SetBranchAddress("vx1",  &vx1_em);
   emb3_Branch->SetBranchAddress("vy1",  &vy1_em);
   emb3_Branch->SetBranchAddress("pt2",  &pt2_em);
   emb3_Branch->SetBranchAddress("eta2", &eta2_em);
   emb3_Branch->SetBranchAddress("phi2", &phi2_em);
   emb3_Branch->SetBranchAddress("vx2",  &vx2_em);
   emb3_Branch->SetBranchAddress("vy2",  &vy2_em);
   emb3_Branch->SetBranchAddress("Nj",   &Nj_em);
   emb3_Branch->SetBranchAddress("Nak8j",&Nak8j_em);
   emb3_Branch->SetBranchAddress("missET",&missET_em);

   emb4_Branch->SetBranchAddress("pt1",  &pt1_em);
   emb4_Branch->SetBranchAddress("eta1", &eta1_em);
   emb4_Branch->SetBranchAddress("phi1", &phi1_em);
   emb4_Branch->SetBranchAddress("vx1",  &vx1_em);
   emb4_Branch->SetBranchAddress("vy1",  &vy1_em);
   emb4_Branch->SetBranchAddress("pt2",  &pt2_em);
   emb4_Branch->SetBranchAddress("eta2", &eta2_em);
   emb4_Branch->SetBranchAddress("phi2", &phi2_em);
   emb4_Branch->SetBranchAddress("vx2",  &vx2_em);
   emb4_Branch->SetBranchAddress("vy2",  &vy2_em);
   emb4_Branch->SetBranchAddress("Nj",   &Nj_em);
   emb4_Branch->SetBranchAddress("Nak8j",&Nak8j_em);
   emb4_Branch->SetBranchAddress("missET",&missET_em);

//  
//-- simu branch
   simu->Branch("pt1",   &pt1_ee,   "pt1/F");
   simu->Branch("eta1",  &eta1_ee,  "eta1/F");
   simu->Branch("phi1",  &phi1_ee,  "phi1/F");
   simu->Branch("vx1",   &vx1_ee,   "vx1/F");
   simu->Branch("vy1",   &vy1_ee,   "vy1/F");
   simu->Branch("pt2",   &pt2_ee,   "pt2/F");
   simu->Branch("eta2",  &eta2_ee,  "eta2/F");
   simu->Branch("phi2",  &phi2_ee,  "phi2/F");
   simu->Branch("vx2",   &vx2_ee,   "vx2/F");
   simu->Branch("vy2",   &vy2_ee,   "vy2/F");
   simu->Branch("Nj",    &Nj_ee,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_ee, "Nak8j/F");
   simu->Branch("missET",&missET_ee,"missET/F");

   simu->Branch("pt1",   &pt1_mm,   "pt1/F");
   simu->Branch("eta1",  &eta1_mm,  "eta1/F");
   simu->Branch("phi1",  &phi1_mm,  "phi1/F");
   simu->Branch("vx1",   &vx1_mm,   "vx1/F");
   simu->Branch("vy1",   &vy1_mm,   "vy1/F");
   simu->Branch("pt2",   &pt2_mm,   "pt2/F");
   simu->Branch("eta2",  &eta2_mm,  "eta2/F");
   simu->Branch("phi2",  &phi2_mm,  "phi2/F");
   simu->Branch("vx2",   &vx2_mm,   "vx2/F");
   simu->Branch("vy2",   &vy2_mm,   "vy2/F");
   simu->Branch("Nj",    &Nj_mm,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_mm, "Nak8j/F");
   simu->Branch("missET",&missET_mm,"missET/F");

   simu->Branch("pt1",   &pt1_em,   "pt1/F");
   simu->Branch("eta1",  &eta1_em,  "eta1/F");
   simu->Branch("phi1",  &phi1_em,  "phi1/F");
   simu->Branch("vx1",   &vx1_em,   "vx1/F");
   simu->Branch("vy1",   &vy1_em,   "vy1/F");
   simu->Branch("pt2",   &pt2_em,   "pt2/F");
   simu->Branch("eta2",  &eta2_em,  "eta2/F");
   simu->Branch("phi2",  &phi2_em,  "phi2/F");
   simu->Branch("vx2",   &vx2_em,   "vx2/F");
   simu->Branch("vy2",   &vy2_em,   "vy2/F");
   simu->Branch("Nj",    &Nj_em,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_em, "Nak8j/F");
   simu->Branch("missET",&missET_em,"missET/F");

   simu->Branch("type",   &type,   "type/I");

//--type signal and background: 1-signal, 0-background
   Int_t i;
   type = 1;
   for(i = 0; i < ee_Branch->GetEntries(); i++) {
      ee_Branch->GetEntry(i);
      simu->Fill();
   }
//eeb
   type = 0;
   for(i = 0; i < eeb_Branch->GetEntries(); i++) {
      eeb_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < eeb2_Branch->GetEntries(); i++) {
      eeb2_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < eeb3_Branch->GetEntries(); i++) {
      eeb3_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < eeb4_Branch->GetEntries(); i++) {
      eeb4_Branch->GetEntry(i);
      simu->Fill();
   }


   type = 1;
   for(i = 0; i < mm_Branch->GetEntries(); i++) {
      mm_Branch->GetEntry(i);
      simu->Fill();
   }
//mmb
   type = 0;
   for(i = 0; i < mmb_Branch->GetEntries(); i++) {
      mmb_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < mmb2_Branch->GetEntries(); i++) {
      mmb2_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < mmb3_Branch->GetEntries(); i++) {
      mmb3_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < mmb4_Branch->GetEntries(); i++) {
      mmb4_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 1;
   for(i = 0; i < em_Branch->GetEntries(); i++) {
      em_Branch->GetEntry(i);
      simu->Fill();
   }
//emb
   type = 0;
   for(i = 0; i < emb_Branch->GetEntries(); i++) {
      emb_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < emb2_Branch->GetEntries(); i++) {
      emb2_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < emb3_Branch->GetEntries(); i++) {
      emb3_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < emb4_Branch->GetEntries(); i++) {
      emb4_Branch->GetEntry(i);
      simu->Fill();
   }
//
   
   //-- train NN
   TMultiLayerPerceptron *mlp = new TMultiLayerPerceptron("@pt1,@eta1,@phi1,@vx1,@vy1,@pt2,@eta2,@phi2,@vx2,@vy2,@Nj,@Nak8j,@missET:8:6:@type",simu,"Entry$%2","(Entry$+1)%2");   
   mlp->Train(ntrain, "text,graph,update=10");
   mlp->Export("test", "python");

   //-- Use TMLPAnalyzer to see what it looks for
   TCanvas* mlpa_canvas = new TCanvas("mlpa_canvas","Network analysis SUSY");
   mlpa_canvas->Divide(2,2);
   TMLPAnalyzer ana(mlp);
   //--Initialization
   ana.GatherInformations();
   //--output to the console
   ana.CheckNetwork();
     
   //--show how each var affects the network
   mlpa_canvas->cd(1);
   ana.DrawDInputs();

   //--show the network structure 
   mlpa_canvas->cd(2);
   mlp->Draw();

   //--draw the resulting network
   mlpa_canvas->cd(3);
   ana.DrawNetwork(0, "type==1", "type==0");

   //-- Use the NN to plot the results for each sample
   mlpa_canvas->cd(4);
   TH1F* MLPee = new TH1F("MLPeeh", "NN output", 50, -.5, 1.5);
   TH1F* MLPeeb = new TH1F("MLPeebh", "NNb output", 50, -.5, 1.5);

   TH1F* MLPmm = new TH1F("MLPmmh", "NNm output", 50, -.5, 1.5);
   TH1F* MLPmmb = new TH1F("MLPmmbh", "NNmb output", 50, -.5, 1.5);

   TH1F* MLPem = new TH1F("MLPemh", "NNem output", 50, -.5, 1.5);
   TH1F* MLPemb = new TH1F("MLPembh", "NNemb output", 50, -.5, 1.5);

   MLPee->SetDirectory(0);
   MLPeeb->SetDirectory(0);
   MLPmm->SetDirectory(0);
   MLPmmb->SetDirectory(0);
   MLPem->SetDirectory(0);
   MLPemb->SetDirectory(0);
   
//--feeding to NN
//--ee
   Double_t params[13];
   Double_t paramsb[13];
   for(i = 0; i < ee_Branch->GetEntries(); i++) {
      ee_Branch->GetEntry(i);

      params[0] = pt1_ee;
      params[1] = eta1_ee;
      params[2] = phi1_ee;
      params[3] = vx1_ee;
      params[4] = vy1_ee;
      params[5] = pt2_ee;
      params[6] = eta2_ee;
      params[7] = phi2_ee;
      params[8] = vx2_ee;
      params[9] = vy2_ee;
      params[10] = Nj_ee;
      params[11] = Nak8j_ee;
      params[12] = missET_ee;
      MLPee->Fill(mlp->Evaluate(0, params));
   }
//
//--eeb
   for(i = 0; i < eeb_Branch->GetEntries(); i++) {
      eeb_Branch->GetEntry(i);

      paramsb[0] = pt1_ee;
      paramsb[1] = eta1_ee;
      paramsb[2] = phi1_ee;
      paramsb[3] = vx1_ee;
      paramsb[4] = vy1_ee;
      paramsb[5] = pt2_ee;
      paramsb[6] = eta2_ee;
      paramsb[7] = phi2_ee;
      paramsb[8] = vx2_ee;
      paramsb[9] = vy2_ee;
      paramsb[10] = Nj_ee;
      paramsb[11] = Nak8j_ee;
      paramsb[12] = missET_ee;
      MLPeeb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < eeb2_Branch->GetEntries(); i++) {
      eeb2_Branch->GetEntry(i);

      paramsb[0] = pt1_ee;
      paramsb[1] = eta1_ee;
      paramsb[2] = phi1_ee;
      paramsb[3] = vx1_ee;
      paramsb[4] = vy1_ee;
      paramsb[5] = pt2_ee;
      paramsb[6] = eta2_ee;
      paramsb[7] = phi2_ee;
      paramsb[8] = vx2_ee;
      paramsb[9] = vy2_ee;
      paramsb[10] = Nj_ee;
      paramsb[11] = Nak8j_ee;
      paramsb[12] = missET_ee;
      MLPeeb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < eeb3_Branch->GetEntries(); i++) {
      eeb3_Branch->GetEntry(i);

      paramsb[0] = pt1_ee;
      paramsb[1] = eta1_ee;
      paramsb[2] = phi1_ee;
      paramsb[3] = vx1_ee;
      paramsb[4] = vy1_ee;
      paramsb[5] = pt2_ee;
      paramsb[6] = eta2_ee;
      paramsb[7] = phi2_ee;
      paramsb[8] = vx2_ee;
      paramsb[9] = vy2_ee;
      paramsb[10] = Nj_ee;
      paramsb[11] = Nak8j_ee;
      paramsb[12] = missET_ee;
      MLPeeb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < eeb4_Branch->GetEntries(); i++) {
      eeb4_Branch->GetEntry(i);

      paramsb[0] = pt1_ee;
      paramsb[1] = eta1_ee;
      paramsb[2] = phi1_ee;
      paramsb[3] = vx1_ee;
      paramsb[4] = vy1_ee;
      paramsb[5] = pt2_ee;
      paramsb[6] = eta2_ee;
      paramsb[7] = phi2_ee;
      paramsb[8] = vx2_ee;
      paramsb[9] = vy2_ee;
      paramsb[10] = Nj_ee;
      paramsb[11] = Nak8j_ee;
      paramsb[12] = missET_ee;
      MLPeeb->Fill(mlp->Evaluate(0, paramsb));
   } 


//--mm
   Double_t paramsmm[13];
   Double_t paramsmmb[13];
   for(i = 0; i < mm_Branch->GetEntries(); i++) {
      mm_Branch->GetEntry(i);

      paramsmm[0] = pt1_mm;
      paramsmm[1] = eta1_mm;
      paramsmm[2] = phi1_mm;
      paramsmm[3] = vx1_mm;
      paramsmm[4] = vy1_mm;
      paramsmm[5] = pt2_mm;
      paramsmm[6] = eta2_mm;
      paramsmm[7] = phi2_mm;
      paramsmm[8] = vx2_mm;
      paramsmm[9] = vy2_mm;
      paramsmm[10] = Nj_mm;
      paramsmm[11] = Nak8j_mm;
      paramsmm[12] = missET_mm;
      MLPmm->Fill(mlp->Evaluate(0, paramsmm));
   }
//
//--mmb
   for(i = 0; i < mmb_Branch->GetEntries(); i++) {
      mmb_Branch->GetEntry(i);

      paramsmmb[0] = pt1_mm;
      paramsmmb[1] = eta1_mm;
      paramsmmb[2] = phi1_mm;
      paramsmmb[3] = vx1_mm;
      paramsmmb[4] = vy1_mm;
      paramsmmb[5] = pt2_mm;
      paramsmmb[6] = eta2_mm;
      paramsmmb[7] = phi2_mm;
      paramsmmb[8] = vx2_mm;
      paramsmmb[9] = vy2_mm;
      paramsmmb[10] = Nj_mm;
      paramsmmb[11] = Nak8j_mm;
      paramsmmb[12] = missET_mm;
      MLPmmb->Fill(mlp->Evaluate(0, paramsmmb));
   } 

   for(i = 0; i < mmb2_Branch->GetEntries(); i++) {
      mmb2_Branch->GetEntry(i);

      paramsb[0] = pt1_mm;
      paramsb[1] = eta1_mm;
      paramsb[2] = phi1_mm;
      paramsb[3] = vx1_mm;
      paramsb[4] = vy1_mm;
      paramsb[5] = pt2_mm;
      paramsb[6] = eta2_mm;
      paramsb[7] = phi2_mm;
      paramsb[8] = vx2_mm;
      paramsb[9] = vy2_mm;
      paramsb[10] = Nj_mm;
      paramsb[11] = Nak8j_mm;
      paramsb[12] = missET_mm;
      MLPmmb->Fill(mlp->Evaluate(0, paramsmmb));
   } 

   for(i = 0; i < mmb3_Branch->GetEntries(); i++) {
      mmb3_Branch->GetEntry(i);

      paramsb[0] = pt1_mm;
      paramsb[1] = eta1_mm;
      paramsb[2] = phi1_mm;
      paramsb[3] = vx1_mm;
      paramsb[4] = vy1_mm;
      paramsb[5] = pt2_mm;
      paramsb[6] = eta2_mm;
      paramsb[7] = phi2_mm;
      paramsb[8] = vx2_mm;
      paramsb[9] = vy2_mm;
      paramsb[10] = Nj_mm;
      paramsb[11] = Nak8j_mm;
      paramsb[12] = missET_mm;
      MLPmmb->Fill(mlp->Evaluate(0, paramsmmb));
   } 

   for(i = 0; i < mmb4_Branch->GetEntries(); i++) {
      mmb4_Branch->GetEntry(i);

      paramsb[0] = pt1_mm;
      paramsb[1] = eta1_mm;
      paramsb[2] = phi1_mm;
      paramsb[3] = vx1_mm;
      paramsb[4] = vy1_mm;
      paramsb[5] = pt2_mm;
      paramsb[6] = eta2_mm;
      paramsb[7] = phi2_mm;
      paramsb[8] = vx2_mm;
      paramsb[9] = vy2_mm;
      paramsb[10] = Nj_mm;
      paramsb[11] = Nak8j_mm;
      paramsb[12] = missET_mm;
      MLPmmb->Fill(mlp->Evaluate(0, paramsmmb));
   } 
//


//--em
   Double_t paramsem[13];
   Double_t paramsemb[13];
   for(i = 0; i < em_Branch->GetEntries(); i++) {
      em_Branch->GetEntry(i);

      paramsem[0] = pt1_em;
      paramsem[1] = eta1_em;
      paramsem[2] = phi1_em;
      paramsem[3] = vx1_em;
      paramsem[4] = vy1_em;
      paramsem[5] = pt2_em;
      paramsem[6] = eta2_em;
      paramsem[7] = phi2_em;
      paramsem[8] = vx2_em;
      paramsem[9] = vy2_em;
      paramsem[10] = Nj_em;
      paramsem[11] = Nak8j_em;
      paramsem[12] = missET_em;
      MLPem->Fill(mlp->Evaluate(0, paramsem));
   }
//
//--emb
   for(i = 0; i < emb_Branch->GetEntries(); i++) {
      emb_Branch->GetEntry(i);

      paramsemb[0] = pt1_em;
      paramsemb[1] = eta1_em;
      paramsemb[2] = phi1_em;
      paramsemb[3] = vx1_em;
      paramsemb[4] = vy1_em;
      paramsemb[5] = pt2_em;
      paramsemb[6] = eta2_em;
      paramsemb[7] = phi2_em;
      paramsemb[8] = vx2_em;
      paramsemb[9] = vy2_em;
      paramsemb[10] = Nj_em;
      paramsemb[11] = Nak8j_em;
      paramsemb[12] = missET_em;
      MLPemb->Fill(mlp->Evaluate(0, paramsemb));
   }

   for(i = 0; i < emb2_Branch->GetEntries(); i++) {
      emb2_Branch->GetEntry(i);

      paramsemb[0] = pt1_em;
      paramsemb[1] = eta1_em;
      paramsemb[2] = phi1_em;
      paramsemb[3] = vx1_em;
      paramsemb[4] = vy1_em;
      paramsemb[5] = pt2_em;
      paramsemb[6] = eta2_em;
      paramsemb[7] = phi2_em;
      paramsemb[8] = vx2_em;
      paramsemb[9] = vy2_em;
      paramsemb[10] = Nj_em;
      paramsemb[11] = Nak8j_em;
      paramsemb[12] = missET_em;
      MLPemb->Fill(mlp->Evaluate(0, paramsemb));
   } 

   for(i = 0; i < emb3_Branch->GetEntries(); i++) {
      emb3_Branch->GetEntry(i);

      paramsemb[0] = pt1_em;
      paramsemb[1] = eta1_em;
      paramsemb[2] = phi1_em;
      paramsemb[3] = vx1_em;
      paramsemb[4] = vy1_em;
      paramsemb[5] = pt2_em;
      paramsemb[6] = eta2_em;
      paramsemb[7] = phi2_em;
      paramsemb[8] = vx2_em;
      paramsemb[9] = vy2_em;
      paramsemb[10] = Nj_em;
      paramsemb[11] = Nak8j_em;
      paramsemb[12] = missET_em;
      MLPemb->Fill(mlp->Evaluate(0, paramsemb));
   } 

   for(i = 0; i < emb4_Branch->GetEntries(); i++) {
      emb4_Branch->GetEntry(i);

      paramsemb[0] = pt1_em;
      paramsemb[1] = eta1_em;
      paramsemb[2] = phi1_em;
      paramsemb[3] = vx1_em;
      paramsemb[4] = vy1_em;
      paramsemb[5] = pt2_em;
      paramsemb[6] = eta2_em;
      paramsemb[7] = phi2_em;
      paramsemb[8] = vx2_em;
      paramsemb[9] = vy2_em;
      paramsemb[10] = Nj_em;
      paramsemb[11] = Nak8j_em;
      paramsemb[12] = missET_em;
      MLPemb->Fill(mlp->Evaluate(0, paramsemb));
   } 
//
   signalStyling(MLPee);
   backgroundStyling(MLPeeb);
   signalStyling(MLPmm);
   backgroundStyling(MLPmmb);
   signalStyling(MLPem);
   backgroundStyling(MLPemb);

   MLPee->SetStats(0);
   MLPeeb->SetStats(0);

   MLPmm->SetStats(0);
   MLPmmb->SetStats(0);

   MLPem->SetStats(0);
   MLPemb->SetStats(0);
   
   MLPee->Draw();
   MLPeeb->Draw("same");
   MLPmm->Draw("same");
   MLPmmb->Draw("same");
   MLPem->Draw("same");
   MLPemb->Draw("same");

   TLegend *legend = new TLegend(.75, .80, .95, .95);
   legend->AddEntry(MLPee, "ee");
   legend->AddEntry(MLPeeb, "eeb");
   legend->AddEntry(MLPmm, "mm");
   legend->AddEntry(MLPmmb, "mmb");
   legend->AddEntry(MLPem, "em");
   legend->AddEntry(MLPemb, "emb");
   legend->Draw();
   mlpa_canvas->cd(0);

   delete input;

//
}

