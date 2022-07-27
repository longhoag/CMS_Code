void graphing(TH2F* h, TH2F* g, const char* title) {
   h->Draw("Lego2");
   g->Draw(" Lego2 same");
   h->SetTitle(title);
   h->GetXaxis()->SetTitle("MET");
   h->GetYaxis()->SetTitle("Jet Count");
}

void metplot() {

   TFile *f1 = new TFile("ttTest.root");
   TFile *f2 = new TFile("DYTest.root");
   TFile *f3 = new TFile("wwTest.root");

   TH2F* h1 = (TH2F*) f1->Get("analyzeBasicPat/MET_eeSel_Jet_");
   TH2F* h2 = (TH2F*) f1->Get("analyzeBasicPat/MET_mumuSel_Jet_");

   TH2F* h3 = (TH2F*) f2->Get("analyzeBasicPat/MET_eeSel_Jet_");
   TH2F* h4 = (TH2F*) f2->Get("analyzeBasicPat/MET_mumuSel_Jet_");

   TH2F* h5 = (TH2F*) f3->Get("analyzeBasicPat/MET_eeSel_Jet_");
   TH2F* h6 = (TH2F*) f3->Get("analyzeBasicPat/MET_mumuSel_Jet_");

   TCanvas *c11 = new TCanvas();
   c11->Divide(2, 2);
   c11->cd(1);
   graphing(h1, h2, "MET_Jet_tt");

   c11->cd(2);
   graphing(h3, h4, "MET_Jet_DY");

   c11->cd(3);
   graphing(h5, h6, "MET_Jet_ww");
}