void mlpHiggs_3(Int_t ntrain=100) {
   const char *fname = "Ntuple_Drell_Yan_FINAL.root";
// const char *fname1 = "Ntuple_QCD.root";
   const char *fname2 = "Ntuple_VBFHiggs_FINAL.root";
   TFile *input = 0;
   TFile *input2 = 0;
   if (!gSystem->AccessPathName(fname)&& !gSystem->AccessPathName(fname2)) {
      input = TFile::Open(fname);
      input2 = TFile::Open(fname2);
   } else {
   printf("did not find the files");
   return;
   }
   // b is background
   TTree *Muon_Branch12b = (TTree *) input->Get("Muon_Branch12");
   TTree *Muon_Branch12 = (TTree *) input2->Get("Muon_Branch12");
   TTree *Muon_Branch34b = (TTree *) input->Get("Muon_Branch34");
   TTree *Muon_Branch34 = (TTree *) input2->Get("Muon_Branch34");   
   TTree *Muon_BranchMass1b = (TTree *) input->Get("Muon_BranchMass1");
   TTree *Muon_BranchMass1 = (TTree *) input2->Get("Muon_BranchMass1");
   TTree *Muon_BranchMass2b = (TTree *) input->Get("Muon_BranchMass2");
   TTree *Muon_BranchMass2 = (TTree *) input2->Get("Muon_BranchMass2");
   TTree *simu = new TTree("MonteCarlo", "Filtered Monte Carlo Events");
//   TTree *Electron_Branch = (TTree *) input->Get("Electron_Branch");
//   TTree *Tau_Branch = (TTree *) input->Get("Tau_Branch");
//   TTree *Jet_Branch = (TTree *) input->Get("Jet_Branch");
   Float_t pt1,eta1,phi1,iso1,vx1,vy1,vz1,pt2,eta2,phi2,iso2,vx2,vy2,vz2,pt3,eta3,phi3,iso3,vx3,vy3,vz3,pt4,eta4,phi4,iso4,vx4,vy4,vz4,mass14,mass23,massT,missET,deltaR1,deltaR2,deltaR3,deltaR4;
   Float_t Nmu;
   Int_t type;
   Muon_Branch12->SetBranchAddress("pt1",    &pt1);
   // cout<<"output"<<pt1;
   Muon_Branch12->SetBranchAddress("eta1",   &eta1);
   Muon_Branch12->SetBranchAddress("phi1",   &phi1);
   Muon_Branch12->SetBranchAddress("iso1",   &iso1);
   Muon_Branch12->SetBranchAddress("vx1",    &vx1);
   Muon_Branch12->SetBranchAddress("vy1",    &vy1);
   Muon_Branch12->SetBranchAddress("vz1",    &vz1);
   Muon_Branch12->SetBranchAddress("pt2",    &pt2);
   Muon_Branch12->SetBranchAddress("eta2",   &eta2);
   Muon_Branch12->SetBranchAddress("phi2",   &phi2);
   Muon_Branch12->SetBranchAddress("iso2",   &iso2);
   Muon_Branch12->SetBranchAddress("vx2",    &vx2);
   Muon_Branch12->SetBranchAddress("vy2",    &vy2);
   Muon_Branch12->SetBranchAddress("vz2",    &vz2);

   Muon_Branch12b->SetBranchAddress("pt1",    &pt1);
   Muon_Branch12b->SetBranchAddress("eta1",   &eta1);
   Muon_Branch12b->SetBranchAddress("phi1",   &phi1);
   Muon_Branch12b->SetBranchAddress("iso1",   &iso1);
   Muon_Branch12b->SetBranchAddress("vx1",    &vx1);
   Muon_Branch12b->SetBranchAddress("vy1",    &vy1);
   Muon_Branch12b->SetBranchAddress("vz1",    &vz1);
   Muon_Branch12b->SetBranchAddress("pt2",    &pt2);
   Muon_Branch12b->SetBranchAddress("eta2",   &eta2);
   Muon_Branch12b->SetBranchAddress("phi2",   &phi2);
   Muon_Branch12b->SetBranchAddress("iso2",   &iso2);
   Muon_Branch12b->SetBranchAddress("vx2",    &vx2);
   Muon_Branch12b->SetBranchAddress("vy2",    &vy2);
   Muon_Branch12b->SetBranchAddress("vz2",    &vz2);

   Muon_Branch34->SetBranchAddress("pt3",    &pt3);
   Muon_Branch34->SetBranchAddress("eta3",   &eta3);
   Muon_Branch34->SetBranchAddress("phi3",   &phi3);
   Muon_Branch34->SetBranchAddress("iso3",   &iso3);
   Muon_Branch34->SetBranchAddress("vx3",    &vx3);
   Muon_Branch34->SetBranchAddress("vy3",    &vy3);
   Muon_Branch34->SetBranchAddress("vz3",    &vz3);
   Muon_Branch34->SetBranchAddress("pt4",    &pt4);
   Muon_Branch34->SetBranchAddress("eta4",   &eta4);
   Muon_Branch34->SetBranchAddress("phi4",   &phi4);
   Muon_Branch34->SetBranchAddress("iso4",   &iso4);
   Muon_Branch34->SetBranchAddress("vx4",    &vx4);
   Muon_Branch34->SetBranchAddress("vy4",    &vy4);
   Muon_Branch34->SetBranchAddress("vz4",    &vz4);

   Muon_Branch34b->SetBranchAddress("pt3",    &pt3);
   Muon_Branch34b->SetBranchAddress("eta3",   &eta3);
   Muon_Branch34b->SetBranchAddress("phi3",   &phi3);
   Muon_Branch34b->SetBranchAddress("iso3",   &iso3);
   Muon_Branch34b->SetBranchAddress("vx3",    &vx3);
   Muon_Branch34b->SetBranchAddress("vy3",    &vy3);
   Muon_Branch34b->SetBranchAddress("vz3",    &vz3);
   Muon_Branch34b->SetBranchAddress("pt4",    &pt4);
   Muon_Branch34b->SetBranchAddress("eta4",   &eta4);
   Muon_Branch34b->SetBranchAddress("phi4",   &phi4);
   Muon_Branch34b->SetBranchAddress("iso4",   &iso4);
   Muon_Branch34b->SetBranchAddress("vx4",    &vx4);
   Muon_Branch34b->SetBranchAddress("vy4",    &vy4);
   Muon_Branch34b->SetBranchAddress("vz4",    &vz4);

   Muon_BranchMass1->SetBranchAddress("mass14",    &mass14);
   Muon_BranchMass1->SetBranchAddress("mass23",    &mass23);
   Muon_BranchMass1->SetBranchAddress("massT",    &massT);
   Muon_BranchMass1->SetBranchAddress("Nmu",    &Nmu);
   Muon_BranchMass1->SetBranchAddress("missET",    &missET);
   Muon_BranchMass1->SetBranchAddress("deltaR1",    &deltaR1);
   Muon_BranchMass1->SetBranchAddress("deltaR2",    &deltaR2);

   Muon_BranchMass1b->SetBranchAddress("mass14",    &mass14);
   Muon_BranchMass1b->SetBranchAddress("mass23",    &mass23);
   Muon_BranchMass1b->SetBranchAddress("massT",    &massT);
   Muon_BranchMass1b->SetBranchAddress("Nmu",    &Nmu);
   Muon_BranchMass1b->SetBranchAddress("missET",    &missET);
   Muon_BranchMass1b->SetBranchAddress("deltaR1",    &deltaR1);
   Muon_BranchMass1b->SetBranchAddress("deltaR2",    &deltaR2);

   Muon_BranchMass2->SetBranchAddress("mass14",    &mass14);
   Muon_BranchMass2->SetBranchAddress("mass23",    &mass23);
   Muon_BranchMass2->SetBranchAddress("massT",    &massT);
   Muon_BranchMass2->SetBranchAddress("Nmu",    &Nmu);
   Muon_BranchMass2->SetBranchAddress("missET",    &missET);
   Muon_BranchMass2->SetBranchAddress("deltaR3",    &deltaR3);
   Muon_BranchMass2->SetBranchAddress("deltaR4",    &deltaR4);

   Muon_BranchMass2b->SetBranchAddress("mass14",    &mass14);
   Muon_BranchMass2b->SetBranchAddress("mass23",    &mass23);
   Muon_BranchMass2b->SetBranchAddress("massT",    &massT);
   Muon_BranchMass2b->SetBranchAddress("Nmu",    &Nmu);
   Muon_BranchMass2b->SetBranchAddress("missET",    &missET);
   Muon_BranchMass2b->SetBranchAddress("deltaR3",    &deltaR3);
   Muon_BranchMass2b->SetBranchAddress("deltaR4",    &deltaR4);

/*   Electron_Branch->SetBranchAddress("pt1",    &pt1);
   Electron_Branch->SetBranchAddress("eta1",   &eta1);
   Electron_Branch->SetBranchAddress("phi1",   &phi1);
   Electron_Branch->SetBranchAddress("iso1",   &iso1);
   Electron_Branch->SetBranchAddress("vx1",    &vx1);
   Electron_Branch->SetBranchAddress("vy1",    &vy1);
   Electron_Branch->SetBranchAddress("vz1",    &vz1);
   Electron_Branch->SetBranchAddress("mass",   &mass);
   Electron_Branch->SetBranchAddress("Ne",     &Ne);
   Electron_Branch->SetBranchAddress("missET", &missET);
   Tau_Branch->SetBranchAddress("pt1",    &pt1);
   Tau_Branch->SetBranchAddress("eta1",   &eta1);
   Tau_Branch->SetBranchAddress("phi1",   &phi1);
   Tau_Branch->SetBranchAddress("vx1",    &vx1);
   Tau_Branch->SetBranchAddress("vy1",    &vy1);
   Tau_Branch->SetBranchAddress("mass",   &mass);
   Tau_Branch->SetBranchAddress("Nt",     &Nt);
   Tau_Branch->SetBranchAddress("missET", &missET);
   Jet_Branch->SetBranchAddress("pt1",    &pt1);
   Jet_Branch->SetBranchAddress("eta1",   &eta1);
   Jet_Branch->SetBranchAddress("phi1",   &phi1);
   Jet_Branch->SetBranchAddress("vx1",    &vx1);
   Jet_Branch->SetBranchAddress("vy1",    &vy1); 
   Jet_Branch->SetBranchAddress("mass",   &mass);
   Jet_Branch->SetBranchAddress("Nj",     &Nj);
   Jet_Branch->SetBranchAddress("missET", &missET); 
*/

   simu->Branch("pt1",    &pt1,    "pt1/F");
   simu->Branch("eta1",   &eta1,   "eta1/F");
   simu->Branch("phi1",   &phi1,   "phi1/F");
   simu->Branch("iso1",   &iso1,   "iso1/F");
   simu->Branch("vx1",    &vx1,    "vx1/F");
   simu->Branch("vy1",    &vy1,    "vy1/F");
   simu->Branch("vz1",    &vz1,    "vz1/F");
   simu->Branch("pt2",    &pt2,    "pt2/F");
   simu->Branch("eta2",   &eta2,   "eta2/F");
   simu->Branch("phi2",   &phi2,   "phi2/F");
   simu->Branch("iso2",   &iso2,   "iso2/F");
   simu->Branch("vx2",    &vx2,    "vx2/F");
   simu->Branch("vy2",    &vy2,    "vy2/F");
   simu->Branch("vz2",    &vz2,    "vz2/F");
   simu->Branch("pt3",    &pt3,    "pt3/F");
   simu->Branch("eta3",   &eta3,   "eta3/F");
   simu->Branch("phi3",   &phi3,   "phi3/F");
   simu->Branch("iso3",   &iso3,   "iso3/F");
   simu->Branch("vx3",    &vx3,    "vx3/F");
   simu->Branch("vy3",    &vy3,    "vy3/F");
   simu->Branch("vz3",    &vz3,    "vz3/F");
   simu->Branch("pt4",    &pt4,    "pt4/F");
   simu->Branch("eta4",   &eta4,   "eta4/F");
   simu->Branch("phi4",   &phi4,   "phi4/F");
   simu->Branch("iso4",   &iso4,   "iso4/F");
   simu->Branch("vx4",    &vx4,    "vx4/F");
   simu->Branch("vy4",    &vy4,    "vy4/F");
   simu->Branch("vz4",    &vz4,    "vz4/F");
   simu->Branch("mass14",   &mass14,   "mass14/F");
   simu->Branch("mass23",   &mass23,   "mass23/F");
   simu->Branch("massT",   &massT,   "massT/F");
   simu->Branch("Nmu",    &Nmu,    "Nmu/F");
   simu->Branch("missET", &missET, "missET/F");
   simu->Branch("deltaR1", &deltaR1, "deltaR1/F");
   simu->Branch("deltaR2", &deltaR2, "deltaR2/F");
   simu->Branch("deltaR3", &deltaR3, "deltaR3/F");
   simu->Branch("deltaR4", &deltaR4, "deltaR4/F");
   simu->Branch("type",   &type,   "type/I");

   type = 1;
   Int_t i;
   for (i = 0; i < Muon_Branch12->GetEntries(); i++) {
      Muon_Branch12->GetEntry(i);
      simu->Fill();
   }
   type = 0;
   for (i = 0; i < Muon_Branch12b->GetEntries(); i++) {
      Muon_Branch12b->GetEntry(i);
      simu->Fill();
   }
   type = 1;
   for (i = 0; i < Muon_Branch34->GetEntries(); i++) {
      Muon_Branch34->GetEntry(i);
      simu->Fill();
   }
   type = 0;
   for (i = 0; i < Muon_Branch34b->GetEntries(); i++) {
      Muon_Branch34b->GetEntry(i);
      simu->Fill();
   }
   type = 1;
   for (i = 0; i < Muon_BranchMass1->GetEntries(); i++) {
      Muon_BranchMass1->GetEntry(i);
      simu->Fill();
   }
   type = 0;
   for (i = 0; i < Muon_BranchMass1b->GetEntries(); i++) {
      Muon_BranchMass1b->GetEntry(i);
      simu->Fill();
   }
   type = 1;
   for (i = 0; i < Muon_BranchMass2->GetEntries(); i++) {
      Muon_BranchMass2->GetEntry(i);
      simu->Fill();
   }
   type = 0;
   for (i = 0; i < Muon_BranchMass2b->GetEntries(); i++) {
      Muon_BranchMass2b->GetEntry(i);
      simu->Fill();
   }
/*   type = 2;
   for (i = 0; i < Electron_Branch->GetEntries(); i++) {
      Electron_Branch->GetEntry(i);
      simu->Fill();
   }
   type = 1;
   for (i = 0; i < Tau_Branch->GetEntries(); i++) {
      Tau_Branch->GetEntry(i);
      simu->Fill();
   }
   type = 0;
   for (i = 0; i < Jet_Branch->GetEntries(); i++) {
      Jet_Branch->GetEntry(i);
      simu->Fill();
   } */

      TH1F *hpt1  = new TH1F("hpt1","pt1 distribution",100,0,300);
      TH1F *heta1  = new TH1F("heta1","eta1 distribution",100,-3,3);
      TH1F *hphi1  = new TH1F("hphi1","phi1 distribution",100,-5,5);
      TH1F *hiso1  = new TH1F("hiso1","iso1 distribution",100,-5,5);
      TH1F *hvx1  = new TH1F("hvx1","vx1 distribution",100,-0.5,0.5);
      TH1F *hvy1  = new TH1F("hvy1","vy1 distribution",100,-0.5,0.5);
      TH1F *hvz1  = new TH1F("hvz1","vz1 distribution",100,-30,30);
      TH1F *hpt2  = new TH1F("hpt2","pt1 distribution",100,0,300);
      TH1F *heta2  = new TH1F("heta2","eta1 distribution",100,-3,3);
      TH1F *hphi2  = new TH1F("hphi2","phi1 distribution",100,-5,5);
      TH1F *hiso2  = new TH1F("hiso2","iso1 distribution",100,-5,5);
      TH1F *hvx2  = new TH1F("hvx2","vx1 distribution",100,-0.5,0.5);
      TH1F *hvy2  = new TH1F("hvy2","vy1 distribution",100,-0.5,0.5);
      TH1F *hvz2  = new TH1F("hvz2","vz1 distribution",100,-30,30);
      TH1F *hpt3  = new TH1F("hpt3","pt1 distribution",100,0,300);
      TH1F *heta3  = new TH1F("heta3","eta1 distribution",100,-3,3);
      TH1F *hphi3  = new TH1F("hphi3","phi1 distribution",100,-5,5);
      TH1F *hiso3  = new TH1F("hiso3","iso1 distribution",100,-5,5);
      TH1F *hvx3  = new TH1F("hvx3","vx1 distribution",100,-0.5,0.5);
      TH1F *hvy3  = new TH1F("hvy3","vy1 distribution",100,-0.5,0.5);
      TH1F *hvz3  = new TH1F("hvz3","vz1 distribution",100,-30,30);
      TH1F *hpt4  = new TH1F("hpt4","pt1 distribution",100,0,300);
      TH1F *heta4  = new TH1F("heta4","eta1 distribution",100,-3,3);
      TH1F *hphi4  = new TH1F("hphi4","phi1 distribution",100,-5,5);
      TH1F *hiso4  = new TH1F("hiso4","iso1 distribution",100,-5,5);
      TH1F *hvx4  = new TH1F("hvx4","vx1 distribution",100,-0.5,0.5);
      TH1F *hvy4  = new TH1F("hvy4","vy1 distribution",100,-0.5,0.5);
      TH1F *hvz4  = new TH1F("hvz4","vz1 distribution",100,-30,30);
      TH1F *hmass14  = new TH1F("hmass14","mass14 distribution",90,30,120);
      TH1F *hmass23  = new TH1F("hmass23","mass23 distribution",90,30,120);
      TH1F *hmassT  = new TH1F("hmassT","massT distribution",90,30,120);
      TH1F *hNmu  = new TH1F("hNmu","Nmu distribution",11,0,11);
      TH1F *hmissET  = new TH1F("hmissET","missET distribution",100,0,2400);
      TH1F *hdeltaR1 = new TH1F("hdeltaR1", "deltaR1", 100, 0., 10.);
      TH1F *hdeltaR2 = new TH1F("hdeltaR2", "deltaR2", 100, 0., 10.);
      TH1F *hdeltaR3 = new TH1F("hdeltaR3", "deltaR3", 100, 0., 10.);
      TH1F *hdeltaR4 = new TH1F("hdeltaR4", "deltaR4", 100, 0., 10.);
//      printf("Got here");
      TCanvas *muon_canvas12 = new TCanvas("muon_canvas12","Muon Data",900,700);
      muon_canvas12->Divide(7,2);
      gPad->Divide(7,2);
      //TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentries12 = (Int_t)Muon_Branch12->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_canvas12->cd(i);
         //TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hpt1->Fill(pt1);
            }
         hpt1->SetFillColor(kBlue);
         hpt1->GetXaxis()->SetTitle("GeV");
         hpt1->GetYaxis()->SetTitle("Events");
         hpt1->Draw("hist");
         printf("Got Here");
         }
         if (i == 1) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            heta1->Fill(eta1);
            }
         heta1->SetFillColor(kBlue);
         heta1->GetXaxis()->SetTitle("GeV");
         heta1->GetYaxis()->SetTitle("Events");
         heta1->Draw("hist");
         }
         if (i == 2) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hphi1->Fill(phi1);
            }
         hphi1->SetFillColor(kBlue);
         hphi1->GetXaxis()->SetTitle("GeV");
         hphi1->GetYaxis()->SetTitle("Events");
         hphi1->Draw("hist");
         }
         if (i == 3) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hiso1->Fill(iso1);
            }
         hiso1->SetFillColor(kBlue);
         hiso1->GetXaxis()->SetTitle("GeV");
         hiso1->GetYaxis()->SetTitle("Events");
         hiso1->Draw("hist");
         }
         if (i == 4) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hvx1->Fill(vx1);
            }
         hvx1->SetFillColor(kBlue);
         hvx1->GetXaxis()->SetTitle("GeV");
         hvx1->GetYaxis()->SetTitle("Events");
         hvx1->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hvy1->Fill(vy1);
            }
         hvy1->SetFillColor(kBlue);
         hvy1->GetXaxis()->SetTitle("GeV");
         hvy1->GetYaxis()->SetTitle("Events");
         hvy1->Draw("hist");
         }
         if (i == 6) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hvz1->Fill(vz1);
            }
         hvz1->SetFillColor(kBlue);
         hvz1->GetXaxis()->SetTitle("GeV");
         hvz1->GetYaxis()->SetTitle("Events");
         hvz1->Draw("hist");
         }
         if (i == 7) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hpt2->Fill(pt2);
            }
         hpt2->SetFillColor(kBlue);
         hpt2->GetXaxis()->SetTitle("GeV");
         hpt2->GetYaxis()->SetTitle("Events");
         hpt2->Draw("hist");
         }
         if (i == 8) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            heta2->Fill(eta2);
            }
         heta2->SetFillColor(kBlue);
         heta2->GetXaxis()->SetTitle("GeV");
         heta2->GetYaxis()->SetTitle("Events");
         heta2->Draw("hist");
         }
         if (i == 9) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hphi2->Fill(phi2);
            }
         hphi2->SetFillColor(kBlue);
         hphi2->GetXaxis()->SetTitle("GeV");
         hphi2->GetYaxis()->SetTitle("Events");
         hphi2->Draw("hist");
         }
         if (i == 10) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hiso2->Fill(iso2);
            }
         hiso2->SetFillColor(kBlue);
         hiso2->GetXaxis()->SetTitle("GeV");
         hiso2->GetYaxis()->SetTitle("Events");
         hiso2->Draw("hist");
         }
         if (i == 11) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hvx2->Fill(vx2);
            }
         hvx2->SetFillColor(kBlue);
         hvx2->GetXaxis()->SetTitle("GeV");
         hvx2->GetYaxis()->SetTitle("Events");
         hvx2->Draw("hist");
         }
         if (i == 12) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hvy2->Fill(vy2);
            }
         hvy2->SetFillColor(kBlue);
         hvy2->GetXaxis()->SetTitle("GeV");
         hvy2->GetYaxis()->SetTitle("Events");
         hvy2->Draw("hist");
         }
         if (i == 13) {
            for (j = 0; j < Muon_Branch12->GetEntries(); j++) {
            Muon_Branch12->GetEntry(j);
            hvz2->Fill(vz2);
            }
         hvz2->SetFillColor(kBlue);
         hvz2->GetXaxis()->SetTitle("GeV");
         hvz2->GetYaxis()->SetTitle("Events");
         hvz2->Draw("hist");
         }
      }

      TCanvas *muon_canvas12b = new TCanvas("muon_canvas12b","Muon Data");
      muon_canvas12b->Divide(7,2);
      // TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentries12b = (Int_t)Muon_Branch12b->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_canvas12b->cd(i);
         // TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hpt1->Fill(pt1);
            }
         hpt1->SetFillColor(kBlue);
         hpt1->GetXaxis()->SetTitle("GeV");
         hpt1->GetYaxis()->SetTitle("Events");
         hpt1->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            heta1->Fill(eta1);
            }
         heta1->SetFillColor(kBlue);
         heta1->GetXaxis()->SetTitle("GeV");
         heta1->GetYaxis()->SetTitle("Events");
         heta1->Draw("hist");
         }
         if (i == 2) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hphi1->Fill(phi1);
            }
         hphi1->SetFillColor(kBlue);
         hphi1->GetXaxis()->SetTitle("GeV");
         hphi1->GetYaxis()->SetTitle("Events");
         hphi1->Draw("hist");
         }
         if (i == 3) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hiso1->Fill(iso1);
            }
         hiso1->SetFillColor(kBlue);
         hiso1->GetXaxis()->SetTitle("GeV");
         hiso1->GetYaxis()->SetTitle("Events");
         hiso1->Draw("hist");
         }
         if (i == 4) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hvx1->Fill(vx1);
            }
         hvx1->SetFillColor(kBlue);
         hvx1->GetXaxis()->SetTitle("GeV");
         hvx1->GetYaxis()->SetTitle("Events");
         hvx1->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hvy1->Fill(vy1);
            }
         hvy1->SetFillColor(kBlue);
         hvy1->GetXaxis()->SetTitle("GeV");
         hvy1->GetYaxis()->SetTitle("Events");
         hvy1->Draw("hist");
         }
         if (i == 6) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hvz1->Fill(vz1);
            }
         hvz1->SetFillColor(kBlue);
         hvz1->GetXaxis()->SetTitle("GeV");
         hvz1->GetYaxis()->SetTitle("Events");
         hvz1->Draw("hist");
         }
         if (i == 7) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hpt2->Fill(pt2);
            }
         hpt2->SetFillColor(kBlue);
         hpt2->GetXaxis()->SetTitle("GeV");
         hpt2->GetYaxis()->SetTitle("Events");
         hpt2->Draw("hist");
         }
         if (i == 8) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            heta2->Fill(eta2);
            }
         heta2->SetFillColor(kBlue);
         heta2->GetXaxis()->SetTitle("GeV");
         heta2->GetYaxis()->SetTitle("Events");
         heta2->Draw("hist");
         }
         if (i == 9) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hphi2->Fill(phi2);
            }
         hphi2->SetFillColor(kBlue);
         hphi2->GetXaxis()->SetTitle("GeV");
         hphi2->GetYaxis()->SetTitle("Events");
         hphi2->Draw("hist");
         }
         if (i == 10) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hiso2->Fill(iso2);
            }
         hiso2->SetFillColor(kBlue);
         hiso2->GetXaxis()->SetTitle("GeV");
         hiso2->GetYaxis()->SetTitle("Events");
         hiso2->Draw("hist");
         }
         if (i == 11) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hvx2->Fill(vx2);
            }
         hvx2->SetFillColor(kBlue);
         hvx2->GetXaxis()->SetTitle("GeV");
         hvx2->GetYaxis()->SetTitle("Events");
         hvx2->Draw("hist");
         }
         if (i == 12) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hvy2->Fill(vy2);
            }
         hvy2->SetFillColor(kBlue);
         hvy2->GetXaxis()->SetTitle("GeV");
         hvy2->GetYaxis()->SetTitle("Events");
         hvy2->Draw("hist");
         }
         if (i == 13) {
            for (j = 0; j < Muon_Branch12b->GetEntries(); j++) {
            Muon_Branch12b->GetEntry(j);
            hvz2->Fill(vz2);
            }
         hvz2->SetFillColor(kBlue);
         hvz2->GetXaxis()->SetTitle("GeV");
         hvz2->GetYaxis()->SetTitle("Events");
         hvz2->Draw("hist");
         }
      }

      TCanvas *muon_canvas34 = new TCanvas("muon_canvas34","Muon Data");
      muon_canvas34->Divide(5,2);
      // TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentries34 = (Int_t)Muon_Branch34->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_canvas34->cd(i);
         // TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hpt3->Fill(pt3);
            }
         hpt3->SetFillColor(kBlue);
         hpt3->GetXaxis()->SetTitle("GeV");
         hpt3->GetYaxis()->SetTitle("Events");
         hpt3->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            heta3->Fill(eta3);
            }
         heta3->SetFillColor(kBlue);
         heta3->GetXaxis()->SetTitle("GeV");
         heta3->GetYaxis()->SetTitle("Events");
         heta3->Draw("hist");
         }
         if (i == 2) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hphi3->Fill(phi3);
            }
         hphi3->SetFillColor(kBlue);
         hphi3->GetXaxis()->SetTitle("GeV");
         hphi3->GetYaxis()->SetTitle("Events");
         hphi3->Draw("hist");
         }
         if (i == 3) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hiso3->Fill(iso3);
            }
         hiso3->SetFillColor(kBlue);
         hiso3->GetXaxis()->SetTitle("GeV");
         hiso3->GetYaxis()->SetTitle("Events");
         hiso3->Draw("hist");
         }
         if (i == 4) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hvx3->Fill(vx3);
            }
         hvx3->SetFillColor(kBlue);
         hvx3->GetXaxis()->SetTitle("GeV");
         hvx3->GetYaxis()->SetTitle("Events");
         hvx3->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hvy3->Fill(vy3);
            }
         hvy3->SetFillColor(kBlue);
         hvy3->GetXaxis()->SetTitle("GeV");
         hvy3->GetYaxis()->SetTitle("Events");
         hvy3->Draw("hist");
         }
         if (i == 6) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hvz3->Fill(vz3);
            }
         hvz3->SetFillColor(kBlue);
         hvz3->GetXaxis()->SetTitle("GeV");
         hvz3->GetYaxis()->SetTitle("Events");
         hvz3->Draw("hist");
         }
         if (i == 7) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hpt4->Fill(pt4);
            }
         hpt4->SetFillColor(kBlue);
         hpt4->GetXaxis()->SetTitle("GeV");
         hpt4->GetYaxis()->SetTitle("Events");
         hpt4->Draw("hist");
         }
         if (i == 8) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            heta4->Fill(eta4);
            }
         heta4->SetFillColor(kBlue);
         heta4->GetXaxis()->SetTitle("GeV");
         heta4->GetYaxis()->SetTitle("Events");
         heta4->Draw("hist");
         }
         if (i == 9) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hphi4->Fill(phi4);
            }
         hphi4->SetFillColor(kBlue);
         hphi4->GetXaxis()->SetTitle("GeV");
         hphi4->GetYaxis()->SetTitle("Events");
         hphi4->Draw("hist");
         }  
         if (i == 10) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hiso4->Fill(iso4);
            }
         hiso4->SetFillColor(kBlue);
         hiso4->GetXaxis()->SetTitle("GeV");
         hiso4->GetYaxis()->SetTitle("Events");
         hiso4->Draw("hist");
         }  
         if (i == 11) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hvx4->Fill(vx4);
            }
         hvx4->SetFillColor(kBlue);
         hvx4->GetXaxis()->SetTitle("GeV");
         hvx4->GetYaxis()->SetTitle("Events");
         hvx4->Draw("hist");
         }  
         if (i == 12) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hvy4->Fill(vy4);
            }
         hvy4->SetFillColor(kBlue);
         hvy4->GetXaxis()->SetTitle("GeV");
         hvy4->GetYaxis()->SetTitle("Events");
         hvy4->Draw("hist");
         }  
         if (i == 13) {
            for (j = 0; j < Muon_Branch34->GetEntries(); j++) {
            Muon_Branch34->GetEntry(j);
            hvz4->Fill(vz4);
            }
         hvz4->SetFillColor(kBlue);
         hvz4->GetXaxis()->SetTitle("GeV");
         hvz4->GetYaxis()->SetTitle("Events");
         hvz4->Draw("hist");
         }
      }

      TCanvas *muon_canvas34b = new TCanvas("muon_canvas34b","Muon Data");
      muon_canvas34b->Divide(5,2);
      // TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentries34b = (Int_t)Muon_Branch34b->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_canvas34b->cd(i);
         // TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hpt3->Fill(pt3);
            }
         hpt3->SetFillColor(kBlue);
         hpt3->GetXaxis()->SetTitle("GeV");
         hpt3->GetYaxis()->SetTitle("Events");
         hpt3->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            heta3->Fill(eta3);
            }
         heta3->SetFillColor(kBlue);
         heta3->GetXaxis()->SetTitle("GeV");
         heta3->GetYaxis()->SetTitle("Events");
         heta3->Draw("hist");
         }
         if (i == 2) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hphi3->Fill(phi3);
            }
         hphi3->SetFillColor(kBlue);
         hphi3->GetXaxis()->SetTitle("GeV");
         hphi3->GetYaxis()->SetTitle("Events");
         hphi3->Draw("hist");
         }
         if (i == 3) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hiso3->Fill(iso3);
            }
         hiso3->SetFillColor(kBlue);
         hiso3->GetXaxis()->SetTitle("GeV");
         hiso3->GetYaxis()->SetTitle("Events");
         hiso3->Draw("hist");
         }
         if (i == 4) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hvx3->Fill(vx3);
            }
         hvx3->SetFillColor(kBlue);
         hvx3->GetXaxis()->SetTitle("GeV");
         hvx3->GetYaxis()->SetTitle("Events");
         hvx3->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hvy3->Fill(vy3);
            }
         hvy3->SetFillColor(kBlue);
         hvy3->GetXaxis()->SetTitle("GeV");
         hvy3->GetYaxis()->SetTitle("Events");
         hvy3->Draw("hist");
         }  
         if (i == 6) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hvz3->Fill(vz3);
            }
         hvz3->SetFillColor(kBlue);
         hvz3->GetXaxis()->SetTitle("GeV");
         hvz3->GetYaxis()->SetTitle("Events");
         hvz3->Draw("hist");
         }  
         if (i == 7) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hpt4->Fill(pt4);
            }
         hpt4->SetFillColor(kBlue);
         hpt4->GetXaxis()->SetTitle("GeV");
         hpt4->GetYaxis()->SetTitle("Events");
         hpt4->Draw("hist");
         }  
         if (i == 8) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            heta4->Fill(eta4);
            }
         heta4->SetFillColor(kBlue);
         heta4->GetXaxis()->SetTitle("GeV");
         heta4->GetYaxis()->SetTitle("Events");
         heta4->Draw("hist");
         }  
         if (i == 9) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hphi4->Fill(phi4);
            }
         hphi4->SetFillColor(kBlue);
         hphi4->GetXaxis()->SetTitle("GeV");
         hphi4->GetYaxis()->SetTitle("Events");
         hphi4->Draw("hist");
         }  
         if (i == 10) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hiso4->Fill(iso4);
            }
         hiso4->SetFillColor(kBlue);
         hiso4->GetXaxis()->SetTitle("GeV");
         hiso4->GetYaxis()->SetTitle("Events");
         hiso4->Draw("hist");
         }
         if (i == 11) { 
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hvx4->Fill(vx4);
            }
         hvx4->SetFillColor(kBlue);
         hvx4->GetXaxis()->SetTitle("GeV");
         hvx4->GetYaxis()->SetTitle("Events");
         hvx4->Draw("hist");
         }
         if (i == 12) {
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hvy4->Fill(vy4);
            }
         hvy4->SetFillColor(kBlue);
         hvy4->GetXaxis()->SetTitle("GeV");
         hvy4->GetYaxis()->SetTitle("Events");
         hvy4->Draw("hist");
         }
         if (i == 13) { 
            for (j = 0; j < Muon_Branch34b->GetEntries(); j++) {
            Muon_Branch34b->GetEntry(j);
            hvz4->Fill(vz4);
            }
         hvz4->SetFillColor(kBlue);
         hvz4->GetXaxis()->SetTitle("GeV");
         hvz4->GetYaxis()->SetTitle("Events");
         hvz4->Draw("hist");
         }
      }

      TCanvas *muon_mass_canvas1 = new TCanvas("muon_mass_canvas1","Muon Data");
      muon_mass_canvas1->Divide(5,2);
      // TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentriesM1 = (Int_t)Muon_BranchMass1->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_mass_canvas1->cd(i);
         // TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_BranchMass1->GetEntries(); j++) {
            Muon_BranchMass1->GetEntry(j);
            hmass14->Fill(mass14);
            }
         hmass14->SetFillColor(kBlue);
         hmass14->GetXaxis()->SetTitle("GeV");
         hmass14->GetYaxis()->SetTitle("Events");
         hmass14->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Muon_BranchMass1->GetEntries(); j++) {
            Muon_BranchMass1->GetEntry(j);
            hmass23->Fill(mass23);
            }
         hmass23->SetFillColor(kBlue);
         hmass23->GetXaxis()->SetTitle("GeV");
         hmass23->GetYaxis()->SetTitle("Events");
         hmass23->Draw("hist");
         }
         if (i == 2) {
            for (j = 0; j < Muon_BranchMass1->GetEntries(); j++) {
            Muon_BranchMass1->GetEntry(j);
            hmassT->Fill(massT);
            }
         hmassT->SetFillColor(kBlue);
         hmassT->GetXaxis()->SetTitle("GeV");
         hmassT->GetYaxis()->SetTitle("Events");
         hmassT->Draw("hist");
         }
         if (i == 3) {
            for (j = 0; j < Muon_BranchMass1->GetEntries(); j++) {
            Muon_BranchMass1->GetEntry(j);
            hNmu->Fill(Nmu);
            }
         hNmu->SetFillColor(kBlue);
         hNmu->GetXaxis()->SetTitle("GeV");
         hNmu->GetYaxis()->SetTitle("Events");
         hNmu->Draw("hist");
         }
         if (i == 4) {
            for (j = 0; j < Muon_BranchMass1->GetEntries(); j++) {
            Muon_BranchMass1->GetEntry(j);
            hmissET->Fill(missET);
            }
         hmissET->SetFillColor(kBlue);
         hmissET->GetXaxis()->SetTitle("GeV");
         hmissET->GetYaxis()->SetTitle("Events");
         hmissET->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_BranchMass1->GetEntries(); j++) {
            Muon_BranchMass1->GetEntry(j);
            hdeltaR1->Fill(deltaR1);
            }
         hdeltaR1->SetFillColor(kBlue);
         hdeltaR1->GetXaxis()->SetTitle("GeV");
         hdeltaR1->GetYaxis()->SetTitle("Events");
         hdeltaR1->Draw("hist");
         }
         if (i == 6) {
            for (j = 0; j < Muon_BranchMass1->GetEntries(); j++) {
            Muon_BranchMass1->GetEntry(j);
            hdeltaR2->Fill(deltaR2);
            }
         hdeltaR2->SetFillColor(kBlue);
         hdeltaR2->GetXaxis()->SetTitle("GeV");
         hdeltaR2->GetYaxis()->SetTitle("Events");
         hdeltaR2->Draw("hist");
         }
      }

      TCanvas *muon_mass_canvas1b = new TCanvas("muon_mass_canvas1b","Muon Data");
      muon_mass_canvas1b->Divide(5,2);
      // TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentriesM1b = (Int_t)Muon_BranchMass1b->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_mass_canvas1b->cd(i);
         // TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_BranchMass1b->GetEntries(); j++) {
            Muon_BranchMass1b->GetEntry(j);
            hmass14->Fill(mass14);
            }
         hmass14->SetFillColor(kBlue);
         hmass14->GetXaxis()->SetTitle("GeV");
         hmass14->GetYaxis()->SetTitle("Events");
         hmass14->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Muon_BranchMass1b->GetEntries(); j++) {
            Muon_BranchMass1b->GetEntry(j);
            hmass23->Fill(mass23);
            }
         hmass23->SetFillColor(kBlue);
         hmass23->GetXaxis()->SetTitle("GeV");
         hmass23->GetYaxis()->SetTitle("Events");
         hmass23->Draw("hist");
         }
         if (i == 2) {
            for (j = 0; j < Muon_BranchMass1b->GetEntries(); j++) {
            Muon_BranchMass1b->GetEntry(j);
            hmassT->Fill(massT);
            }
         hmassT->SetFillColor(kBlue);
         hmassT->GetXaxis()->SetTitle("GeV");
         hmassT->GetYaxis()->SetTitle("Events");
         hmassT->Draw("hist");
         }
         if (i == 3) {
            for (j = 0; j < Muon_BranchMass1b->GetEntries(); j++) {
            Muon_BranchMass1b->GetEntry(j);
            hNmu->Fill(Nmu);
            }
         hNmu->SetFillColor(kBlue);
         hNmu->GetXaxis()->SetTitle("GeV");
         hNmu->GetYaxis()->SetTitle("Events");
         hNmu->Draw("hist");
         }
         if (i == 4) {
            for (j = 0; j < Muon_BranchMass1b->GetEntries(); j++) {
            Muon_BranchMass1b->GetEntry(j);
            hmissET->Fill(missET);
            }
         hmissET->SetFillColor(kBlue);
         hmissET->GetXaxis()->SetTitle("GeV");
         hmissET->GetYaxis()->SetTitle("Events");
         hmissET->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_BranchMass1b->GetEntries(); j++) {
            Muon_BranchMass1b->GetEntry(j);
            hdeltaR1->Fill(deltaR1);
            }
         hdeltaR1->SetFillColor(kBlue);
         hdeltaR1->GetXaxis()->SetTitle("GeV");
         hdeltaR1->GetYaxis()->SetTitle("Events");
         hdeltaR1->Draw("hist");
         }  
         if (i == 6) {
            for (j = 0; j < Muon_BranchMass1b->GetEntries(); j++) {
            Muon_BranchMass1b->GetEntry(j);
            hdeltaR2->Fill(deltaR2);
            }
         hdeltaR2->SetFillColor(kBlue);
         hdeltaR2->GetXaxis()->SetTitle("GeV");
         hdeltaR2->GetYaxis()->SetTitle("Events");
         hdeltaR2->Draw("hist");
         }
      }

      TCanvas *muon_mass_canvas2 = new TCanvas("muon_mass_canvas2","Muon Data");
      muon_mass_canvas2->Divide(5,2);
      // TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentriesM2 = (Int_t)Muon_BranchMass2->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_mass_canvas2->cd(i);
         // TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_BranchMass2->GetEntries(); j++) {
            Muon_BranchMass2->GetEntry(j);
            hmass14->Fill(mass14);
            }
         hmass14->SetFillColor(kBlue);
         hmass14->GetXaxis()->SetTitle("GeV");
         hmass14->GetYaxis()->SetTitle("Events");
         hmass14->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Muon_BranchMass2->GetEntries(); j++) {
            Muon_BranchMass2->GetEntry(j);
            hmass23->Fill(mass23);
            }
         hmass23->SetFillColor(kBlue);
         hmass23->GetXaxis()->SetTitle("GeV");
         hmass23->GetYaxis()->SetTitle("Events");
         hmass23->Draw("hist");
         }
         if (i == 2) {
            for (j = 0; j < Muon_BranchMass2->GetEntries(); j++) {
            Muon_BranchMass2->GetEntry(j);
            hmassT->Fill(massT);
            }
         hmassT->SetFillColor(kBlue);
         hmassT->GetXaxis()->SetTitle("GeV");
         hmassT->GetYaxis()->SetTitle("Events");
         hmassT->Draw("hist");
         }
         if (i == 3) {
            for (j = 0; j < Muon_BranchMass2->GetEntries(); j++) {
            Muon_BranchMass2->GetEntry(j);
            hNmu->Fill(Nmu);
            }
         hNmu->SetFillColor(kBlue);
         hNmu->GetXaxis()->SetTitle("GeV");
         hNmu->GetYaxis()->SetTitle("Events");
         hNmu->Draw("hist");
         }
         if (i == 4) {
            for (j = 0; j < Muon_BranchMass2->GetEntries(); j++) {
            Muon_BranchMass2->GetEntry(j);
            hmissET->Fill(missET);
            }
         hmissET->SetFillColor(kBlue);
         hmissET->GetXaxis()->SetTitle("GeV");
         hmissET->GetYaxis()->SetTitle("Events");
         hmissET->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_BranchMass2->GetEntries(); j++) {
            Muon_BranchMass2->GetEntry(j);
            hdeltaR3->Fill(deltaR3);
            }
         hdeltaR3->SetFillColor(kBlue);
         hdeltaR3->GetXaxis()->SetTitle("GeV");
         hdeltaR3->GetYaxis()->SetTitle("Events");
         hdeltaR3->Draw("hist");
         }
         if (i == 6) {
            for (j = 0; j < Muon_BranchMass2->GetEntries(); j++) {
            Muon_BranchMass2->GetEntry(j);
            hdeltaR4->Fill(deltaR4);
            }
         hdeltaR4->SetFillColor(kBlue);
         hdeltaR4->GetXaxis()->SetTitle("GeV");
         hdeltaR4->GetYaxis()->SetTitle("Events");
         hdeltaR4->Draw("hist");
         }
      }

      TCanvas *muon_mass_canvas2b = new TCanvas("muon_mass_canvas2b","Muon Data");
      muon_mass_canvas2b->Divide(5,2);
      // TString myopt[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentriesM2b = (Int_t)Muon_BranchMass2b->GetEntries();
      for (Int_t i=0;i<14;i++) {
         muon_mass_canvas2b->cd(i);
         // TString title = TString::Format("Muon(%s)", myopt[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Muon_BranchMass2b->GetEntries(); j++) {
            Muon_BranchMass2b->GetEntry(j);
            hmass14->Fill(mass14);
            }
         hmass14->SetFillColor(kBlue);
         hmass14->GetXaxis()->SetTitle("GeV");
         hmass14->GetYaxis()->SetTitle("Events");
         hmass14->Draw("hist");
         }  
         if (i == 1) {
            for (j = 0; j < Muon_BranchMass2b->GetEntries(); j++) {
            Muon_BranchMass2b->GetEntry(j);
            hmass23->Fill(mass23);
            }
         hmass23->SetFillColor(kBlue);
         hmass23->GetXaxis()->SetTitle("GeV");
         hmass23->GetYaxis()->SetTitle("Events");
         hmass23->Draw("hist");
         }  
         if (i == 2) {
            for (j = 0; j < Muon_BranchMass2b->GetEntries(); j++) {
            Muon_BranchMass2b->GetEntry(j);
            hmassT->Fill(massT);
            }
         hmassT->SetFillColor(kBlue);
         hmassT->GetXaxis()->SetTitle("GeV");
         hmassT->GetYaxis()->SetTitle("Events");
         hmassT->Draw("hist");
         }  
         if (i == 3) {
            for (j = 0; j < Muon_BranchMass2b->GetEntries(); j++) {
            Muon_BranchMass2b->GetEntry(j);
            hNmu->Fill(Nmu);
            }
         hNmu->SetFillColor(kBlue);
         hNmu->GetXaxis()->SetTitle("GeV");
         hNmu->GetYaxis()->SetTitle("Events");
         hNmu->Draw("hist");
         }  
         if (i == 4) {
            for (j = 0; j < Muon_BranchMass2b->GetEntries(); j++) {
            Muon_BranchMass2b->GetEntry(j);
            hmissET->Fill(missET);
            }
         hmissET->SetFillColor(kBlue);
         hmissET->GetXaxis()->SetTitle("GeV");
         hmissET->GetYaxis()->SetTitle("Events");
         hmissET->Draw("hist");
         }
         if (i == 5) {
            for (j = 0; j < Muon_BranchMass2b->GetEntries(); j++) {
            Muon_BranchMass2b->GetEntry(j);
            hdeltaR3->Fill(deltaR3);
            }
         hdeltaR3->SetFillColor(kBlue);
         hdeltaR3->GetXaxis()->SetTitle("GeV");
         hdeltaR3->GetYaxis()->SetTitle("Events");
         hdeltaR3->Draw("hist");
         }
         if (i == 6) {
            for (j = 0; j < Muon_BranchMass2b->GetEntries(); j++) {
            Muon_BranchMass2b->GetEntry(j);
            hdeltaR4->Fill(deltaR4);
            }
         hdeltaR4->SetFillColor(kBlue);
         hdeltaR4->GetXaxis()->SetTitle("GeV");
         hdeltaR4->GetYaxis()->SetTitle("Events");
         hdeltaR4->Draw("hist");
         }
      }

/*      TCanvas *electron_canvas = new TCanvas("electron_canvas","Electron Data");
      electron_canvas->Divide(5,2);
      // TString myopt1[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentries1 = (Int_t)Electron_Branch->GetEntries();
      for (Int_t i=0;i<10;i++) {
         electron_canvas->cd(i);
         // TString title = TString::Format("Electron(%s)", myopt1[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hpt1->Fill(pt1);
            }
         hpt1->SetFillColor(kBlue);
         hpt1->GetXaxis()->SetTitle("GeV");
         hpt1->GetYaxis()->SetTitle("Events");
         hpt1->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            heta1->Fill(eta1);
            }
         heta1->SetFillColor(kBlue);
         heta1->GetXaxis()->SetTitle("GeV");
         heta1->GetYaxis()->SetTitle("Events");
         heta1->Draw("Samehist");
         }
         if (i == 2) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hphi1->Fill(phi1);
            }
         hphi1->SetFillColor(kBlue);
         hphi1->GetXaxis()->SetTitle("GeV");
         hphi1->GetYaxis()->SetTitle("Events");
         hphi1->Draw("Samehist");
         }
         if (i == 3) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hiso1->Fill(iso1);
            }
         hiso1->SetFillColor(kBlue);
         hiso1->GetXaxis()->SetTitle("GeV");
         hiso1->GetYaxis()->SetTitle("Events");
         hiso1->Draw("Samehist");
         }
         if (i == 4) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hvx1->Fill(vx1);
            }
         hvx1->SetFillColor(kBlue);
         hvx1->GetXaxis()->SetTitle("GeV");
         hvx1->GetYaxis()->SetTitle("Events");
         hvx1->Draw("Samehist");
         }  
         if (i == 5) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hvy1->Fill(vy1);
            }
         hvy1->SetFillColor(kBlue);
         hvy1->GetXaxis()->SetTitle("GeV");
         hvy1->GetYaxis()->SetTitle("Events");
         hvy1->Draw("Samehist");
         }  
         if (i == 6) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hvz1->Fill(vz1);
            }
         hvz1->SetFillColor(kBlue);
         hvz1->GetXaxis()->SetTitle("GeV");
         hvz1->GetYaxis()->SetTitle("Events");
         hvz1->Draw("Samehist");
         }  
         if (i == 7) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hmass->Fill(mass);
            }
         hmass->SetFillColor(kBlue);
         hmass->GetXaxis()->SetTitle("GeV");
         hmass->GetYaxis()->SetTitle("Events");
         hmass->Draw("Samehist");
         }
         if (i == 8) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hNmu->Fill(Nmu);
            }
         hNmu->SetFillColor(kBlue);
         hNmu->GetXaxis()->SetTitle("GeV");
         hNmu->GetYaxis()->SetTitle("Events");
         hNmu->Draw("Samehist");
         }  
         if (i == 9) {
            for (j = 0; j < Electron_Branch->GetEntries(); j++) {
            Electron_Branch->GetEntry(j);
            hmissET->Fill(missET);
            }
         hmissET->SetFillColor(kBlue);
         hmissET->GetXaxis()->SetTitle("GeV");
         hmissET->GetYaxis()->SetTitle("Events");
         hmissET->Draw("Samehist");
         }
      }
      TCanvas* tau_canvas = new TCanvas("tau_canvas","Tau Data");
      tau_canvas->Divide(5,2);
      // TString myopt2[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentries2 = (Int_t)Tau_Branch->GetEntries();
      for (Int_t i=0;i<10;i++) {
         tau_canvas->cd(i);
         // TString title = TString::Format("Tau(%s)", myopt2[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hpt1->Fill(pt1);
            }
         hpt1->SetFillColor(kBlue);
         hpt1->GetXaxis()->SetTitle("GeV");
         hpt1->GetYaxis()->SetTitle("Events");
         hpt1->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            heta1->Fill(eta1);
            }
         heta1->SetFillColor(kBlue);
         heta1->GetXaxis()->SetTitle("GeV");
         heta1->GetYaxis()->SetTitle("Events");
         heta1->Draw("Samehist");
         }
         if (i == 2) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hphi1->Fill(phi1);
            }
         hphi1->SetFillColor(kBlue);
         hphi1->GetXaxis()->SetTitle("GeV");
         hphi1->GetYaxis()->SetTitle("Events");
         hphi1->Draw("Samehist");
         }
         if (i == 3) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hiso1->Fill(iso1);
            }
         hiso1->SetFillColor(kBlue);
         hiso1->GetXaxis()->SetTitle("GeV");
         hiso1->GetYaxis()->SetTitle("Events");
         hiso1->Draw("Samehist");
         }
         if (i == 4) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hvx1->Fill(vx1);
            }
         hvx1->SetFillColor(kBlue);
         hvx1->GetXaxis()->SetTitle("GeV");
         hvx1->GetYaxis()->SetTitle("Events");
         hvx1->Draw("Samehist");
         }
         if (i == 5) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hvy1->Fill(vy1);
            }
         hvy1->SetFillColor(kBlue);
         hvy1->GetXaxis()->SetTitle("GeV");
         hvy1->GetYaxis()->SetTitle("Events");
         hvy1->Draw("Samehist");
         }
         if (i == 6) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hvz1->Fill(vz1);
            }
         hvz1->SetFillColor(kBlue);
         hvz1->GetXaxis()->SetTitle("GeV");
         hvz1->GetYaxis()->SetTitle("Events");
         hvz1->Draw("Samehist");
         }
         if (i == 7) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hmass->Fill(mass);
            }
         hmass->SetFillColor(kBlue);
         hmass->GetXaxis()->SetTitle("GeV");
         hmass->GetYaxis()->SetTitle("Events");
         hmass->Draw("Samehist");
         }
         if (i == 8) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hNmu->Fill(Nmu);
            }
         hNmu->SetFillColor(kBlue);
         hNmu->GetXaxis()->SetTitle("GeV");
         hNmu->GetYaxis()->SetTitle("Events");
         hNmu->Draw("Samehist");
         }
         if (i == 9) {
            for (j = 0; j < Tau_Branch->GetEntries(); j++) {
            Tau_Branch->GetEntry(j);
            hmissET->Fill(missET);
            }
         hmissET->SetFillColor(kBlue);
         hmissET->GetXaxis()->SetTitle("GeV");
         hmissET->GetYaxis()->SetTitle("Events");
         hmissET->Draw("Samehist");
         }
      }
      TCanvas* jet_canvas = new TCanvas("jet_canvas","Jet Data");
      jet_canvas->Divide(5,2);
      // TString myopt3[10] = {"pt1","eta1","phi1","iso1","vx1","vy1","vz1","mass","Nmu","missET"};
      Int_t nentries3 = (Int_t)Jet_Branch->GetEntries();
      for (Int_t i=0;i<10;i++) {
         jet_canvas->cd(i);
         // TString title = TString::Format("Jet(%s)", myopt3[i].Data());
         Int_t j;
         if (i == 0) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hpt1->Fill(pt1);
            }
         hpt1->SetFillColor(kBlue);
         hpt1->GetXaxis()->SetTitle("GeV");
         hpt1->GetYaxis()->SetTitle("Events");
         hpt1->Draw("hist");
         }
         if (i == 1) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            heta1->Fill(eta1);
            }
         heta1->SetFillColor(kBlue);
         heta1->GetXaxis()->SetTitle("GeV");
         heta1->GetYaxis()->SetTitle("Events");
         heta1->Draw("Samehist");
         }
         if (i == 2) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hphi1->Fill(phi1);
            }
         hphi1->SetFillColor(kBlue);
         hphi1->GetXaxis()->SetTitle("GeV");
         hphi1->GetYaxis()->SetTitle("Events");
         hphi1->Draw("Samehist");
         }
         if (i == 3) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hiso1->Fill(iso1);
            }
         hiso1->SetFillColor(kBlue);
         hiso1->GetXaxis()->SetTitle("GeV");
         hiso1->GetYaxis()->SetTitle("Events");
         hiso1->Draw("Samehist");
         }
         if (i == 4) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hvx1->Fill(vx1);
            }
         hvx1->SetFillColor(kBlue);
         hvx1->GetXaxis()->SetTitle("GeV");
         hvx1->GetYaxis()->SetTitle("Events");
         hvx1->Draw("Samehist");
         }
         if (i == 5) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hvy1->Fill(vy1);
            }
         hvy1->SetFillColor(kBlue);
         hvy1->GetXaxis()->SetTitle("GeV");
         hvy1->GetYaxis()->SetTitle("Events");
         hvy1->Draw("Samehist");
         }
         if (i == 6) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hvz1->Fill(vz1);
            }
         hvz1->SetFillColor(kBlue);
         hvz1->GetXaxis()->SetTitle("GeV");
         hvz1->GetYaxis()->SetTitle("Events");
         hvz1->Draw("Samehist");
         }
         if (i == 7) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hmass->Fill(mass);
            }
         hmass->SetFillColor(kBlue);
         hmass->GetXaxis()->SetTitle("GeV");
         hmass->GetYaxis()->SetTitle("Events");
         hmass->Draw("Samehist");
         }
         if (i == 8) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hNmu->Fill(Nmu);
            }
         hNmu->SetFillColor(kBlue);
         hNmu->GetXaxis()->SetTitle("GeV");
         hNmu->GetYaxis()->SetTitle("Events");
         hNmu->Draw("Samehist");
         }
         if (i == 9) {
            for (j = 0; j < Jet_Branch->GetEntries(); j++) {
            Jet_Branch->GetEntry(j);
            hmissET->Fill(missET);
            }
         hmissET->SetFillColor(kBlue);
         hmissET->GetXaxis()->SetTitle("GeV");
         hmissET->GetYaxis()->SetTitle("Events");
         hmissET->Draw("Samehist");
         }
      }
*/
//   TH1F *hpt1  = new TH1F("hpt1","pt1 distribution",100,0,300);
//   TH2F *hpt1eta1 = new TH2F("hpt1eta1","pt1 vs eta1",30,0,500,30,0,500);

   //canvas

   // all entries and fill the histograms
//   Int_t nentries = (Int_t)Muon_Branch->GetEntries();
//   for (Int_t i=0;i<nentries;i++) {
//     Muon_Branch->GetEntry(i);
//     hpt1->Fill(pt1);
//     hpt1eta1->Fill(pt1,eta1);
//   }

   // Build and train the NN ptsumf is used as a weight since we are primarily
   // interested  by high pt events.
   // The datasets used here are the same as the default ones.
   TMultiLayerPerceptron *mlp =
      new TMultiLayerPerceptron("@pt1,@eta1,@phi1,@iso1,@vx1,@vy1,@vz1,@pt2,@eta2,@phi2,@iso2,@vx2,@vy2,@vz2,@pt3,@eta3,@phi3,@iso3,@vx3,@vy3,@vz3,@pt4,@eta4,@phi4,@iso4,@vx4,@vy4,@vz4,@deltaR1,@deltaR2,@deltaR3,@deltaR4,@mass14,@mass23,@massT,@missET,@Nmu:5:3:type",simu,"Entry$%2","(Entry$+1)%2");
   mlp->Train(ntrain, "text,graph,update=10");
   mlp->Export("test","python");
   // Use TMLPAnalyzer to see what it looks for
   TCanvas* mlpa_canvas = new TCanvas("mlpa_canvas","Network analysis Higgs");
   mlpa_canvas->Divide(2,2);
   TMLPAnalyzer ana(mlp);
   // Initialisation
   ana.GatherInformations();
   // output to the console
   ana.CheckNetwork();
   mlpa_canvas->cd(1);
   // shows how each variable influences the network
   ana.DrawDInputs();
   mlpa_canvas->cd(2);
   // shows the network structure
   mlp->Draw();
   mlpa_canvas->cd(3);
   // draws the resulting network
   ana.DrawNetwork(0,"type==1","type==0");
   mlpa_canvas->cd(4);
   // Use the NN to plot the results for each sample
   // This will give approx. the same result as DrawNetwork.
   // All entries are used, while DrawNetwork focuses on
   // the test sample. Also the xaxis range is manually set.
   TH1F *MLPMuon12b = new TH1F("MLPMuon12bh", "NN output", 50, -.5, 1.5);
   TH1F *MLPMuon12 = new TH1F("MLPMuon12h", "NN output", 50, -.5, 1.5);
   TH1F *MLPMuon34b = new TH1F("MLPMuon34bh", "NN output", 50, -.5, 1.5);
   TH1F *MLPMuon34 = new TH1F("MLPMuon34h", "NN output", 50, -.5, 1.5);
   TH1F *MLPMuonMass1b = new TH1F("MLPMuonMass1bh", "NN output", 50, -.5, 1.5);
   TH1F *MLPMuonMass1 = new TH1F("MLPMuonMass1h", "NN output", 50, -.5, 1.5);
   TH1F *MLPMuonMass2b = new TH1F("MLPMuonMass2bh", "NN output", 50, -.5, 1.5);
   TH1F *MLPMuonMass2 = new TH1F("MLPMuonMass2h", "NN output", 50, -.5, 1.5);
  // TH1F *Electron = new TH1F("Electronh", "NN output", 50, -.5, 1.5);
  // TH1F *Tau = new TH1F("Tauh", "NN output", 50, -.5, 1.5);
  // TH1F *Jet = new TH1F("Jeth", "NN output", 50, -.5, 1.5);
   MLPMuon12->SetDirectory(0);
   MLPMuon34->SetDirectory(0);
   MLPMuonMass1->SetDirectory(0);
   MLPMuonMass2->SetDirectory(0);
   MLPMuon12b->SetDirectory(0);
   MLPMuon34b->SetDirectory(0);
   MLPMuonMass1b->SetDirectory(0);
   MLPMuonMass2b->SetDirectory(0);
  // Electron->SetDirectory(0);
  // Tau->SetDirectory(0);
  // Jet->SetDirectory(0);
   Double_t params[14];
   for (i = 0; i < Muon_Branch12->GetEntries(); i++) {
      Muon_Branch12->GetEntry(i);
      params[0] = pt1;
      params[1] = eta1;
      params[2] = phi1;
      params[3] = iso1;
      params[4] = vx1;
      params[5] = vy1;
      params[6] = vz1;
      params[7] = pt2;
      params[8] = eta2;
      params[9] = phi2;
      params[10] = iso2;
      params[11] = vx2;
      params[12] = vy2;
      params[13] = vz2;
      MLPMuon12->Fill(mlp->Evaluate(0, params));
   }
   for (i = 0; i < Muon_Branch34->GetEntries(); i++) {
      Muon_Branch34->GetEntry(i);
      params[0] = pt3;
      params[1] = eta3;
      params[2] = phi3;
      params[3] = iso3;
      params[4] = vx3;
      params[5] = vy3;
      params[6] = vz3;
      params[7] = pt4;
      params[8] = eta4;
      params[9] = phi4;
      params[10] = iso4;
      params[11] = vx4;
      params[12] = vy4;
      params[13] = vz4;
      MLPMuon34->Fill(mlp->Evaluate(0, params));
   }
   for (i = 0; i < Muon_BranchMass1->GetEntries(); i++) {
      Muon_BranchMass1->GetEntry(i);
      params[0] = mass14;
      params[1] = mass23;
      params[2] = massT;
      params[3] = Nmu;
      params[4] = missET;
      params[5] = deltaR1;
      params[6] = deltaR2;
      MLPMuonMass1->Fill(mlp->Evaluate(0, params));
   }
   for (i = 0; i < Muon_BranchMass2->GetEntries(); i++) {
      Muon_BranchMass2->GetEntry(i);
      params[0] = mass14;
      params[1] = mass23;
      params[2] = massT;
      params[3] = Nmu;
      params[4] = missET;
      params[5] = deltaR3;
      params[6] = deltaR4;
      MLPMuonMass2->Fill(mlp->Evaluate(0, params));
   }
   for (i = 0; i < Muon_Branch12b->GetEntries(); i++) {
      Muon_Branch12b->GetEntry(i);
      params[0] = pt1;
      params[1] = eta1;
      params[2] = phi1;
      params[3] = iso1;
      params[4] = vx1;
      params[5] = vy1;
      params[6] = vz1;
      params[7] = pt2;
      params[8] = eta2;
      params[9] = phi2;
      params[10] = iso2;
      params[11] = vx2;
      params[12] = vy2;
      params[13] = vz2;
      MLPMuon12b->Fill(mlp->Evaluate(0, params));
   }
   for (i = 0; i < Muon_Branch34b->GetEntries(); i++) {
      Muon_Branch34b->GetEntry(i);
      params[0] = pt3;
      params[1] = eta3;
      params[2] = phi3;
      params[3] = iso3;
      params[4] = vx3;
      params[5] = vy3;
      params[6] = vz3;
      params[7] = pt4;
      params[8] = eta4;
      params[9] = phi4;
      params[10] = iso4;
      params[11] = vx4;
      params[12] = vy4;
      params[13] = vz4;
      MLPMuon34b->Fill(mlp->Evaluate(0, params));
   }
   for (i = 0; i < Muon_BranchMass1b->GetEntries(); i++) {
      Muon_BranchMass1b->GetEntry(i);
      params[0] = mass14;
      params[1] = mass23;
      params[2] = massT;
      params[3] = Nmu;
      params[4] = missET;
      params[5] = deltaR1;
      params[6] = deltaR2;
      MLPMuonMass1b->Fill(mlp->Evaluate(0, params));
   }
   for (i = 0; i < Muon_BranchMass2b->GetEntries(); i++) {
      Muon_BranchMass2b->GetEntry(i);
      params[0] = mass14;
      params[1] = mass23;
      params[2] = massT;
      params[3] = Nmu;
      params[4] = missET;
      params[5] = deltaR3;
      params[6] = deltaR4;
      MLPMuonMass2b->Fill(mlp->Evaluate(0, params));
   }
/*
   for (i = 0; i < Electron_Branch->GetEntries(); i++) {
      Electron_Branch->GetEntry(i);
      params[0] = pt1;
      params[1] = eta1;
      params[2] = phi1;
      Electron->Fill(mlp->Evaluate(0,params));
   }
   for (i = 0; i < Tau_Branch->GetEntries(); i++) {
      Tau_Branch->GetEntry(i);
      params[0] = pt1;
      params[1] = eta1;
      params[2] = phi1;
      Tau->Fill(mlp->Evaluate(0,params));
   }
   for (i = 0; i < Jet_Branch->GetEntries(); i++) {
      Jet_Branch->GetEntry(i);
      params[0] = pt1;
      params[1] = eta1;
      params[2] = phi1;
      Jet->Fill(mlp->Evaluate(0,params));
   } */
   MLPMuon12->SetLineColor(kBlue);
   MLPMuon12->SetFillStyle(3008);   
   MLPMuon12->SetFillColor(kBlue);
   
   MLPMuon34->SetLineColor(kBlue);
   MLPMuon34->SetFillStyle(3008);   MLPMuon34->SetFillColor(kBlue);
   MLPMuonMass1->SetLineColor(kBlue);
   MLPMuonMass1->SetFillStyle(3008);   MLPMuonMass1->SetFillColor(kBlue);
   MLPMuonMass2->SetLineColor(kBlue);
   MLPMuonMass2->SetFillStyle(3008);   MLPMuonMass2->SetFillColor(kBlue);
   MLPMuon12b->SetLineColor(kBlue);
   MLPMuon12b->SetFillStyle(3008);   MLPMuon12b->SetFillColor(kBlue);
   MLPMuon34b->SetLineColor(kBlue);
   MLPMuon34b->SetFillStyle(3008);   MLPMuon34b->SetFillColor(kBlue);
   MLPMuonMass1b->SetLineColor(kBlue);
   MLPMuonMass1b->SetFillStyle(3008);   MLPMuonMass1b->SetFillColor(kBlue);
   MLPMuonMass2b->SetLineColor(kBlue);
   MLPMuonMass2b->SetFillStyle(3008);   MLPMuonMass2b->SetFillColor(kBlue);
  // Electron->SetLineColor(kRed);
  // Electron->SetFillStyle(3003); Electron->SetFillColor(kRed);
  // Tau->SetLineColor(kYellow);
  // Tau->SetFillStyle(3002); Tau->SetFillColor(kYellow);
  // Jet->SetLineColor(kGreen);
  // Jet->SetFillStyle(3001); Jet->SetFillColor(kGreen);
   MLPMuon12->SetStats(0);
   MLPMuon34->SetStats(0);
   MLPMuonMass1->SetStats(0);
   MLPMuonMass2->SetStats(0);
   MLPMuon12b->SetStats(0);
   MLPMuon34b->SetStats(0);
   MLPMuonMass1b->SetStats(0);
   MLPMuonMass2b->SetStats(0);
  // Electron->SetStats(0);
  // Tau->SetStats(0);
  // Jet->SetStats(0);
   MLPMuon12->Draw();
   MLPMuon34->Draw("same");
   MLPMuonMass1->Draw("same");
   MLPMuonMass2->Draw("same");
   MLPMuon12b->Draw("same");
   MLPMuon34b->Draw("same");
   MLPMuonMass1b->Draw("same");
   MLPMuonMass2b->Draw("same");
  // Electron->Draw("same");
  // Tau->Draw("same");
  // Jet->Draw("same");
   TLegend *legend = new TLegend(.75, .80, .95, .95);
   legend->AddEntry(MLPMuon12, "Muon12");
   legend->AddEntry(MLPMuon34, "Muon34");
   legend->AddEntry(MLPMuonMass1, "MuonMass1");
   legend->AddEntry(MLPMuonMass2, "MuonMass2");
   legend->AddEntry(MLPMuon12b, "Muon12b");
   legend->AddEntry(MLPMuon34b, "Muon34b");
   legend->AddEntry(MLPMuonMass1b, "MuonMass1b");
   legend->AddEntry(MLPMuonMass2b, "MuonMass2b");
  // legend->AddEntry(Electron, "Electron");
  // legend->AddEntry(Tau, "Tau");
  // legend->AddEntry(Jet, "Jet");
   legend->Draw();
   mlpa_canvas->cd(0);
   delete input;
}
