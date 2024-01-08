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

void Analyzer::TestStatistic(float mean, float dev){

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);
   rand = new TRandom3();

   histo1 = new TH1F("TestStatistic","TestStatistic",100,160,170);
   histo2 = new TH1F("Data","data",100,160,170);

   for(int i = 0; i < 1000000; i++){
      sum1 = 0;
      for(int j = 0; j < 100; j++){
         sum1 += rand->Gaus(mean,dev);
      }
      sum1 /= 100;
      histo1->Fill(sum1);
   }
   data = 0;
   for (Long64_t jentry = 0; jentry < fChain->GetEntries(); jentry++) {
        LoadTree(jentry);
        fChain->GetEntry(jentry);
        data += height;
   }
   data /= fChain->GetEntries();

   histo1->Scale(1./histo1->Integral());
   histo1->Draw("HIST");
   line = new TLine(data,0,data,histo1->GetMaximum());
   line->Draw("SAME");

   p_value = histo1->Integral(histo1->FindBin(data), 100);
   z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value);

   cout << "P-vrijednost je " << p_value << " , a signifikantnost je " << z_score << endl;

   canvas->Print("TestStatistic.pdf");
}

void Analyzer::HypothesisTesting(TString country,float mean, float dev){

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);

   histo1 = new TH1F("H0","H0",100,160,175);
   histo2 = new TH1F("H1","H1",100,160,175);

   for(int i = 0; i < 1000000; i++){
      sum1 = 0;
      sum2 = 0;
      for(int j = 0; j < 100; j++){
         sum1 += rand->Gaus(166.1,6.5);
         sum2 += rand->Gaus(mean,dev);
      }
      sum1 /= 100;
      sum2 /= 100;
      histo1->Fill(sum1);
      histo2->Fill(sum2);
   }
   histo1->SetTitle("Italy and "+ country);
   gStyle->SetOptStat(0);
   histo1->SetLineColor(kBlue);
   histo1->Scale(1./histo1->Integral());
   histo1->Draw("HIST");
   histo2->SetLineColor(kRed);
   histo2->Scale(1./histo2->Integral());
   histo2->Draw("HIST SAME");  
   line = new TLine(data,0,data,histo1->GetMaximum());
   line->Draw("SAME");  

   legend = new TLegend(0.7, 0.7, 0.9, 0.9);
   legend->AddEntry(histo1,"Italy","l");
   legend->AddEntry(histo2,country,"l");
   legend->Draw();

   canvas->Print("HypothesisTesting_Italy_and_"+country+".pdf");

   if ( mean < 166.1){
      pH0 = histo1->Integral(0,histo1->FindBin(data));
      pH1 = histo2->Integral(histo2->FindBin(data),100);
	}
	else{
      pH0 = histo1->Integral(histo1->FindBin(data),100);
      pH1 = histo2->Integral(0,histo2->FindBin(data));
	}
   cout << "DEBUG: pH0 = " << pH0 << ", pH1 = " << pH1 << endl;
   cout << "Alternativna hipoteza drzava " << country << " se moze odbaciti s " << (1 - std::min(static_cast<double>(pH1 / pH0), 1.0)) * 100 << " \% CL." << endl;


   delete histo1;
   delete histo2;
   delete canvas;
}