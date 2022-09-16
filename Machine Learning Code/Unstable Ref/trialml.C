//--all input, with diagrams, ee mm branches, seperate variables, 2 data sets, not normalize

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

void trialml(Int_t ntrain = 100) {
   const char* fname = "outputNtuple_tt.root";
   const char* fname2 = "outputNtuple_DY.root";

   TFile* input = 0;
   TFile* input2 = 0;

   if(!gSystem->AccessPathName(fname) && !gSystem->AccessPathName(fname2)) {
      input = TFile::Open(fname);
      input2 = TFile::Open(fname2);
   }
   else {
      printf("Cannot find the file");
      return;
   }
//
   TTree* ee_Branch = (TTree*) input->Get("ee_Branch");
   TTree* eeb_Branch = (TTree*) input2->Get("ee_Branch");

   TTree* mm_Branch = (TTree*) input->Get("mm_Branch");
   TTree* mmb_Branch = (TTree*) input2->Get("mm_Branch");


   TFile* ofile = new TFile("output_ML","RECREATE");
   TTree *simu = new TTree("MonteCarlo", "Filtered Monte Carlo Events");

   //--ee
   Float_t pt1_ee, eta1_ee, phi1_ee, vx1_ee, vy1_ee;
   Float_t pt2_ee, eta2_ee, phi2_ee, vx2_ee, vy2_ee;
   Float_t Nj_ee, Nak8j_ee, missET_ee;

   Float_t pt1_eeb, eta1_eeb, phi1_eeb, vx1_eeb, vy1_eeb;
   Float_t pt2_eeb, eta2_eeb, phi2_eeb, vx2_eeb, vy2_eeb;
   Float_t Nj_eeb, Nak8j_eeb, missET_eeb;

   //--mm
   Float_t pt1_mm, eta1_mm, phi1_mm, vx1_mm, vy1_mm;
   Float_t pt2_mm, eta2_mm, phi2_mm, vx2_mm, vy2_mm;
   Float_t Nj_mm, Nak8j_mm, missET_mm;

   Float_t pt1_mmb, eta1_mmb, phi1_mmb, vx1_mmb, vy1_mmb;
   Float_t pt2_mmb, eta2_mmb, phi2_mmb, vx2_mmb, vy2_mmb;
   Float_t Nj_mmb, Nak8j_mmb, missET_mmb;

   Float_t Nmu, type;

//-- set branches
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

   eeb_Branch->SetBranchAddress("pt1",  &pt1_eeb);
   eeb_Branch->SetBranchAddress("eta1", &eta1_eeb);
   eeb_Branch->SetBranchAddress("phi1", &phi1_eeb);
   eeb_Branch->SetBranchAddress("vx1",  &vx1_eeb);
   eeb_Branch->SetBranchAddress("vy1",  &vy1_eeb);
   eeb_Branch->SetBranchAddress("pt2",  &pt2_eeb);
   eeb_Branch->SetBranchAddress("eta2", &eta2_eeb);
   eeb_Branch->SetBranchAddress("phi2", &phi2_eeb);
   eeb_Branch->SetBranchAddress("vx2",  &vx2_eeb);
   eeb_Branch->SetBranchAddress("vy2",  &vy2_eeb);
   eeb_Branch->SetBranchAddress("Nj",   &Nj_eeb);
   eeb_Branch->SetBranchAddress("Nak8j",&Nak8j_eeb);
   eeb_Branch->SetBranchAddress("missET",&missET_eeb);

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

   mmb_Branch->SetBranchAddress("pt1",  &pt1_mmb);
   mmb_Branch->SetBranchAddress("eta1", &eta1_mmb);
   mmb_Branch->SetBranchAddress("phi1", &phi1_mmb);
   mmb_Branch->SetBranchAddress("vx1",  &vx1_mmb);
   mmb_Branch->SetBranchAddress("vy1",  &vy1_mmb);
   mmb_Branch->SetBranchAddress("pt2",  &pt2_mmb);
   mmb_Branch->SetBranchAddress("eta2", &eta2_mmb);
   mmb_Branch->SetBranchAddress("phi2", &phi2_mmb);
   mmb_Branch->SetBranchAddress("vx2",  &vx2_mmb);
   mmb_Branch->SetBranchAddress("vy2",  &vy2_mmb);
   mmb_Branch->SetBranchAddress("Nj",   &Nj_mmb);
   mmb_Branch->SetBranchAddress("Nak8j",&Nak8j_mmb);
   mmb_Branch->SetBranchAddress("missET",&missET_mmb);

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

   simu->Branch("pt1",   &pt1_eeb,   "pt1/F");
   simu->Branch("eta1",  &eta1_eeb,  "eta1/F");
   simu->Branch("phi1",  &phi1_eeb,  "phi1/F");
   simu->Branch("vx1",   &vx1_eeb,   "vx1/F");
   simu->Branch("vy1",   &vy1_eeb,   "vy1/F");
   simu->Branch("pt2",   &pt2_eeb,   "pt2/F");
   simu->Branch("eta2",  &eta2_eeb,  "eta2/F");
   simu->Branch("phi2",  &phi2_eeb,  "phi2/F");
   simu->Branch("vx2",   &vx2_eeb,   "vx2/F");
   simu->Branch("vy2",   &vy2_eeb,   "vy2/F");
   simu->Branch("Nj",    &Nj_eeb,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_eeb, "Nak8j/F");
   simu->Branch("missET",&missET_eeb,"missET/F");

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

   simu->Branch("pt1",   &pt1_mmb,   "pt1/F");
   simu->Branch("eta1",  &eta1_mmb,  "eta1/F");
   simu->Branch("phi1",  &phi1_mmb,  "phi1/F");
   simu->Branch("vx1",   &vx1_mmb,   "vx1/F");
   simu->Branch("vy1",   &vy1_mmb,   "vy1/F");
   simu->Branch("pt2",   &pt2_mmb,   "pt2/F");
   simu->Branch("eta2",  &eta2_mmb,  "eta2/F");
   simu->Branch("phi2",  &phi2_mmb,  "phi2/F");
   simu->Branch("vx2",   &vx2_mmb,   "vx2/F");
   simu->Branch("vy2",   &vy2_mmb,   "vy2/F");
   simu->Branch("Nj",    &Nj_mmb,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_mmb, "Nak8j/F");
   simu->Branch("missET",&missET_mmb,"missET/F");

   simu->Branch("type",   &type,   "type/I");

//--type signal and background: 1-signal, 0-background
   Int_t i;
   type = 1;
   for(i = 0; i < ee_Branch->GetEntries(); i++) {
      ee_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < eeb_Branch->GetEntries(); i++) {
      eeb_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 1;
   for(i = 0; i < mm_Branch->GetEntries(); i++) {
      mm_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < mm_Branch->GetEntries(); i++) {
      mmb_Branch->GetEntry(i);
      simu->Fill();
   }
//

//--ee
   TH1F *hpt1_ee  = new TH1F("hpt1","pt1 distribution", 100, 0., 1200.);
   TH1F *heta1_ee  = new TH1F("heta1","eta1 distribution", 100,-3,3);
   TH1F *hphi1_ee  = new TH1F("hphi1","phi1 distribution", 100,-5,5);
   TH1F *hvx1_ee  = new TH1F("hvx1","vx1 distribution", 100,-0.5,0.5);
   TH1F *hvy1_ee  = new TH1F("hvy1","vy1 distribution", 100,-0.5,0.5);

   TH1F *hpt2_ee  = new TH1F("hpt2","pt2 distribution", 100, 0., 1200.);
   TH1F *heta2_ee  = new TH1F("heta2","eta2 distribution",100,-3,3);
   TH1F *hphi2_ee  = new TH1F("hphi2","phi2 distribution",100,-5,5);
   TH1F *hvx2_ee  = new TH1F("hvx2","vx2 distribution",100,-0.5,0.5);
   TH1F *hvy2_ee  = new TH1F("hvy2","vy2 distribution",100,-0.5,0.5);
   
   TH1F *hNj_ee = new TH1F("hNj", "Nj distribution", 11, 0., 11.);
   TH1F *hNak8j_ee = new TH1F("hNak8j", "Nak8j distribution", 11, 0., 11.);
   TH1F *hmissET_ee  = new TH1F("hmissET","missET distribution",100, 0., 8000.);

   
   TH1F *hpt1_eeb  = new TH1F("hpt1b","pt1 distribution", 100, 0., 1200.);
   TH1F *heta1_eeb  = new TH1F("heta1b","eta1 distribution", 100,-3,3);
   TH1F *hphi1_eeb  = new TH1F("hphi1b","phi1 distribution", 100,-5,5);
   TH1F *hvx1_eeb  = new TH1F("hvx1b","vx1 distribution", 100,-0.5,0.5);
   TH1F *hvy1_eeb  = new TH1F("hvy1b","vy1 distribution", 100,-0.5,0.5);

   TH1F *hpt2_eeb  = new TH1F("hpt2b","pt2 distribution", 100, 0., 1200.);
   TH1F *heta2_eeb  = new TH1F("heta2b","eta2 distribution",100,-3,3);
   TH1F *hphi2_eeb  = new TH1F("hphi2b","phi2 distribution",100,-5,5);
   TH1F *hvx2_eeb  = new TH1F("hvx2b","vx2 distribution",100,-0.5,0.5);
   TH1F *hvy2_eeb  = new TH1F("hvy2b","vy2 distribution",100,-0.5,0.5);
   
   TH1F *hNj_eeb = new TH1F("hNjb", "Nj distribution", 11, 0., 11.);
   TH1F *hNak8j_eeb = new TH1F("hNak8jb", "Nak8j distribution", 11, 0., 11.);
   TH1F *hmissET_eeb  = new TH1F("hmissETb","missET distribution",100, 0., 8000.);
//
//--mm
   TH1F *hpt1_mm  = new TH1F("hpt1_mm","pt1 distribution", 100, 0., 1200.);
   TH1F *heta1_mm  = new TH1F("heta1_mm","eta1 distribution",100,-3,3);
   TH1F *hphi1_mm  = new TH1F("hphi1_mm","phi1 distribution",100,-5,5);
   TH1F *hvx1_mm  = new TH1F("hvx1_mm","vx1 distribution",100,-0.5,0.5);
   TH1F *hvy1_mm  = new TH1F("hvy1_mm","vy1 distribution",100,-0.5,0.5);

   TH1F *hpt2_mm  = new TH1F("hpt2_mm","pt2 distribution", 100, 0., 1200.);
   TH1F *heta2_mm  = new TH1F("heta2_mm","eta2 distribution",100,-3,3);
   TH1F *hphi2_mm  = new TH1F("hphi2_mm","phi2 distribution",100,-5,5);
   TH1F *hvx2_mm  = new TH1F("hvx2_mm","vx2 distribution",100,-0.5,0.5);
   TH1F *hvy2_mm  = new TH1F("hvy2_mm","vy2 distribution",100,-0.5,0.5);
   
   TH1F *hNj_mm = new TH1F("hNj_mm", "Nj distribution", 11, 0., 11.);
   TH1F *hNak8j_mm = new TH1F("hNak8j_mm", "Nak8j distribution", 11, 0., 11.);
   TH1F *hmissET_mm  = new TH1F("hmissET_mm","missET distribution",100, 0., 8000.);

   TH1F *hpt1_mmb  = new TH1F("hpt1_mmb","pt1 distribution", 100, 0., 1200.);
   TH1F *heta1_mmb  = new TH1F("heta1_mmb","eta1 distribution",100,-3,3);
   TH1F *hphi1_mmb  = new TH1F("hphi1_mmb","phi1 distribution",100,-5,5);
   TH1F *hvx1_mmb  = new TH1F("hvx1_mmb","vx1 distribution",100,-0.5,0.5);
   TH1F *hvy1_mmb  = new TH1F("hvy1_mmb","vy1 distribution",100,-0.5,0.5);

   TH1F *hpt2_mmb  = new TH1F("hpt2_mmb","pt2 distribution", 100, 0., 1200.);
   TH1F *heta2_mmb  = new TH1F("heta2_mmb","eta2 distribution",100,-3,3);
   TH1F *hphi2_mmb  = new TH1F("hphi2_mmb","phi2 distribution",100,-5,5);
   TH1F *hvx2_mmb  = new TH1F("hvx2_mmb","vx2 distribution",100,-0.5,0.5);
   TH1F *hvy2_mmb  = new TH1F("hvy2_mmb","vy2 distribution",100,-0.5,0.5);
   
   TH1F *hNj_mmb = new TH1F("hNj_mmb", "Nj distribution", 11, 0., 11.);
   TH1F *hNak8j_mmb = new TH1F("hNak8j_mmb", "Nak8j distribution", 11, 0., 11.);
   TH1F *hmissET_mmb  = new TH1F("hmissET_mmb","missET distribution",100, 0., 8000.);

//ee
   TCanvas *ee_canvas = new TCanvas("ee_canvas", "ee Data", 900, 700);
   ee_canvas->Divide(7,2,0,0);
   Int_t ee_entries = (Int_t) ee_Branch->GetEntries();

   for(Int_t i = 1; i <= 13; i++) {
      ee_canvas->cd(i);
      Int_t j;
      if(i == 1) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hpt1_ee->Fill(pt1_ee);
         }
         filler(hpt1_ee, "GeV");
      }

      if(i == 2) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            heta1_ee->Fill(eta1_ee);
         }
         filler(heta1_ee, "eta");
      }

      if(i == 3) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hphi1_ee->Fill(phi1_ee);
         }
         filler(hphi1_ee, "rad");
      }

      if(i == 4) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hvx1_ee->Fill(vx1_ee);
         }
         filler(hvx1_ee, "pos");
      }

      if(i == 5) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hvy1_ee->Fill(vy1_ee);
         }
         filler(hvy1_ee, "pos");
      }


      if(i == 6) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hpt2_ee->Fill(pt2_ee);
         }
         filler(hpt2_ee, "GV");
      }

      if(i == 7) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            heta2_ee->Fill(eta2_ee);
         }
         filler(heta2_ee, "eta");
      }

      if(i == 8) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hphi2_ee->Fill(phi2_ee);
         }
         filler(hphi2_ee, "rad");
      }

      if(i == 9) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hvx2_ee->Fill(vx2_ee);
         }
         filler(hvx2_ee, "pos");
      }

      if(i == 10) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hvy2_ee->Fill(vy2_ee);
         }
         filler(hvy2_ee, "pos");
      }

      if(i == 11) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hNj_ee->Fill(Nj_ee);
         }
         filler(hNj_ee, "number");
      }

      if(i == 12) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hNak8j_ee->Fill(Nak8j_ee);
         }
         filler(hNak8j_ee, "number");
      }

      if(i == 13) {
         for(j = 0; j < ee_entries; j++) {
            ee_Branch->GetEntry(j);
            hmissET_ee->Fill(missET_ee);
         }
         filler(hmissET_ee, "GV");
      }
   }
//eeb
   TCanvas *eeb_canvas = new TCanvas("eeb_canvas", "ee Background Data", 900, 700);
   eeb_canvas->Divide(7,2,0,0);
   Int_t eeb_entries = (Int_t) eeb_Branch->GetEntries();

   for(Int_t i = 1; i <= 13; i++) {
      eeb_canvas->cd(i);
      Int_t j;
      if(i == 1) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hpt1_eeb->Fill(pt1_eeb);
         }
         filler(hpt1_eeb, "GeV");
      }

      if(i == 2) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            heta1_eeb->Fill(eta1_eeb);
         }
         filler(heta1_eeb, "eta");
      }

      if(i == 3) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hphi1_eeb->Fill(phi1_eeb);
         }
         filler(hphi1_eeb, "rad");
      }

      if(i == 4) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvx1_eeb->Fill(vx1_eeb);
         }
         filler(hvx1_eeb, "pos");
      }

      if(i == 5) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvy1_eeb->Fill(vy1_eeb);
         }
         filler(hvy1_eeb, "pos");
      }


      if(i == 6) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hpt2_eeb->Fill(pt2_eeb);
         }
         filler(hpt2_eeb, "GV");
      }

      if(i == 7) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            heta2_eeb->Fill(eta2_eeb);
         }
         filler(heta2_eeb, "eta");
      }

      if(i == 8) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hphi2_eeb->Fill(phi2_eeb);
         }
         filler(hphi2_eeb, "rad");
      }

      if(i == 9) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvx2_eeb->Fill(vx2_eeb);
         }
         filler(hvx2_eeb, "pos");
      }

      if(i == 10) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvy2_eeb->Fill(vy2_eeb);
         }
         filler(hvy2_eeb, "pos");
      }

      if(i == 11) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hNj_eeb->Fill(Nj_eeb);
         }
         filler(hNj_eeb, "number");
      }

      if(i == 12) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hNak8j_eeb->Fill(Nak8j_eeb);
         }
         filler(hNak8j_eeb, "number");
      }

      if(i == 13) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hmissET_eeb->Fill(missET_eeb);
         }
         filler(hmissET_eeb, "GV");
      }
   }
   
   //-- train NN
   //TMultiLayerPerceptron* mlp = new TMultiLayerPerceptron("pt1,eta1,phi1,vx1:6::type",simu);
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

   MLPee->SetDirectory(0);
   MLPeeb->SetDirectory(0);
   MLPmm->SetDirectory(0);
   MLPmmb->SetDirectory(0);
   
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
      MLPee->Fill(mlp->Evaluate(1, params));
   }
//
//--eeb
   for(i = 0; i < eeb_Branch->GetEntries(); i++) {
      eeb_Branch->GetEntry(i);

      paramsb[0] = pt1_eeb;
      paramsb[1] = eta1_eeb;
      paramsb[2] = phi1_eeb;
      paramsb[3] = vx1_eeb;
      paramsb[4] = vy1_eeb;
      paramsb[5] = pt2_eeb;
      paramsb[6] = eta2_eeb;
      paramsb[7] = phi2_eeb;
      paramsb[8] = vx2_eeb;
      paramsb[9] = vy2_eeb;
      paramsb[10] = Nj_eeb;
      paramsb[11] = Nak8j_eeb;
      paramsb[12] = missET_eeb;
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
      MLPmm->Fill(mlp->Evaluate(1, paramsmm));
   }
//
//--mmb
   for(i = 0; i < mmb_Branch->GetEntries(); i++) {
      mmb_Branch->GetEntry(i);

      paramsmmb[0] = pt1_mmb;
      paramsmmb[1] = eta1_mmb;
      paramsmmb[2] = phi1_mmb;
      paramsmmb[3] = vx1_mmb;
      paramsmmb[4] = vy1_mmb;
      paramsmmb[5] = pt2_mmb;
      paramsmmb[6] = eta2_mmb;
      paramsmmb[7] = phi2_mmb;
      paramsmmb[8] = vx2_mmb;
      paramsmmb[9] = vy2_mmb;
      paramsmmb[10] = Nj_mmb;
      paramsmmb[11] = Nak8j_mmb;
      paramsmmb[12] = missET_mmb;
      MLPmmb->Fill(mlp->Evaluate(0, paramsmmb));
   } 
//
   signalStyling(MLPee);
   backgroundStyling(MLPeeb);
   signalStyling(MLPmm);
   backgroundStyling(MLPmmb);

   MLPee->SetStats(0);
   MLPeeb->SetStats(0);

   MLPmm->SetStats(0);
   MLPmmb->SetStats(0);
   
   MLPee->Draw();
   MLPeeb->Draw("same");

   MLPmm->Draw("same");
   MLPmmb->Draw("same");

   TLegend *legend = new TLegend(.75, .80, .95, .95);
   legend->AddEntry(MLPee, "ee");
   legend->AddEntry(MLPeeb, "eeb");
   legend->AddEntry(MLPmm, "mm");
   legend->AddEntry(MLPmmb, "mmb");
   legend->Draw();
   mlpa_canvas->cd(0);

   delete input;
}

