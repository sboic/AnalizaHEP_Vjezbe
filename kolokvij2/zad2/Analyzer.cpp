#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void Analyzer::TestestStatistic(float lambda0, float lambda1){

   canvas = new TCanvas();
   canvas->SetCanvasSize(1000,900);
   rand = new TRandom3();

   histo0 = new TH1F("H0","H0",100,0,70);
   histo1 = new TH1F("H1","H1",100,0,70);


   for(int i = 0; i < 1000000; i++){
      x1 = rand->Poisson(lambda0);
      x2 = rand->Poisson(lambda1);
      histo0->Fill(x1);
      histo1->Fill(x2);
   }

   histo0->SetTitle("H0 i H1");
   gStyle->SetOptStat(0);
   histo0->Scale(1./histo0->Integral());
   histo0->SetLineColor(kRed);
   histo0->Draw("HISTO");
   histo1->SetLineColor(kBlue);
   histo1->Scale(1./histo1->Integral());
   histo1->Draw("HISTO SAME");
   histo0->GetYaxis()->SetRangeUser(0,0.08);
   histo0->GetXaxis()->SetTitle("Broj sudara");
   histo0->GetYaxis()->SetTitle("counts");


   legend = new TLegend(0.6,0.75,0.9,0.9);
   legend->AddEntry(histo0,"H0","l");
   legend->AddEntry(histo1,"H1","l");
   legend->Draw();
   
   canvas->Print("H0 i H1.pdf");
}

void Analyzer::PValue(){

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);

   histo3 = new TH1F("Data","Data",100,0,60);
   Poisson = new TF1("Poisson","TMath::Poisson(x,[0])",0,1000);
   Poisson->SetParameter(0,35.);
   Poisson->SetParName(0,"Lambda");

   data = 0;
   for (Long64_t jentry = 0; jentry < fChain->GetEntries(); jentry++) {
        LoadTree(jentry);
        fChain->GetEntry(jentry);
        histo3->Fill(BrojSudara);
        data += BrojSudara;
   }
   data /= fChain->GetEntries();

   histo3->Fit(Poisson,"");
   gStyle->SetOptStat(0);
   histo3->Scale(1./histo3->Integral());
   histo3->Draw("HISTO");

   p_value = histo3->Integral(0,histo3->FindBin(data));
   cout << "Lambda je " << Poisson->GetParameter(0) << endl;
   cout << "P-value je " << p_value << endl;

   canvas->Print("Data.pdf");

}