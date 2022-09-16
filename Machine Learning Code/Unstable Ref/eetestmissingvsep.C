//--best testing yet
//--not all input(missing vx,vy,nj), wo diagrams, ee branches, seperate variables, 2 data sets, normalize


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

void eetestmissingvsep(Int_t ntrain = 100) {
   const char* fname = "outputNtuple_wz.root";
   const char* fname2 = "outputNtuple_tt.root";
   const char* fname3 = "outputNtuple_DY.root";
   const char* fname4 = "outputNtuple_ww.root";
   const char* fname5 = "outputNtuple_wz.root";

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
   

   TFile* ofile = new TFile("output_ML","RECREATE");
   TTree *simu = new TTree("MonteCarlo", "Filtered Monte Carlo Events");


   Float_t pt1, eta1, phi1;
   Float_t pt2, eta2, phi2;
   Float_t Nak8j, missET;


   Float_t pt1_ee, eta1_ee, phi1_ee;
   Float_t pt2_ee, eta2_ee, phi2_ee;
   Float_t Nak8j_ee, missET_ee;

   Float_t Nmu, type;

//-- set branches
   ee_Branch->SetBranchAddress("pt1",  &pt1);
   ee_Branch->SetBranchAddress("eta1", &eta1);
   ee_Branch->SetBranchAddress("phi1", &phi1);
   ee_Branch->SetBranchAddress("pt2",  &pt2);
   ee_Branch->SetBranchAddress("eta2", &eta2);
   ee_Branch->SetBranchAddress("phi2", &phi2);
   ee_Branch->SetBranchAddress("Nak8j",&Nak8j);
   ee_Branch->SetBranchAddress("missET",&missET);

   eeb_Branch->SetBranchAddress("pt1",  &pt1_ee);
   eeb_Branch->SetBranchAddress("eta1", &eta1_ee);
   eeb_Branch->SetBranchAddress("phi1", &phi1_ee);
   eeb_Branch->SetBranchAddress("pt2",  &pt2_ee);
   eeb_Branch->SetBranchAddress("eta2", &eta2_ee);
   eeb_Branch->SetBranchAddress("phi2", &phi2_ee);
   eeb_Branch->SetBranchAddress("Nak8j",&Nak8j_ee);
   eeb_Branch->SetBranchAddress("missET",&missET_ee);
//  

//-- simu branch
   simu->Branch("pt1",   &pt1,   "pt1/F");
   simu->Branch("eta1",  &eta1,  "eta1/F");
   simu->Branch("phi1",  &phi1,  "phi1/F");
   simu->Branch("pt2",   &pt2,   "pt2/F");
   simu->Branch("eta2",  &eta2,  "eta2/F");
   simu->Branch("phi2",  &phi2,  "phi2/F");
   simu->Branch("Nak8j", &Nak8j, "Nak8j/F");
   simu->Branch("missET",&missET,"missET/F");

   simu->Branch("pt1",   &pt1_ee,   "pt1/F");
   simu->Branch("eta1",  &eta1_ee,  "eta1/F");
   simu->Branch("phi1",  &phi1_ee,  "phi1/F");
   simu->Branch("pt2",   &pt2_ee,   "pt2/F");
   simu->Branch("eta2",  &eta2_ee,  "eta2/F");
   simu->Branch("phi2",  &phi2_ee,  "phi2/F");
   simu->Branch("Nak8j", &Nak8j_ee, "Nak8j/F");
   simu->Branch("missET",&missET_ee,"missET/F");
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
   

   //-- train NN
   //TMultiLayerPerceptron* mlp = new TMultiLayerPerceptron("pt1,eta1,phi1,vx1:6::type",simu);
   TMultiLayerPerceptron *mlp = new TMultiLayerPerceptron("@pt1,@eta1,@phi1,@pt2,@eta2,@phi2,@Nak8j,@missET:8:6:@type",simu,"Entry$%2","(Entry$+1)%2");   
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

   MLPee->SetDirectory(0);
   MLPeeb->SetDirectory(0);


//--feeding to NN
   //--ee
   Double_t params[8];

   for(i = 0; i < ee_Branch->GetEntries(); i++) {
      ee_Branch->GetEntry(i);

      params[0] = pt1;
      params[1] = eta1;
      params[2] = phi1;
      params[3] = pt2;
      params[4] = eta2;
      params[5] = phi2;
      params[6] = Nak8j;
      params[7] = missET;

      MLPee->Fill(mlp->Evaluate(0, params));
   }

   //--eeb
   for(i = 0; i < eeb_Branch->GetEntries(); i++) {
      eeb_Branch->GetEntry(i);

      params[0] = pt1_ee;
      params[1] = eta1_ee;
      params[2] = phi1_ee;
      params[3] = pt2_ee;
      params[4] = eta2_ee;
      params[5] = phi2_ee;
      params[6] = Nak8j_ee;
      params[7] = missET_ee;
      MLPeeb->Fill(mlp->Evaluate(0, params));
   }

   signalStyling(MLPee);
   backgroundStyling(MLPeeb);

   MLPee->SetStats(0);
   MLPeeb->SetStats(0);

   MLPee-> Scale(10/MLPee->Integral());
   MLPeeb-> Scale(10/MLPeeb->Integral());

   MLPeeb->Draw("hist");
   MLPee->Draw("hist same");


   TLegend *legend = new TLegend(.75, .80, .95, .95);
   legend->AddEntry(MLPee, "ee");
   legend->AddEntry(MLPeeb, "eeb");

   legend->Draw();
   mlpa_canvas->cd(0);

   //ofile->Write();
   //ofile->Close();

   delete input;
}

