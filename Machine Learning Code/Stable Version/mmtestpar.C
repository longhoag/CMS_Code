//--best testing yet
//--not all input(missing vx,vy,nj), wo diagrams, ee branches, unify variables, 2 data sets, normalize


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

void mmtestpar(Int_t ntrain = 100) {
   const char* fname = "outputNtuple_tt.root";
   const char* fname2 = "outputNtuple_ww.root";

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
   TTree* mm_Branch = (TTree*) input->Get("mm_Branch");
   TTree* mmb_Branch = (TTree*) input2->Get("mm_Branch");

   TFile* ofile = new TFile("output_ML","RECREATE");
   TTree *simu = new TTree("MonteCarlo", "Filtered Monte Carlo Events");

   Float_t pt1_mm, eta1_mm, phi1_mm;
   Float_t pt2_mm, eta2_mm, phi2_mm;
   Float_t Nak8j_mm, missET_mm;


   // Float_t pt1, eta1, phi1b;
   // Float_t pt2b, eta2b, phi2b;
   // Float_t Nak8jb, missETb;

   // Float_t pt1b, eta1b, phi1b;
   // Float_t pt2b, eta2b, phi2b;
   // Float_t Nak8jb, missETb;

   Int_t type;

//-- set branches
   mm_Branch->SetBranchAddress("pt1",  &pt1_mm);
   mm_Branch->SetBranchAddress("eta1", &eta1_mm);
   mm_Branch->SetBranchAddress("phi1", &phi1_mm);
   mm_Branch->SetBranchAddress("pt2",  &pt2_mm);
   mm_Branch->SetBranchAddress("eta2", &eta2_mm);
   mm_Branch->SetBranchAddress("phi2", &phi2_mm);
   mm_Branch->SetBranchAddress("Nak8j",&Nak8j_mm);
   mm_Branch->SetBranchAddress("missET",&missET_mm);

   mmb_Branch->SetBranchAddress("pt1",  &pt1_mm);
   mmb_Branch->SetBranchAddress("eta1", &eta1_mm);
   mmb_Branch->SetBranchAddress("phi1", &phi1_mm);
   mmb_Branch->SetBranchAddress("pt2",  &pt2_mm);
   mmb_Branch->SetBranchAddress("eta2", &eta2_mm);
   mmb_Branch->SetBranchAddress("phi2", &phi2_mm);
   mmb_Branch->SetBranchAddress("Nak8j",&Nak8j_mm);
   mmb_Branch->SetBranchAddress("missET",&missET_mm);
//  

//-- simu branch
   simu->Branch("pt1",   &pt1_mm,   "pt1/F");
   simu->Branch("eta1",  &eta1_mm,  "eta1/F");
   simu->Branch("phi1",  &phi1_mm,  "phi1/F");
   simu->Branch("pt2",   &pt2_mm,   "pt2/F");
   simu->Branch("eta2",  &eta2_mm,  "eta2/F");
   simu->Branch("phi2",  &phi2_mm,  "phi2/F");
   simu->Branch("Nak8j", &Nak8j_mm, "Nak8j/F");
   simu->Branch("missET",&missET_mm,"missET/F");

   simu->Branch("type",   &type,   "type/I");


//--type signal and background: 1-signal, 0-background
   Int_t i;
   type = 1;
   for(i = 0; i < mm_Branch->GetEntries(); i++) {
      mm_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < mmb_Branch->GetEntries(); i++) {
      mmb_Branch->GetEntry(i);
      simu->Fill();
   }
   

   //-- train NN
   TMultiLayerPerceptron *mlp = new TMultiLayerPerceptron("@pt1,@eta1,@phi1,@pt2,@eta2,@phi2,@Nak8j,@missET:5:3:type",simu,"Entry$%2", "(Entry$+1)%2");   
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
   TH1F* MLPmm = new TH1F("MLPmmh", "NN output", 50, -.5, 1.5);
   TH1F* MLPmmb = new TH1F("MLPmmbh", "NN output", 50, -.5, 1.5);

   MLPmm->SetDirectory(0);
   MLPmmb->SetDirectory(0);


//--feeding to NN
   //--mm
   Double_t params[8];

   for(i = 0; i < mm_Branch->GetEntries(); i++) {
      mm_Branch->GetEntry(i);

      params[0] = pt1_mm;
      params[1] = eta1_mm;
      params[2] = phi1_mm;
      params[3] = pt2_mm;
      params[4] = eta2_mm;
      params[5] = phi2_mm;
      params[6] = Nak8j_mm;
      params[7] = missET_mm;

      MLPmm->Fill(mlp->Evaluate(0, params));
   }

   //--mmb
   for(i = 0; i < mmb_Branch->GetEntries(); i++) {
      mmb_Branch->GetEntry(i);

      params[0] = pt1_mm;
      params[1] = eta1_mm;
      params[2] = phi1_mm;
      params[3] = pt2_mm;
      params[4] = eta2_mm;
      params[5] = phi2_mm;
      params[6] = Nak8j_mm;
      params[7] = missET_mm;
      MLPmmb->Fill(mlp->Evaluate(0, params));
   }

   signalStyling(MLPmm);
   backgroundStyling(MLPmmb);

   MLPmm-> Scale(100/MLPmm->Integral());
   MLPmmb-> Scale(100/MLPmmb->Integral());

   MLPmm->SetStats(0);
   MLPmmb->SetStats(0);

   MLPmmb->Draw("hist");
   MLPmm->Draw("hist same");

   TLegend *legend = new TLegend(.75, .80, .95, .95);
   legend->AddEntry(MLPmm, "mm");
   legend->AddEntry(MLPmmb, "mmb");

   legend->Draw();
   mlpa_canvas->cd(0);
   //ofile->Write();
   //ofile->Close();
   delete input;
}

