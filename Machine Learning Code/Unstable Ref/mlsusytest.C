//--original
//--all inputs, with diagrams, ee mm em branches, unify variables, all data sets, normalize


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

// void branchSet(TTree* branch, TTree* bbranch, Float_t pt1, Float_t eta1, Float_t phi1, Float_t vx1, Float_t vy1, Float_t pt2, Float_t eta2, Float_t phi2, Float_t vx2, Float_t vy2, Float_t Nj, Float_t Nak8j, Float_t missET) {
//    branch->SetBranchAddress("pt1",  &pt1);
//    branch->SetBranchAddress("eta1", &eta1);
//    branch->SetBranchAddress("phi1", &phi1);
//    branch->SetBranchAddress("vx1",  &vx1);
//    branch->SetBranchAddress("vy1",  &vy1);
//    branch->SetBranchAddress("pt2",  &pt2);
//    branch->SetBranchAddress("eta2", &eta2);
//    branch->SetBranchAddress("phi2", &phi2);
//    branch->SetBranchAddress("vx2",  &vx2);
//    branch->SetBranchAddress("vy2",  &vy2);
//    branch->SetBranchAddress("Nj",   &Nj);
//    branch->SetBranchAddress("Nak8j",&Nak8j);
//    branch->SetBranchAddress("missET",&missET);

//    bbranch->SetBranchAddress("pt1",  &pt1);
//    bbranch->SetBranchAddress("eta1", &eta1);
//    bbranch->SetBranchAddress("phi1", &phi1);
//    bbranch->SetBranchAddress("vx1",  &vx1);
//    bbranch->SetBranchAddress("vy1",  &vy1);
//    bbranch->SetBranchAddress("pt2",  &pt2);
//    bbranch->SetBranchAddress("eta2", &eta2);
//    bbranch->SetBranchAddress("phi2", &phi2);
//    bbranch->SetBranchAddress("vx2",  &vx2);
//    bbranch->SetBranchAddress("vy2",  &vy2);
//    bbranch->SetBranchAddress("Nj",   &Nj);
//    bbranch->SetBranchAddress("Nak8j",&Nak8j);
//    bbranch->SetBranchAddress("missET",&missET);
// }
void mlsusytest(Int_t ntrain = 100) {
   const char* fname = "outputNtuple_tt.root";
   const char* fname2 = "outputNtuple_DY.root";
   const char* fname3 = "outputNtuple_ww.root";
   const char* fname4 = "outputNtuple_wz.root";
   const char* fname5 = "outputNtuple_zz.root";

   TFile* input = 0;
   TFile* input2 = 0;
   TFile* input3 = 0;
   TFile* input4 = 0;
   TFile* input5 = 0;

   if(!gSystem->AccessPathName(fname) && !gSystem->AccessPathName(fname2) && !gSystem->AccessPathName(fname3) && !gSystem->AccessPathName(fname4) && !gSystem->AccessPathName(fname5)) {
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
   
   TTree* mm_Branch = (TTree*) input->Get("mm_Branch");
   TTree* mmb_Branch = (TTree*) input2->Get("mm_Branch");

   TTree* em_Branch = (TTree*) input->Get("em_Branch");
   TTree* emb_Branch = (TTree*) input2->Get("em_Branch");

   TFile* ofile = new TFile("output_ML","RECREATE");
   TTree *simu = new TTree("MonteCarlo", "Filtered Monte Carlo Events");

  // Float_t pt1, Float_t eta1, Float_t phi1, Float_t vx1, Float_t vy1, Float_t pt2, Float_t eta2, Float_t phi2, Float_t vx2, Float_t vy2, Float_t Nj, Float_t Nak8j, Float_t missET;
  // pt1, eta1, phi1, vx1, vy1, pt2, eta2, phi2, vx2, vy2, Nj, Nak8j, missET;

   Float_t pt1_ee, eta1_ee, phi1_ee, vx1_ee, vy1_ee;
   Float_t pt2_ee, eta2_ee, phi2_ee, vx2_ee, vy2_ee;
   Float_t Nj_ee, Nak8j_ee, missET_ee;

   Float_t pt1_em, eta1_em, phi1_em, vx1_em, vy1_em;
   Float_t pt2_em, eta2_em, phi2_em, vx2_em, vy2_em;
   Float_t Nj_em, Nak8j_em, missET_em;

   Float_t pt1_mm, eta1_mm, phi1_mm, vx1_mm, vy1_mm;
   Float_t pt2_mm, eta2_mm, phi2_mm, vx2_mm, vy2_mm;
   Float_t Nj_mm, Nak8j_mm, missET_mm;

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
   //branchSet(ee_Branch, eeb_Branch, pt1_ee, eta1_ee, phi1_ee, vx1_ee, vy1_ee, pt2_ee, eta2_ee, phi2_ee, vx2_ee, vy2_ee, Nj_ee, Nak8j_ee, missET_ee);
   
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


   // ee_Branch->SetBranchAddress("pt1",  pt1_ee);
   // ee_Branch->SetBranchAddress("eta1", eta1_ee);
   // ee_Branch->SetBranchAddress("phi1", phi1_ee);
   // ee_Branch->SetBranchAddress("vx1",  vx1_ee);
   // ee_Branch->SetBranchAddress("vy1",  vy1_ee);
   // ee_Branch->SetBranchAddress("pt2",  pt2_ee);
   // ee_Branch->SetBranchAddress("eta2", eta2_ee);
   // ee_Branch->SetBranchAddress("phi2", phi2_ee);
   // ee_Branch->SetBranchAddress("vx2",  vx2_ee);
   // ee_Branch->SetBranchAddress("vy2",  vy2_ee);
   // ee_Branch->SetBranchAddress("Nj",   Nj_ee);
   // ee_Branch->SetBranchAddress("Nak8j",Nak8j_ee);
   // ee_Branch->SetBranchAddress("missET",missET_ee);

   // eeb_Branch->SetBranchAddress("pt1",  pt1_ee);
   // eeb_Branch->SetBranchAddress("eta1", eta1_ee);
   // eeb_Branch->SetBranchAddress("phi1", phi1_ee);
   // eeb_Branch->SetBranchAddress("vx1",  vx1_ee);
   // eeb_Branch->SetBranchAddress("vy1",  vy1_ee);
   // eeb_Branch->SetBranchAddress("pt2",  pt2_ee);
   // eeb_Branch->SetBranchAddress("eta2", eta2_ee);
   // eeb_Branch->SetBranchAddress("phi2", phi2_ee);
   // eeb_Branch->SetBranchAddress("vx2",  vx2_ee);
   // eeb_Branch->SetBranchAddress("vy2",  vy2_ee);
   // eeb_Branch->SetBranchAddress("Nj",   Nj_ee);
   // eeb_Branch->SetBranchAddress("Nak8j",Nak8j_ee);
   // eeb_Branch->SetBranchAddress("missET",missET_ee);
   // //branchSet(ee_Branch, eeb_Branch, pt1_ee, eta1_ee, phi1_ee, vx1_ee, vy1_ee, pt2_ee, eta2_ee, phi2_ee, vx2_ee, vy2_ee, Nj_ee, Nak8j_ee, missET_ee);
   
   // mm_Branch->SetBranchAddress("pt1",  pt1_mm);
   // mm_Branch->SetBranchAddress("eta1", eta1_mm);
   // mm_Branch->SetBranchAddress("phi1", phi1_mm);
   // mm_Branch->SetBranchAddress("vx1",  vx1_mm);
   // mm_Branch->SetBranchAddress("vy1",  vy1_mm);
   // mm_Branch->SetBranchAddress("pt2",  pt2_mm);
   // mm_Branch->SetBranchAddress("eta2", eta2_mm);
   // mm_Branch->SetBranchAddress("phi2", phi2_mm);
   // mm_Branch->SetBranchAddress("vx2",  vx2_mm);
   // mm_Branch->SetBranchAddress("vy2",  vy2_mm);
   // mm_Branch->SetBranchAddress("Nj",   Nj_mm);
   // mm_Branch->SetBranchAddress("Nak8j",Nak8j_mm);
   // mm_Branch->SetBranchAddress("missET",missET_mm);

   // mmb_Branch->SetBranchAddress("pt1",  pt1_mm);
   // mmb_Branch->SetBranchAddress("eta1", eta1_mm);
   // mmb_Branch->SetBranchAddress("phi1", phi1_mm);
   // mmb_Branch->SetBranchAddress("vx1",  vx1_mm);
   // mmb_Branch->SetBranchAddress("vy1",  vy1_mm);
   // mmb_Branch->SetBranchAddress("pt2",  pt2_mm);
   // mmb_Branch->SetBranchAddress("eta2", eta2_mm);
   // mmb_Branch->SetBranchAddress("phi2", phi2_mm);
   // mmb_Branch->SetBranchAddress("vx2",  vx2_mm);
   // mmb_Branch->SetBranchAddress("vy2",  vy2_mm);
   // mmb_Branch->SetBranchAddress("Nj",   Nj_mm);
   // mmb_Branch->SetBranchAddress("Nak8j",Nak8j_mm);
   // mmb_Branch->SetBranchAddress("missET",missET_mm);

   // em_Branch->SetBranchAddress("pt1",  pt1_em);
   // em_Branch->SetBranchAddress("eta1", eta1_em);
   // em_Branch->SetBranchAddress("phi1", phi1_em);
   // em_Branch->SetBranchAddress("vx1",  vx1_em);
   // em_Branch->SetBranchAddress("vy1",  vy1_em);
   // em_Branch->SetBranchAddress("pt2",  pt2_em);
   // em_Branch->SetBranchAddress("eta2", eta2_em);
   // em_Branch->SetBranchAddress("phi2", phi2_em);
   // em_Branch->SetBranchAddress("vx2",  vx2_em);
   // em_Branch->SetBranchAddress("vy2",  vy2_em);
   // em_Branch->SetBranchAddress("Nj",   Nj_em);
   // em_Branch->SetBranchAddress("Nak8j",Nak8j_em);
   // em_Branch->SetBranchAddress("missET",missET_em);

   // emb_Branch->SetBranchAddress("pt1",  pt1_em);
   // emb_Branch->SetBranchAddress("eta1", eta1_em);
   // emb_Branch->SetBranchAddress("phi1", phi1_em);
   // emb_Branch->SetBranchAddress("vx1",  vx1_em);
   // emb_Branch->SetBranchAddress("vy1",  vy1_em);
   // emb_Branch->SetBranchAddress("pt2",  pt2_em);
   // emb_Branch->SetBranchAddress("eta2", eta2_em);
   // emb_Branch->SetBranchAddress("phi2", phi2_em);
   // emb_Branch->SetBranchAddress("vx2",  vx2_em);
   // emb_Branch->SetBranchAddress("vy2",  vy2_em);
   // emb_Branch->SetBranchAddress("Nj",   Nj_em);
   // emb_Branch->SetBranchAddress("Nak8j",Nak8j_em);
   // emb_Branch->SetBranchAddress("missET",missET_em);
 
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

   //ee_Branch->Print();

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

   type = 1;
   for(i = 0; i < em_Branch->GetEntries(); i++) {
      em_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < em_Branch->GetEntries(); i++) {
      emb_Branch->GetEntry(i);
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

//--em
   TH1F *hpt1_em  = new TH1F("hpt1_em","pt1 distribution", 100, 0., 1200.);
   TH1F *heta1_em  = new TH1F("heta1_em","eta1 distribution",100,-3,3);
   TH1F *hphi1_em  = new TH1F("hphi1_em","phi1 distribution",100,-5,5);
   TH1F *hvx1_em  = new TH1F("hvx1_em","vx1 distribution",100,-0.5,0.5);
   TH1F *hvy1_em  = new TH1F("hvy1_em","vy1 distribution",100,-0.5,0.5);

   TH1F *hpt2_em  = new TH1F("hpt2_em","pt2 distribution", 100, 0., 1200.);
   TH1F *heta2_em  = new TH1F("heta2_em","eta2 distribution",100,-3,3);
   TH1F *hphi2_em  = new TH1F("hphi2_em","phi2 distribution",100,-5,5);
   TH1F *hvx2_em  = new TH1F("hvx2_em","vx2 distribution",100,-0.5,0.5);
   TH1F *hvy2_em  = new TH1F("hvy2_em","vy2 distribution",100,-0.5,0.5);
   
   TH1F *hNj_em = new TH1F("hNj_em", "Nj distribution", 11, 0., 11.);
   TH1F *hNak8j_em = new TH1F("hNak8j_em", "Nak8j distribution", 11, 0., 11.);
   TH1F *hmissET_em  = new TH1F("hmissET_em","missET distribution",100, 0., 8000.); 
//-
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
            hpt1_ee->Fill(pt1_ee);
         }
         filler(hpt1_ee, "GeV");
      }

      if(i == 2) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            heta1_ee->Fill(eta1_ee);
         }
         filler(heta1_ee, "eta");
      }

      if(i == 3) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hphi1_ee->Fill(phi1_ee);
         }
         filler(hphi1_ee, "rad");
      }

      if(i == 4) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvx1_ee->Fill(vx1_ee);
         }
         filler(hvx1_ee, "pos");
      }

      if(i == 5) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvy1_ee->Fill(vy1_ee);
         }
         filler(hvy1_ee, "pos");
      }


      if(i == 6) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hpt2_ee->Fill(pt2_ee);
         }
         filler(hpt2_ee, "GV");
      }

      if(i == 7) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            heta2_ee->Fill(eta2_ee);
         }
         filler(heta2_ee, "eta");
      }

      if(i == 8) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hphi2_ee->Fill(phi2_ee);
         }
         filler(hphi2_ee, "rad");
      }

      if(i == 9) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvx2_ee->Fill(vx2_ee);
         }
         filler(hvx2_ee, "pos");
      }

      if(i == 10) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hvy2_ee->Fill(vy2_ee);
         }
         filler(hvy2_ee, "pos");
      }

      if(i == 11) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hNj_ee->Fill(Nj_ee);
         }
         filler(hNj_ee, "number");
      }

      if(i == 12) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hNak8j_ee->Fill(Nak8j_ee);
         }
         filler(hNak8j_ee, "number");
      }

      if(i == 13) {
         for(j = 0; j < eeb_entries; j++) {
            eeb_Branch->GetEntry(j);
            hmissET_ee->Fill(missET_ee);
         }
         filler(hmissET_ee, "GV");
      }
   }

   //em
   TCanvas *em_canvas = new TCanvas("em_canvas", "em Data", 900, 700);
   em_canvas->Divide(7,2,0,0);
   Int_t em_entries = (Int_t) em_Branch->GetEntries();

   for(Int_t i = 1; i <= 13; i++) {
      em_canvas->cd(i);
      Int_t j;
      if(i == 1) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hpt1_em->Fill(pt1_em);
         }
         filler(hpt1_em, "GeV");
      }

      if(i == 2) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            heta1_em->Fill(eta1_em);
         }
         filler(heta1_em, "eta");
      }

      if(i == 3) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hphi1_em->Fill(phi1_em);
         }
         filler(hphi1_em, "rad");
      }

      if(i == 4) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hvx1_em->Fill(vx1_em);
         }
         filler(hvx1_em, "pos");
      }

      if(i == 5) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hvy1_em->Fill(vy1_em);
         }
         filler(hvy1_em, "pos");
      }


      if(i == 6) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hpt2_em->Fill(pt2_em);
         }
         filler(hpt2_em, "GV");
      }

      if(i == 7) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            heta2_em->Fill(eta2_em);
         }
         filler(heta2_em, "eta");
      }

      if(i == 8) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hphi2_em->Fill(phi2_em);
         }
         filler(hphi2_em, "rad");
      }

      if(i == 9) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hvx2_em->Fill(vx2_em);
         }
         filler(hvx2_em, "pos");
      }

      if(i == 10) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hvy2_em->Fill(vy2_em);
         }
         filler(hvy2_em, "pos");
      }

      if(i == 11) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hNj_em->Fill(Nj_em);
         }
         filler(hNj_em, "number");
      }

      if(i == 12) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hNak8j_em->Fill(Nak8j_em);
         }
         filler(hNak8j_em, "number");
      }

      if(i == 13) {
         for(j = 0; j < em_Branch->GetEntries(); j++) {
            em_Branch->GetEntry(j);
            hmissET_em->Fill(missET_em);
         }
         filler(hmissET_em, "GV");
      }
   }

   //emb
   TCanvas *emb_canvas = new TCanvas("emb_canvas", "em Background Data", 900, 700);
   emb_canvas->Divide(7,2,0,0);
   Int_t emb_entries = (Int_t) emb_Branch->GetEntries();

   for(Int_t i = 1; i <= 13; i++) {
      emb_canvas->cd(i);
      Int_t j;
      if(i == 1) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hpt1_em->Fill(pt1_em);
         }
         filler(hpt1_em, "GeV");
      }

      if(i == 2) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            heta1_em->Fill(eta1_em);
         }
         filler(heta1_em, "eta");
      }

      if(i == 3) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hphi1_em->Fill(phi1_em);
         }
         filler(hphi1_em, "rad");
      }

      if(i == 4) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hvx1_em->Fill(vx1_em);
         }
         filler(hvx1_em, "pos");
      }

      if(i == 5) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hvy1_em->Fill(vy1_em);
         }
         filler(hvy1_em, "pos");
      }


      if(i == 6) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hpt2_em->Fill(pt2_em);
         }
         filler(hpt2_em, "GV");
      }

      if(i == 7) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            heta2_em->Fill(eta2_em);
         }
         filler(heta2_em, "eta");
      }

      if(i == 8) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hphi2_em->Fill(phi2_em);
         }
         filler(hphi2_em, "rad");
      }

      if(i == 9) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hvx2_em->Fill(vx2_em);
         }
         filler(hvx2_em, "pos");
      }

      if(i == 10) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hvy2_em->Fill(vy2_em);
         }
         filler(hvy2_em, "pos");
      }

      if(i == 11) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hNj_em->Fill(Nj_em);
         }
         filler(hNj_em, "number");
      }

      if(i == 12) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hNak8j_em->Fill(Nak8j_em);
         }
         filler(hNak8j_em, "number");
      }

      if(i == 13) {
         for(j = 0; j < emb_Branch->GetEntries(); j++) {
            emb_Branch->GetEntry(j);
            hmissET_em->Fill(missET_em);
         }
         filler(hmissET_em, "GV");
      }
   }   

   //mm
   TCanvas *mm_canvas = new TCanvas("mm_canvas", "mm Data", 900, 700);
   mm_canvas->Divide(7,2,0,0);
   Int_t mm_entries = (Int_t) mm_Branch->GetEntries();

   for(Int_t i = 1; i <= 13; i++) {
      mm_canvas->cd(i);
      Int_t j;
      if(i == 1) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hpt1_mm->Fill(pt1_mm);
         }
         filler(hpt1_mm, "GeV");
      }

      if(i == 2) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            heta1_mm->Fill(eta1_mm);
         }
         filler(heta1_mm, "eta");
      }

      if(i == 3) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hphi1_mm->Fill(phi1_mm);
         }
         filler(hphi1_mm, "rad");
      }

      if(i == 4) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hvx1_mm->Fill(vx1_mm);
         }
         filler(hvx1_mm, "pos");
      }

      if(i == 5) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hvy1_mm->Fill(vy1_mm);
         }
         filler(hvy1_mm, "pos");
      }


      if(i == 6) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hpt2_mm->Fill(pt2_mm);
         }
         filler(hpt2_mm, "GV");
      }

      if(i == 7) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            heta2_mm->Fill(eta2_mm);
         }
         filler(heta2_mm, "eta");
      }

      if(i == 8) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hphi2_mm->Fill(phi2_mm);
         }
         filler(hphi2_mm, "rad");
      }

      if(i == 9) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hvx2_mm->Fill(vx2_mm);
         }
         filler(hvx2_mm, "pos");
      }

      if(i == 10) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hvy2_mm->Fill(vy2_mm);
         }
         filler(hvy2_mm, "pos");
      }

      if(i == 11) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hNj_mm->Fill(Nj_mm);
         }
         filler(hNj_mm, "number");
      }

      if(i == 12) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hNak8j_mm->Fill(Nak8j_mm);
         }
         filler(hNak8j_mm, "number");
      }

      if(i == 13) {
         for(j = 0; j < mm_entries; j++) {
            mm_Branch->GetEntry(j);
            hmissET_mm->Fill(missET_mm);
         }
         filler(hmissET_mm, "GV");
      }
   }

   //mmb
   TCanvas *mmb_canvas = new TCanvas("mmb_canvas", "mm Background Data", 900, 700);
   mmb_canvas->Divide(7,2,0,0);
   Int_t mmb_entries = (Int_t) mmb_Branch->GetEntries();

   for(Int_t i = 1; i <= 13; i++) {
      mmb_canvas->cd(i);
      Int_t j;
      if(i == 1) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hpt1_mm->Fill(pt1_mm);
         }
         filler(hpt1_mm, "GeV");
      }

      if(i == 2) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            heta1_mm->Fill(eta1_mm);
         }
         filler(heta1_mm, "eta");
      }

      if(i == 3) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hphi1_mm->Fill(phi1_mm);
         }
         filler(hphi1_mm, "rad");
      }

      if(i == 4) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hvx1_mm->Fill(vx1_mm);
         }
         filler(hvx1_mm, "pos");
      }

      if(i == 5) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hvy1_mm->Fill(vy1_mm);
         }
         filler(hvy1_mm, "pos");
      }


      if(i == 6) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hpt2_mm->Fill(pt2_mm);
         }
         filler(hpt2_mm, "GV");
      }

      if(i == 7) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            heta2_mm->Fill(eta2_mm);
         }
         filler(heta2_mm, "eta");
      }

      if(i == 8) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hphi2_mm->Fill(phi2_mm);
         }
         filler(hphi2_mm, "rad");
      }

      if(i == 9) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hvx2_mm->Fill(vx2_mm);
         }
         filler(hvx2_mm, "pos");
      }

      if(i == 10) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hvy2_mm->Fill(vy2_mm);
         }
         filler(hvy2_mm, "pos");
      }

      if(i == 11) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hNj_mm->Fill(Nj_mm);
         }
         filler(hNj_mm, "number");
      }

      if(i == 12) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hNak8j_mm->Fill(Nak8j_mm);
         }
         filler(hNak8j_mm, "number");
      }

      if(i == 13) {
         for(j = 0; j < mmb_entries; j++) {
            mmb_Branch->GetEntry(j);
            hmissET_mm->Fill(missET_mm);
         }
         filler(hmissET_mm, "GV");
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
   TH1F* MLPeeb = new TH1F("MLPeebh", "NN output", 50, -.5, 1.5);
   TH1F* MLPmm = new TH1F("MLPmmh", "NN output", 50, -.5, 1.5);
   TH1F* MLPmmb = new TH1F("MLPmmbh", "NN output", 50, -.5, 1.5);
   TH1F* MLPem = new TH1F("MLPemh", "NN output", 50, -.5, 1.5);
   TH1F* MLPemb = new TH1F("MLPembh", "NN output", 50, -.5, 1.5);

   MLPee->SetDirectory(0);
   MLPmm->SetDirectory(0);
   MLPem->SetDirectory(0);
   MLPeeb->SetDirectory(0);
   MLPmmb->SetDirectory(0);
   MLPemb->SetDirectory(0);
   

//--feeding to NN
   //--ee
   Double_t params[14];
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

   //--mm
   for(i = 0; i < mm_Branch->GetEntries(); i++) {
      mm_Branch->GetEntry(i);

      params[0] = pt1_mm;
      params[1] = eta1_mm;
      params[2] = phi1_mm;
      params[3] = vx1_mm;
      params[4] = vy1_mm;
      params[5] = pt2_mm;
      params[6] = eta2_mm;
      params[7] = phi2_mm;
      params[8] = vx2_mm;
      params[9] = vy2_mm;
      params[10] = Nj_mm;
      params[11] = Nak8j_mm;
      params[12] = missET_mm;
      MLPmm->Fill(mlp->Evaluate(0, params));
   }   

   //--em
   for(i = 0; i < em_Branch->GetEntries(); i++) {
      em_Branch->GetEntry(i);

      params[0] = pt1_em;
      params[1] = eta1_em;
      params[2] = phi1_em;
      params[3] = vx1_em;
      params[4] = vy1_em;
      params[5] = pt2_em;
      params[6] = eta2_em;
      params[7] = phi2_em;
      params[8] = vx2_em;
      params[9] = vy2_em;
      params[10] = Nj_em;
      params[11] = Nak8j_em;
      params[12] = missET_em;
      MLPem->Fill(mlp->Evaluate(0, params));
   }

   //--eeb
   for(i = 0; i < eeb_Branch->GetEntries(); i++) {
      eeb_Branch->GetEntry(i);

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
      MLPeeb->Fill(mlp->Evaluate(0, params));
   }

   //--mmb
   for(i = 0; i < mmb_Branch->GetEntries(); i++) {
      mmb_Branch->GetEntry(i);

      params[0] = pt1_mm;
      params[1] = eta1_mm;
      params[2] = phi1_mm;
      params[3] = vx1_mm;
      params[4] = vy1_mm;
      params[5] = pt2_mm;
      params[6] = eta2_mm;
      params[7] = phi2_mm;
      params[8] = vx2_mm;
      params[9] = vy2_mm;
      params[10] = Nj_mm;
      params[11] = Nak8j_mm;
      params[12] = missET_mm;
      MLPmmb->Fill(mlp->Evaluate(0, params));
   }   

   //--emb
   for(i = 0; i < emb_Branch->GetEntries(); i++) {
      emb_Branch->GetEntry(i);

      params[0] = pt1_em;
      params[1] = eta1_em;
      params[2] = phi1_em;
      params[3] = vx1_em;
      params[4] = vy1_em;
      params[5] = pt2_em;
      params[6] = eta2_em;
      params[7] = phi2_em;
      params[8] = vx2_em;
      params[9] = vy2_em;
      params[10] = Nj_em;
      params[11] = Nak8j_em;
      params[12] = missET_em;
      MLPemb->Fill(mlp->Evaluate(0, params));
   }
//   

   signalStyling(MLPee);
   backgroundStyling(MLPeeb);
   signalStyling(MLPmm);
   backgroundStyling(MLPmmb);
   signalStyling(MLPem);
   backgroundStyling(MLPemb);

   MLPee->SetStats(0);
   MLPmm->SetStats(0);
   MLPem->SetStats(0);
   MLPeeb->SetStats(0);
   MLPmmb->SetStats(0);
   MLPemb->SetStats(0);

   // MLPee->Draw();
   // MLPmm->Draw("same");
   // MLPem->Draw("same");
   // MLPeeb->Draw("same");
   // MLPmmb->Draw("same");
   // MLPemb->Draw("same");

   MLPee-> Scale(10/MLPee->GetEntries());
   MLPeeb-> Scale(10/MLPeeb->GetEntries());
   MLPmm-> Scale(10/MLPmm->GetEntries());
   MLPmmb-> Scale(10/MLPmmb->GetEntries());
   MLPem-> Scale(10/MLPem->GetEntries());
   MLPemb-> Scale(10/MLPemb->GetEntries());

   MLPeeb->Draw("hist");
   MLPee->Draw("hist same");
   MLPmmb->Draw("hist same");
   MLPmmb->Draw("hist same");
   MLPem->Draw("hist same");
   MLPemb->Draw("hist same");

   TLegend *legend = new TLegend(.75, .80, .95, .95);
   legend->AddEntry(MLPee, "ee");
   legend->AddEntry(MLPmm, "mm");
   legend->AddEntry(MLPem, "em");
   legend->AddEntry(MLPeeb, "eeb");
   legend->AddEntry(MLPmmb, "mmb");
   legend->AddEntry(MLPemb, "emb");

   legend->Draw();
   mlpa_canvas->cd(0);

   //ofile->Write();
   //ofile->Close();

   delete input;
}

