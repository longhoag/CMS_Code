//--all input, wo diagrams, ee mm em branches, seperate variables, all data sets, not normalize


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

void mtest(Int_t ntrain = 100) {
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

   Float_t pt1_eeb, eta1_eeb, phi1_eeb, vx1_eeb, vy1_eeb;
   Float_t pt2_eeb, eta2_eeb, phi2_eeb, vx2_eeb, vy2_eeb;
   Float_t Nj_eeb, Nak8j_eeb, missET_eeb;

   Float_t pt1_eeb2, eta1_eeb2, phi1_eeb2, vx1_eeb2, vy1_eeb2;
   Float_t pt2_eeb2, eta2_eeb2, phi2_eeb2, vx2_eeb2, vy2_eeb2;
   Float_t Nj_eeb2, Nak8j_eeb2, missET_eeb2;

   Float_t pt1_eeb3, eta1_eeb3, phi1_eeb3, vx1_eeb3, vy1_eeb3;
   Float_t pt2_eeb3, eta2_eeb3, phi2_eeb3, vx2_eeb3, vy2_eeb3;
   Float_t Nj_eeb3, Nak8j_eeb3, missET_eeb3;

   Float_t pt1_eeb4, eta1_eeb4, phi1_eeb4, vx1_eeb4, vy1_eeb4;
   Float_t pt2_eeb4, eta2_eeb4, phi2_eeb4, vx2_eeb4, vy2_eeb4;
   Float_t Nj_eeb4, Nak8j_eeb4, missET_eeb4;

   //--mm
   Float_t pt1_mm, eta1_mm, phi1_mm, vx1_mm, vy1_mm;
   Float_t pt2_mm, eta2_mm, phi2_mm, vx2_mm, vy2_mm;
   Float_t Nj_mm, Nak8j_mm, missET_mm;

   Float_t pt1_mmb, eta1_mmb, phi1_mmb, vx1_mmb, vy1_mmb;
   Float_t pt2_mmb, eta2_mmb, phi2_mmb, vx2_mmb, vy2_mmb;
   Float_t Nj_mmb, Nak8j_mmb, missET_mmb;

   Float_t pt1_mmb2, eta1_mmb2, phi1_mmb2, vx1_mmb2, vy1_mmb2;
   Float_t pt2_mmb2, eta2_mmb2, phi2_mmb2, vx2_mmb2, vy2_mmb2;
   Float_t Nj_mmb2, Nak8j_mmb2, missET_mmb2;

   Float_t pt1_mmb3, eta1_mmb3, phi1_mmb3, vx1_mmb3, vy1_mmb3;
   Float_t pt2_mmb3, eta2_mmb3, phi2_mmb3, vx2_mmb3, vy2_mmb3;
   Float_t Nj_mmb3, Nak8j_mmb3, missET_mmb3;

   Float_t pt1_mmb4, eta1_mmb4, phi1_mmb4, vx1_mmb4, vy1_mmb4;
   Float_t pt2_mmb4, eta2_mmb4, phi2_mmb4, vx2_mmb4, vy2_mmb4;
   Float_t Nj_mmb4, Nak8j_mmb4, missET_mmb4;

   //--em
   Float_t pt1_em, eta1_em, phi1_em, vx1_em, vy1_em;
   Float_t pt2_em, eta2_em, phi2_em, vx2_em, vy2_em;
   Float_t Nj_em, Nak8j_em, missET_em;

   Float_t pt1_emb, eta1_emb, phi1_emb, vx1_emb, vy1_emb;
   Float_t pt2_emb, eta2_emb, phi2_emb, vx2_emb, vy2_emb;
   Float_t Nj_emb, Nak8j_emb, missET_emb;

   Float_t pt1_emb2, eta1_emb2, phi1_emb2, vx1_emb2, vy1_emb2;
   Float_t pt2_emb2, eta2_emb2, phi2_emb2, vx2_emb2, vy2_emb2;
   Float_t Nj_emb2, Nak8j_emb2, missET_emb2;

   Float_t pt1_emb3, eta1_emb3, phi1_emb3, vx1_emb3, vy1_emb3;
   Float_t pt2_emb3, eta2_emb3, phi2_emb3, vx2_emb3, vy2_emb3;
   Float_t Nj_emb3, Nak8j_emb3, missET_emb3;

   Float_t pt1_emb4, eta1_emb4, phi1_emb4, vx1_emb4, vy1_emb4;
   Float_t pt2_emb4, eta2_emb4, phi2_emb4, vx2_emb4, vy2_emb4;
   Float_t Nj_emb4, Nak8j_emb4, missET_emb4;

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

   eeb2_Branch->SetBranchAddress("pt1",  &pt1_eeb2);
   eeb2_Branch->SetBranchAddress("eta1", &eta1_eeb2);
   eeb2_Branch->SetBranchAddress("phi1", &phi1_eeb2);
   eeb2_Branch->SetBranchAddress("vx1",  &vx1_eeb2);
   eeb2_Branch->SetBranchAddress("vy1",  &vy1_eeb2);
   eeb2_Branch->SetBranchAddress("pt2",  &pt2_eeb2);
   eeb2_Branch->SetBranchAddress("eta2", &eta2_eeb2);
   eeb2_Branch->SetBranchAddress("phi2", &phi2_eeb2);
   eeb2_Branch->SetBranchAddress("vx2",  &vx2_eeb2);
   eeb2_Branch->SetBranchAddress("vy2",  &vy2_eeb2);
   eeb2_Branch->SetBranchAddress("Nj",   &Nj_eeb2);
   eeb2_Branch->SetBranchAddress("Nak8j",&Nak8j_eeb2);
   eeb2_Branch->SetBranchAddress("missET",&missET_eeb2);

   eeb3_Branch->SetBranchAddress("pt1",  &pt1_eeb3);
   eeb3_Branch->SetBranchAddress("eta1", &eta1_eeb3);
   eeb3_Branch->SetBranchAddress("phi1", &phi1_eeb3);
   eeb3_Branch->SetBranchAddress("vx1",  &vx1_eeb3);
   eeb3_Branch->SetBranchAddress("vy1",  &vy1_eeb3);
   eeb3_Branch->SetBranchAddress("pt2",  &pt2_eeb3);
   eeb3_Branch->SetBranchAddress("eta2", &eta2_eeb3);
   eeb3_Branch->SetBranchAddress("phi2", &phi2_eeb3);
   eeb3_Branch->SetBranchAddress("vx2",  &vx2_eeb3);
   eeb3_Branch->SetBranchAddress("vy2",  &vy2_eeb3);
   eeb3_Branch->SetBranchAddress("Nj",   &Nj_eeb3);
   eeb3_Branch->SetBranchAddress("Nak8j",&Nak8j_eeb3);
   eeb3_Branch->SetBranchAddress("missET",&missET_eeb3);

   eeb4_Branch->SetBranchAddress("pt1",  &pt1_eeb4);
   eeb4_Branch->SetBranchAddress("eta1", &eta1_eeb4);
   eeb4_Branch->SetBranchAddress("phi1", &phi1_eeb4);
   eeb4_Branch->SetBranchAddress("vx1",  &vx1_eeb4);
   eeb4_Branch->SetBranchAddress("vy1",  &vy1_eeb4);
   eeb4_Branch->SetBranchAddress("pt2",  &pt2_eeb4);
   eeb4_Branch->SetBranchAddress("eta2", &eta2_eeb4);
   eeb4_Branch->SetBranchAddress("phi2", &phi2_eeb4);
   eeb4_Branch->SetBranchAddress("vx2",  &vx2_eeb4);
   eeb4_Branch->SetBranchAddress("vy2",  &vy2_eeb4);
   eeb4_Branch->SetBranchAddress("Nj",   &Nj_eeb4);
   eeb4_Branch->SetBranchAddress("Nak8j",&Nak8j_eeb4);
   eeb4_Branch->SetBranchAddress("missET",&missET_eeb4);
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

   mmb2_Branch->SetBranchAddress("pt1",  &pt1_mmb2);
   mmb2_Branch->SetBranchAddress("eta1", &eta1_mmb2);
   mmb2_Branch->SetBranchAddress("phi1", &phi1_mmb2);
   mmb2_Branch->SetBranchAddress("vx1",  &vx1_mmb2);
   mmb2_Branch->SetBranchAddress("vy1",  &vy1_mmb2);
   mmb2_Branch->SetBranchAddress("pt2",  &pt2_mmb2);
   mmb2_Branch->SetBranchAddress("eta2", &eta2_mmb2);
   mmb2_Branch->SetBranchAddress("phi2", &phi2_mmb2);
   mmb2_Branch->SetBranchAddress("vx2",  &vx2_mmb2);
   mmb2_Branch->SetBranchAddress("vy2",  &vy2_mmb2);
   mmb2_Branch->SetBranchAddress("Nj",   &Nj_mmb2);
   mmb2_Branch->SetBranchAddress("Nak8j",&Nak8j_mmb2);
   mmb2_Branch->SetBranchAddress("missET",&missET_mmb2);

   mmb3_Branch->SetBranchAddress("pt1",  &pt1_mmb3);
   mmb3_Branch->SetBranchAddress("eta1", &eta1_mmb3);
   mmb3_Branch->SetBranchAddress("phi1", &phi1_mmb3);
   mmb3_Branch->SetBranchAddress("vx1",  &vx1_mmb3);
   mmb3_Branch->SetBranchAddress("vy1",  &vy1_mmb3);
   mmb3_Branch->SetBranchAddress("pt2",  &pt2_mmb3);
   mmb3_Branch->SetBranchAddress("eta2", &eta2_mmb3);
   mmb3_Branch->SetBranchAddress("phi2", &phi2_mmb3);
   mmb3_Branch->SetBranchAddress("vx2",  &vx2_mmb3);
   mmb3_Branch->SetBranchAddress("vy2",  &vy2_mmb3);
   mmb3_Branch->SetBranchAddress("Nj",   &Nj_mmb3);
   mmb3_Branch->SetBranchAddress("Nak8j",&Nak8j_mmb3);
   mmb3_Branch->SetBranchAddress("missET",&missET_mmb3);

   mmb4_Branch->SetBranchAddress("pt1",  &pt1_mmb4);
   mmb4_Branch->SetBranchAddress("eta1", &eta1_mmb4);
   mmb4_Branch->SetBranchAddress("phi1", &phi1_mmb4);
   mmb4_Branch->SetBranchAddress("vx1",  &vx1_mmb4);
   mmb4_Branch->SetBranchAddress("vy1",  &vy1_mmb4);
   mmb4_Branch->SetBranchAddress("pt2",  &pt2_mmb4);
   mmb4_Branch->SetBranchAddress("eta2", &eta2_mmb4);
   mmb4_Branch->SetBranchAddress("phi2", &phi2_mmb4);
   mmb4_Branch->SetBranchAddress("vx2",  &vx2_mmb4);
   mmb4_Branch->SetBranchAddress("vy2",  &vy2_mmb4);
   mmb4_Branch->SetBranchAddress("Nj",   &Nj_mmb4);
   mmb4_Branch->SetBranchAddress("Nak8j",&Nak8j_mmb4);
   mmb4_Branch->SetBranchAddress("missET",&missET_mmb4);


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

   emb_Branch->SetBranchAddress("pt1",  &pt1_emb);
   emb_Branch->SetBranchAddress("eta1", &eta1_emb);
   emb_Branch->SetBranchAddress("phi1", &phi1_emb);
   emb_Branch->SetBranchAddress("vx1",  &vx1_emb);
   emb_Branch->SetBranchAddress("vy1",  &vy1_emb);
   emb_Branch->SetBranchAddress("pt2",  &pt2_emb);
   emb_Branch->SetBranchAddress("eta2", &eta2_emb);
   emb_Branch->SetBranchAddress("phi2", &phi2_emb);
   emb_Branch->SetBranchAddress("vx2",  &vx2_emb);
   emb_Branch->SetBranchAddress("vy2",  &vy2_emb);
   emb_Branch->SetBranchAddress("Nj",   &Nj_emb);
   emb_Branch->SetBranchAddress("Nak8j",&Nak8j_emb);
   emb_Branch->SetBranchAddress("missET",&missET_emb);

   emb2_Branch->SetBranchAddress("pt1",  &pt1_emb2);
   emb2_Branch->SetBranchAddress("eta1", &eta1_emb2);
   emb2_Branch->SetBranchAddress("phi1", &phi1_emb2);
   emb2_Branch->SetBranchAddress("vx1",  &vx1_emb2);
   emb2_Branch->SetBranchAddress("vy1",  &vy1_emb2);
   emb2_Branch->SetBranchAddress("pt2",  &pt2_emb2);
   emb2_Branch->SetBranchAddress("eta2", &eta2_emb2);
   emb2_Branch->SetBranchAddress("phi2", &phi2_emb2);
   emb2_Branch->SetBranchAddress("vx2",  &vx2_emb2);
   emb2_Branch->SetBranchAddress("vy2",  &vy2_emb2);
   emb2_Branch->SetBranchAddress("Nj",   &Nj_emb2);
   emb2_Branch->SetBranchAddress("Nak8j",&Nak8j_emb2);
   emb2_Branch->SetBranchAddress("missET",&missET_emb2);

   emb3_Branch->SetBranchAddress("pt1",  &pt1_emb3);
   emb3_Branch->SetBranchAddress("eta1", &eta1_emb3);
   emb3_Branch->SetBranchAddress("phi1", &phi1_emb3);
   emb3_Branch->SetBranchAddress("vx1",  &vx1_emb3);
   emb3_Branch->SetBranchAddress("vy1",  &vy1_emb3);
   emb3_Branch->SetBranchAddress("pt2",  &pt2_emb3);
   emb3_Branch->SetBranchAddress("eta2", &eta2_emb3);
   emb3_Branch->SetBranchAddress("phi2", &phi2_emb3);
   emb3_Branch->SetBranchAddress("vx2",  &vx2_emb3);
   emb3_Branch->SetBranchAddress("vy2",  &vy2_emb3);
   emb3_Branch->SetBranchAddress("Nj",   &Nj_emb3);
   emb3_Branch->SetBranchAddress("Nak8j",&Nak8j_emb3);
   emb3_Branch->SetBranchAddress("missET",&missET_emb3);

   emb4_Branch->SetBranchAddress("pt1",  &pt1_emb4);
   emb4_Branch->SetBranchAddress("eta1", &eta1_emb4);
   emb4_Branch->SetBranchAddress("phi1", &phi1_emb4);
   emb4_Branch->SetBranchAddress("vx1",  &vx1_emb4);
   emb4_Branch->SetBranchAddress("vy1",  &vy1_emb4);
   emb4_Branch->SetBranchAddress("pt2",  &pt2_emb4);
   emb4_Branch->SetBranchAddress("eta2", &eta2_emb4);
   emb4_Branch->SetBranchAddress("phi2", &phi2_emb4);
   emb4_Branch->SetBranchAddress("vx2",  &vx2_emb4);
   emb4_Branch->SetBranchAddress("vy2",  &vy2_emb4);
   emb4_Branch->SetBranchAddress("Nj",   &Nj_emb4);
   emb4_Branch->SetBranchAddress("Nak8j",&Nak8j_emb4);
   emb4_Branch->SetBranchAddress("missET",&missET_emb4);

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

   simu->Branch("pt1",   &pt1_eeb2,   "pt1/F");
   simu->Branch("eta1",  &eta1_eeb2,  "eta1/F");
   simu->Branch("phi1",  &phi1_eeb2,  "phi1/F");
   simu->Branch("vx1",   &vx1_eeb2,   "vx1/F");
   simu->Branch("vy1",   &vy1_eeb2,   "vy1/F");
   simu->Branch("pt2",   &pt2_eeb2,   "pt2/F");
   simu->Branch("eta2",  &eta2_eeb2,  "eta2/F");
   simu->Branch("phi2",  &phi2_eeb2,  "phi2/F");
   simu->Branch("vx2",   &vx2_eeb2,   "vx2/F");
   simu->Branch("vy2",   &vy2_eeb2,   "vy2/F");
   simu->Branch("Nj",    &Nj_eeb2,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_eeb2, "Nak8j/F");
   simu->Branch("missET",&missET_eeb2,"missET/F");

   simu->Branch("pt1",   &pt1_eeb3,   "pt1/F");
   simu->Branch("eta1",  &eta1_eeb3,  "eta1/F");
   simu->Branch("phi1",  &phi1_eeb3,  "phi1/F");
   simu->Branch("vx1",   &vx1_eeb3,   "vx1/F");
   simu->Branch("vy1",   &vy1_eeb3,   "vy1/F");
   simu->Branch("pt2",   &pt2_eeb3,   "pt2/F");
   simu->Branch("eta2",  &eta2_eeb3,  "eta2/F");
   simu->Branch("phi2",  &phi2_eeb3,  "phi2/F");
   simu->Branch("vx2",   &vx2_eeb3,   "vx2/F");
   simu->Branch("vy2",   &vy2_eeb3,   "vy2/F");
   simu->Branch("Nj",    &Nj_eeb3,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_eeb3, "Nak8j/F");
   simu->Branch("missET",&missET_eeb3,"missET/F");

   simu->Branch("pt1",   &pt1_eeb4,   "pt1/F");
   simu->Branch("eta1",  &eta1_eeb4,  "eta1/F");
   simu->Branch("phi1",  &phi1_eeb4,  "phi1/F");
   simu->Branch("vx1",   &vx1_eeb4,   "vx1/F");
   simu->Branch("vy1",   &vy1_eeb4,   "vy1/F");
   simu->Branch("pt2",   &pt2_eeb4,   "pt2/F");
   simu->Branch("eta2",  &eta2_eeb4,  "eta2/F");
   simu->Branch("phi2",  &phi2_eeb4,  "phi2/F");
   simu->Branch("vx2",   &vx2_eeb4,   "vx2/F");
   simu->Branch("vy2",   &vy2_eeb4,   "vy2/F");
   simu->Branch("Nj",    &Nj_eeb4,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_eeb4, "Nak8j/F");
   simu->Branch("missET",&missET_eeb4,"missET/F");

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

   simu->Branch("pt1",   &pt1_mmb2,   "pt1/F");
   simu->Branch("eta1",  &eta1_mmb2,  "eta1/F");
   simu->Branch("phi1",  &phi1_mmb2,  "phi1/F");
   simu->Branch("vx1",   &vx1_mmb2,   "vx1/F");
   simu->Branch("vy1",   &vy1_mmb2,   "vy1/F");
   simu->Branch("pt2",   &pt2_mmb2,   "pt2/F");
   simu->Branch("eta2",  &eta2_mmb2,  "eta2/F");
   simu->Branch("phi2",  &phi2_mmb2,  "phi2/F");
   simu->Branch("vx2",   &vx2_mmb2,   "vx2/F");
   simu->Branch("vy2",   &vy2_mmb2,   "vy2/F");
   simu->Branch("Nj",    &Nj_mmb2,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_mmb2, "Nak8j/F");
   simu->Branch("missET",&missET_mmb2,"missET/F");

   simu->Branch("pt1",   &pt1_mmb3,   "pt1/F");
   simu->Branch("eta1",  &eta1_mmb3,  "eta1/F");
   simu->Branch("phi1",  &phi1_mmb3,  "phi1/F");
   simu->Branch("vx1",   &vx1_mmb3,   "vx1/F");
   simu->Branch("vy1",   &vy1_mmb3,   "vy1/F");
   simu->Branch("pt2",   &pt2_mmb3,   "pt2/F");
   simu->Branch("eta2",  &eta2_mmb3,  "eta2/F");
   simu->Branch("phi2",  &phi2_mmb3,  "phi2/F");
   simu->Branch("vx2",   &vx2_mmb3,   "vx2/F");
   simu->Branch("vy2",   &vy2_mmb3,   "vy2/F");
   simu->Branch("Nj",    &Nj_mmb3,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_mmb3, "Nak8j/F");
   simu->Branch("missET",&missET_mmb3,"missET/F");

   simu->Branch("pt1",   &pt1_mmb4,   "pt1/F");
   simu->Branch("eta1",  &eta1_mmb4,  "eta1/F");
   simu->Branch("phi1",  &phi1_mmb4,  "phi1/F");
   simu->Branch("vx1",   &vx1_mmb4,   "vx1/F");
   simu->Branch("vy1",   &vy1_mmb4,   "vy1/F");
   simu->Branch("pt2",   &pt2_mmb4,   "pt2/F");
   simu->Branch("eta2",  &eta2_mmb4,  "eta2/F");
   simu->Branch("phi2",  &phi2_mmb4,  "phi2/F");
   simu->Branch("vx2",   &vx2_mmb4,   "vx2/F");
   simu->Branch("vy2",   &vy2_mmb4,   "vy2/F");
   simu->Branch("Nj",    &Nj_mmb4,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_mmb4, "Nak8j/F");
   simu->Branch("missET",&missET_mmb4,"missET/F");

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
   
   simu->Branch("pt1",   &pt1_emb,   "pt1/F");
   simu->Branch("eta1",  &eta1_emb,  "eta1/F");
   simu->Branch("phi1",  &phi1_emb,  "phi1/F");
   simu->Branch("vx1",   &vx1_emb,   "vx1/F");
   simu->Branch("vy1",   &vy1_emb,   "vy1/F");
   simu->Branch("pt2",   &pt2_emb,   "pt2/F");
   simu->Branch("eta2",  &eta2_emb,  "eta2/F");
   simu->Branch("phi2",  &phi2_emb,  "phi2/F");
   simu->Branch("vx2",   &vx2_emb,   "vx2/F");
   simu->Branch("vy2",   &vy2_emb,   "vy2/F");
   simu->Branch("Nj",    &Nj_emb,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_emb, "Nak8j/F");
   simu->Branch("missET",&missET_emb,"missET/F");

   simu->Branch("pt1",   &pt1_emb2,   "pt1/F");
   simu->Branch("eta1",  &eta1_emb2,  "eta1/F");
   simu->Branch("phi1",  &phi1_emb2,  "phi1/F");
   simu->Branch("vx1",   &vx1_emb2,   "vx1/F");
   simu->Branch("vy1",   &vy1_emb2,   "vy1/F");
   simu->Branch("pt2",   &pt2_emb2,   "pt2/F");
   simu->Branch("eta2",  &eta2_emb2,  "eta2/F");
   simu->Branch("phi2",  &phi2_emb2,  "phi2/F");
   simu->Branch("vx2",   &vx2_emb2,   "vx2/F");
   simu->Branch("vy2",   &vy2_emb2,   "vy2/F");
   simu->Branch("Nj",    &Nj_emb2,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_emb2, "Nak8j/F");
   simu->Branch("missET",&missET_emb2,"missET/F");

   simu->Branch("pt1",   &pt1_emb3,   "pt1/F");
   simu->Branch("eta1",  &eta1_emb3,  "eta1/F");
   simu->Branch("phi1",  &phi1_emb3,  "phi1/F");
   simu->Branch("vx1",   &vx1_emb3,   "vx1/F");
   simu->Branch("vy1",   &vy1_emb3,   "vy1/F");
   simu->Branch("pt2",   &pt2_emb3,   "pt2/F");
   simu->Branch("eta2",  &eta2_emb3,  "eta2/F");
   simu->Branch("phi2",  &phi2_emb3,  "phi2/F");
   simu->Branch("vx2",   &vx2_emb3,   "vx2/F");
   simu->Branch("vy2",   &vy2_emb3,   "vy2/F");
   simu->Branch("Nj",    &Nj_emb3,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_emb3, "Nak8j/F");
   simu->Branch("missET",&missET_emb3,"missET/F");

   simu->Branch("pt1",   &pt1_emb4,   "pt1/F");
   simu->Branch("eta1",  &eta1_emb4,  "eta1/F");
   simu->Branch("phi1",  &phi1_emb4,  "phi1/F");
   simu->Branch("vx1",   &vx1_emb4,   "vx1/F");
   simu->Branch("vy1",   &vy1_emb4,   "vy1/F");
   simu->Branch("pt2",   &pt2_emb4,   "pt2/F");
   simu->Branch("eta2",  &eta2_emb4,  "eta2/F");
   simu->Branch("phi2",  &phi2_emb4,  "phi2/F");
   simu->Branch("vx2",   &vx2_emb4,   "vx2/F");
   simu->Branch("vy2",   &vy2_emb4,   "vy2/F");
   simu->Branch("Nj",    &Nj_emb4,    "Nj/F");
   simu->Branch("Nak8j", &Nak8j_emb4, "Nak8j/F");
   simu->Branch("missET",&missET_emb4,"missET/F");

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

   for(i = 0; i < eeb2_Branch->GetEntries(); i++) {
      eeb2_Branch->GetEntry(i);

      paramsb[0] = pt1_eeb2;
      paramsb[1] = eta1_eeb2;
      paramsb[2] = phi1_eeb2;
      paramsb[3] = vx1_eeb2;
      paramsb[4] = vy1_eeb2;
      paramsb[5] = pt2_eeb2;
      paramsb[6] = eta2_eeb2;
      paramsb[7] = phi2_eeb2;
      paramsb[8] = vx2_eeb2;
      paramsb[9] = vy2_eeb2;
      paramsb[10] = Nj_eeb2;
      paramsb[11] = Nak8j_eeb2;
      paramsb[12] = missET_eeb2;
      MLPeeb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < eeb3_Branch->GetEntries(); i++) {
      eeb3_Branch->GetEntry(i);

      paramsb[0] = pt1_eeb3;
      paramsb[1] = eta1_eeb3;
      paramsb[2] = phi1_eeb3;
      paramsb[3] = vx1_eeb3;
      paramsb[4] = vy1_eeb3;
      paramsb[5] = pt2_eeb3;
      paramsb[6] = eta2_eeb3;
      paramsb[7] = phi2_eeb3;
      paramsb[8] = vx2_eeb3;
      paramsb[9] = vy2_eeb3;
      paramsb[10] = Nj_eeb3;
      paramsb[11] = Nak8j_eeb3;
      paramsb[12] = missET_eeb3;
      MLPeeb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < eeb4_Branch->GetEntries(); i++) {
      eeb4_Branch->GetEntry(i);

      paramsb[0] = pt1_eeb4;
      paramsb[1] = eta1_eeb4;
      paramsb[2] = phi1_eeb4;
      paramsb[3] = vx1_eeb4;
      paramsb[4] = vy1_eeb4;
      paramsb[5] = pt2_eeb4;
      paramsb[6] = eta2_eeb4;
      paramsb[7] = phi2_eeb4;
      paramsb[8] = vx2_eeb4;
      paramsb[9] = vy2_eeb4;
      paramsb[10] = Nj_eeb4;
      paramsb[11] = Nak8j_eeb4;
      paramsb[12] = missET_eeb4;
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

   for(i = 0; i < mmb2_Branch->GetEntries(); i++) {
      mmb2_Branch->GetEntry(i);

      paramsb[0] = pt1_mmb2;
      paramsb[1] = eta1_mmb2;
      paramsb[2] = phi1_mmb2;
      paramsb[3] = vx1_mmb2;
      paramsb[4] = vy1_mmb2;
      paramsb[5] = pt2_mmb2;
      paramsb[6] = eta2_mmb2;
      paramsb[7] = phi2_mmb2;
      paramsb[8] = vx2_mmb2;
      paramsb[9] = vy2_mmb2;
      paramsb[10] = Nj_mmb2;
      paramsb[11] = Nak8j_mmb2;
      paramsb[12] = missET_mmb2;
      MLPmmb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < mmb3_Branch->GetEntries(); i++) {
      mmb3_Branch->GetEntry(i);

      paramsb[0] = pt1_mmb3;
      paramsb[1] = eta1_mmb3;
      paramsb[2] = phi1_mmb3;
      paramsb[3] = vx1_mmb3;
      paramsb[4] = vy1_mmb3;
      paramsb[5] = pt2_mmb3;
      paramsb[6] = eta2_mmb3;
      paramsb[7] = phi2_mmb3;
      paramsb[8] = vx2_mmb3;
      paramsb[9] = vy2_mmb3;
      paramsb[10] = Nj_mmb3;
      paramsb[11] = Nak8j_mmb3;
      paramsb[12] = missET_mmb3;
      MLPmmb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < mmb4_Branch->GetEntries(); i++) {
      mmb4_Branch->GetEntry(i);

      paramsb[0] = pt1_mmb4;
      paramsb[1] = eta1_mmb4;
      paramsb[2] = phi1_mmb4;
      paramsb[3] = vx1_mmb4;
      paramsb[4] = vy1_mmb4;
      paramsb[5] = pt2_mmb4;
      paramsb[6] = eta2_mmb4;
      paramsb[7] = phi2_mmb4;
      paramsb[8] = vx2_mmb4;
      paramsb[9] = vy2_mmb4;
      paramsb[10] = Nj_mmb4;
      paramsb[11] = Nak8j_mmb4;
      paramsb[12] = missET_mmb4;
      MLPmmb->Fill(mlp->Evaluate(0, paramsb));
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

      paramsemb[0] = pt1_emb;
      paramsemb[1] = eta1_emb;
      paramsemb[2] = phi1_emb;
      paramsemb[3] = vx1_emb;
      paramsemb[4] = vy1_emb;
      paramsemb[5] = pt2_emb;
      paramsemb[6] = eta2_emb;
      paramsemb[7] = phi2_emb;
      paramsemb[8] = vx2_emb;
      paramsemb[9] = vy2_emb;
      paramsemb[10] = Nj_emb;
      paramsemb[11] = Nak8j_emb;
      paramsemb[12] = missET_emb;
      MLPemb->Fill(mlp->Evaluate(0, paramsemb));
   }

   for(i = 0; i < emb2_Branch->GetEntries(); i++) {
      emb2_Branch->GetEntry(i);

      paramsb[0] = pt1_emb2;
      paramsb[1] = eta1_emb2;
      paramsb[2] = phi1_emb2;
      paramsb[3] = vx1_emb2;
      paramsb[4] = vy1_emb2;
      paramsb[5] = pt2_emb2;
      paramsb[6] = eta2_emb2;
      paramsb[7] = phi2_emb2;
      paramsb[8] = vx2_emb2;
      paramsb[9] = vy2_emb2;
      paramsb[10] = Nj_emb2;
      paramsb[11] = Nak8j_emb2;
      paramsb[12] = missET_emb2;
      MLPemb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < emb3_Branch->GetEntries(); i++) {
      emb3_Branch->GetEntry(i);

      paramsb[0] = pt1_emb3;
      paramsb[1] = eta1_emb3;
      paramsb[2] = phi1_emb3;
      paramsb[3] = vx1_emb3;
      paramsb[4] = vy1_emb3;
      paramsb[5] = pt2_emb3;
      paramsb[6] = eta2_emb3;
      paramsb[7] = phi2_emb3;
      paramsb[8] = vx2_emb3;
      paramsb[9] = vy2_emb3;
      paramsb[10] = Nj_emb3;
      paramsb[11] = Nak8j_emb3;
      paramsb[12] = missET_emb3;
      MLPemb->Fill(mlp->Evaluate(0, paramsb));
   } 

   for(i = 0; i < emb4_Branch->GetEntries(); i++) {
      emb4_Branch->GetEntry(i);

      paramsb[0] = pt1_emb4;
      paramsb[1] = eta1_emb4;
      paramsb[2] = phi1_emb4;
      paramsb[3] = vx1_emb4;
      paramsb[4] = vy1_emb4;
      paramsb[5] = pt2_emb4;
      paramsb[6] = eta2_emb4;
      paramsb[7] = phi2_emb4;
      paramsb[8] = vx2_emb4;
      paramsb[9] = vy2_emb4;
      paramsb[10] = Nj_emb4;
      paramsb[11] = Nak8j_emb4;
      paramsb[12] = missET_emb4;
      MLPemb->Fill(mlp->Evaluate(0, paramsb));
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

