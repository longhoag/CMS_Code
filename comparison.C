
void overlap(TH1F* h1, TH1F* h2, TH1F* h3, const char * title) {
   h1->SetLineWidth(2);
   h1->SetLineColor(kRed);
   h1->Scale(1000./h1->GetEntries());
   h1->GetXaxis()->SetTitle(title);
   h1->GetYaxis()->SetTitle("Events");
   h1->Draw("");

   h2->SetLineWidth(2);
   h2->SetLineColor(kGreen);
   h2->Scale(1000./h2->GetEntries());
   h2->Draw("same");

   h3->SetLineWidth(2);
   h3->SetLineColor(kBlue);
   h3->Scale(1000./h3->GetEntries());
   h3->Draw("same");

}

void comparison() {
   TFile *f1 = new TFile("DYTest.root");
   TFile *f2 = new TFile("wwTest.root");
   TFile *f3 = new TFile("ttTest.root");
 
 //--name in the graph (directories)
   TH1F* h1 = (TH1F*) f1->Get("analyzeBasicPat/MET_mumuSEL");
   TH1F* h2 = (TH1F*) f2->Get("analyzeBasicPat/MET_mumuSEL");
   TH1F* h3 = (TH1F*) f3->Get("analyzeBasicPat/MET_mumuSEL");

   TH1F* h4 = (TH1F*) f1->Get("analyzeBasicPat/MET_eeSEL");
   TH1F* h5 = (TH1F*) f2->Get("analyzeBasicPat/MET_eeSEL");
   TH1F* h6 = (TH1F*) f3->Get("analyzeBasicPat/MET_eeSEL");

   TH1F* h7 = (TH1F*) f1->Get("analyzeBasicPat/MET_emuSEL");
   TH1F* h8 = (TH1F*) f2->Get("analyzeBasicPat/MET_emuSEL");
   TH1F* h9 = (TH1F*) f3->Get("analyzeBasicPat/MET_emuSEL");

   TH1F* h10 = (TH1F*) f1->Get("analyzeBasicPat/Njets_all_");
   TH1F* h11 = (TH1F*) f2->Get("analyzeBasicPat/Njets_all_");
   TH1F* h12 = (TH1F*) f3->Get("analyzeBasicPat/Njets_all_");

   TH1F* h13 = (TH1F*) f1->Get("analyzeBasicPat/muonPt");
   TH1F* h14 = (TH1F*) f2->Get("analyzeBasicPat/muonPt");
   TH1F* h15 = (TH1F*) f3->Get("analyzeBasicPat/muonPt");

   TH1F* h16 = (TH1F*) f1->Get("analyzeBasicPat/elecPt");
   TH1F* h17 = (TH1F*) f2->Get("analyzeBasicPat/elecPt");
   TH1F* h18 = (TH1F*) f3->Get("analyzeBasicPat/elecPt");

   TH1F* h19 = (TH1F*) f1->Get("analyzeBasicPat/elec_muonPt");
   TH1F* h20 = (TH1F*) f2->Get("analyzeBasicPat/elec_muonPt");
   TH1F* h21 = (TH1F*) f3->Get("analyzeBasicPat/elec_muonPt");

   TH1F* h22 = (TH1F*) f1->Get("analyzeBasicPat/muonEta");
   TH1F* h23 = (TH1F*) f2->Get("analyzeBasicPat/muonEta");
   TH1F* h24 = (TH1F*) f3->Get("analyzeBasicPat/muonEta");

   TH1F* h25 = (TH1F*) f1->Get("analyzeBasicPat/elecEta");
   TH1F* h26 = (TH1F*) f2->Get("analyzeBasicPat/elecEta");
   TH1F* h27 = (TH1F*) f3->Get("analyzeBasicPat/elecEta");

   TH1F* h28 = (TH1F*) f1->Get("analyzeBasicPat/elec_muonEta");
   TH1F* h29 = (TH1F*) f2->Get("analyzeBasicPat/elec_muonEta");
   TH1F* h30 = (TH1F*) f3->Get("analyzeBasicPat/elec_muonEta");

   TH1F* h31 = (TH1F*) f1->Get("analyzeBasicPat/muonPhi");
   TH1F* h32 = (TH1F*) f2->Get("analyzeBasicPat/muonPhi");
   TH1F* h33 = (TH1F*) f3->Get("analyzeBasicPat/muonPhi");

   TH1F* h34 = (TH1F*) f1->Get("analyzeBasicPat/elecPhi");
   TH1F* h35 = (TH1F*) f2->Get("analyzeBasicPat/elecPhi");
   TH1F* h36 = (TH1F*) f3->Get("analyzeBasicPat/elecPhi");

   TH1F* h37 = (TH1F*) f1->Get("analyzeBasicPat/elec_muonPhi");
   TH1F* h38 = (TH1F*) f2->Get("analyzeBasicPat/elec_muonPhi");
   TH1F* h39 = (TH1F*) f3->Get("analyzeBasicPat/elec_muonPhi");

//

   TCanvas *c11 = new TCanvas("c11", "MET Data");
   c11->Divide(2,2);
   c11->cd(1);
   overlap(h1, h2, h3, "GV");
   c11->cd(2);
   overlap(h4, h5, h6, "GV");
   c11->cd(3);
   overlap(h7, h8, h9, "GV");


   TCanvas *c12 = new TCanvas("c12", "Nj Data");
   c12->cd();
   overlap(h10, h11, h12, "number");

   TCanvas *c13 = new TCanvas("c13", "Pt Data");
   c13->Divide(2,2);
   c13->cd(1);
   overlap(h13, h14, h15, "GeV");
   c13->cd(2);
   overlap(h16, h17, h18, "GeV");
   c13->cd(3);
   overlap(h19, h20, h21, "GeV");

   TCanvas *c14 = new TCanvas("c14", "Eta Data");
   c14->Divide(2,2);
   c14->cd(1);
   overlap(h22, h23, h24, "eta");
   c14->cd(2);
   overlap(h25, h26, h27, "eta");
   c14->cd(3);
   overlap(h28, h29, h30, "eta");

   TCanvas *c15 = new TCanvas("c15", "Phi Data");
   c15->Divide(2,2);
   c15->cd(1);
   overlap(h31, h32, h33, "rad");
   c15->cd(2);
   overlap(h34, h35, h36, "rad");
   c15->cd(3);
   overlap(h37, h38, h39, "rad");
}
