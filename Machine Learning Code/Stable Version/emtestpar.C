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

void emtestpar(Int_t ntrain = 100) {
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
   TTree* em_Branch = (TTree*) input->Get("em_Branch");
   TTree* emb_Branch = (TTree*) input2->Get("em_Branch");

   TFile* ofile = new TFile("output_ML","RECREATE");
   TTree *simu = new TTree("MonteCarlo", "Filtered Monte Carlo Events");

   Float_t pt1_em, eta1_em, phi1_em;
   Float_t pt2_em, eta2_em, phi2_em;
   Float_t Nak8j_em, missET_em;


   // Float_t pt1, eta1, phi1b;
   // Float_t pt2b, eta2b, phi2b;
   // Float_t Nak8jb, missETb;

   // Float_t pt1b, eta1b, phi1b;
   // Float_t pt2b, eta2b, phi2b;
   // Float_t Nak8jb, missETb;

   Int_t type;

//-- set branches
   em_Branch->SetBranchAddress("pt1",  &pt1_em);
   em_Branch->SetBranchAddress("eta1", &eta1_em);
   em_Branch->SetBranchAddress("phi1", &phi1_em);
   em_Branch->SetBranchAddress("pt2",  &pt2_em);
   em_Branch->SetBranchAddress("eta2", &eta2_em);
   em_Branch->SetBranchAddress("phi2", &phi2_em);
   em_Branch->SetBranchAddress("Nak8j",&Nak8j_em);
   em_Branch->SetBranchAddress("missET",&missET_em);

   emb_Branch->SetBranchAddress("pt1",  &pt1_em);
   emb_Branch->SetBranchAddress("eta1", &eta1_em);
   emb_Branch->SetBranchAddress("phi1", &phi1_em);
   emb_Branch->SetBranchAddress("pt2",  &pt2_em);
   emb_Branch->SetBranchAddress("eta2", &eta2_em);
   emb_Branch->SetBranchAddress("phi2", &phi2_em);
   emb_Branch->SetBranchAddress("Nak8j",&Nak8j_em);
   emb_Branch->SetBranchAddress("missET",&missET_em);
//  

//-- simu branch
   simu->Branch("pt1",   &pt1_em,   "pt1/F");
   simu->Branch("eta1",  &eta1_em,  "eta1/F");
   simu->Branch("phi1",  &phi1_em,  "phi1/F");
   simu->Branch("pt2",   &pt2_em,   "pt2/F");
   simu->Branch("eta2",  &eta2_em,  "eta2/F");
   simu->Branch("phi2",  &phi2_em,  "phi2/F");
   simu->Branch("Nak8j", &Nak8j_em, "Nak8j/F");
   simu->Branch("missET",&missET_em,"missET/F");

   simu->Branch("type",   &type,   "type/I");


//--type signal and background: 1-signal, 0-background
   Int_t i;
   type = 1;
   for(i = 0; i < em_Branch->GetEntries(); i++) {
      em_Branch->GetEntry(i);
      simu->Fill();
   }

   type = 0;
   for(i = 0; i < emb_Branch->GetEntries(); i++) {
      emb_Branch->GetEntry(i);
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
   TH1F* MLPem = new TH1F("MLPemh", "NN output", 50, -.5, 1.5);
   TH1F* MLPemb = new TH1F("MLPembh", "NN output", 50, -.5, 1.5);

   MLPem->SetDirectory(0);
   MLPemb->SetDirectory(0);


//--feeding to NN
   //--em
   Double_t params[8];

   for(i = 0; i < em_Branch->GetEntries(); i++) {
      em_Branch->GetEntry(i);

      params[0] = pt1_em;
      params[1] = eta1_em;
      params[2] = phi1_em;
      params[3] = pt2_em;
      params[4] = eta2_em;
      params[5] = phi2_em;
      params[6] = Nak8j_em;
      params[7] = missET_em;

      MLPem->Fill(mlp->Evaluate(0, params));
   }

   //--emb
   for(i = 0; i < emb_Branch->GetEntries(); i++) {
      emb_Branch->GetEntry(i);

      params[0] = pt1_em;
      params[1] = eta1_em;
      params[2] = phi1_em;
      params[3] = pt2_em;
      params[4] = eta2_em;
      params[5] = phi2_em;
      params[6] = Nak8j_em;
      params[7] = missET_em;
      MLPemb->Fill(mlp->Evaluate(0, params));
   }

   signalStyling(MLPem);
   backgroundStyling(MLPemb);

   MLPem-> Scale(100/MLPem->Integral());
   MLPemb-> Scale(100/MLPemb->Integral());

   MLPem->SetStats(0);
   MLPemb->SetStats(0);

   MLPemb->Draw("hist");
   MLPem->Draw("hist same");

   TLegend *legend = new TLegend(.75, .80, .95, .95);
   legend->AddEntry(MLPem, "em");
   legend->AddEntry(MLPemb, "emb");

   legend->Draw();
   mlpa_canvas->cd(0);
   //ofile->Write();
   //ofile->Close();
   delete input;
}

