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

void Analyzer::PlotHistogram(TString inputfile){

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);

   fit_histo = new TH1F("Lifetime fit","Lifetime fit",10,0,12);

   for (Long64_t jentry = 0; jentry < fChain->GetEntries(); jentry++) {
        LoadTree(jentry);
        fChain->GetEntry(jentry);
        
        fit_histo->Fill(t);
   }
   
   fit = new TF1("fit","[0]/[1] * exp(-x/[1])",0,12);
   fit->SetParameters(1000,1);
   fit->SetParNames("Norm","#tau");

   fit_histo->Fit(fit,"L");
   fit_histo->GetXaxis()->SetTitle("Vrijeme");
   fit_histo->GetYaxis()->SetTitle("N");
   gStyle->SetOptFit();
   fit_histo->Draw();

   canvas->Print("Fit.zad1.pdf");
   cout << "1.Zadatak Tau = " << fit->GetParameter(1) << " ± " << fit->GetParError(1) << endl;
}
void Analyzer::Likelihood(){
   // Ovdje gledamo funkciju za t=1s
   fit = new TF1("Likelihood","[0]/x * exp(-1/x)",0,12);
   fit->SetParameter(0,1.24777e+03);

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);
   fit->SetTitle("Likelihood za t = 1s");
   fit->GetXaxis()->SetTitle("#Tau");
   fit->GetYaxis()->SetTitle("L");
   fit->Draw();

   canvas->Print("Fit.zad2.pdf");
}
void Analyzer::DetermineParameter(){
   sum = 0;
   i = 0;
   for (Long64_t jentry = 0; jentry < fChain->GetEntries(); jentry++) {
        LoadTree(jentry);
        fChain->GetEntry(jentry);
        
        sum+=t;
        i++; 
   }
   tau = sum/i;
   error = tau/sqrt(i);
   cout << "3.Zadatak Tau = " << tau << " ± " << error << endl;
}
void Analyzer::LogLikelihood(){

   fit = new TF1("LogLikelihood","-2 * ([0] * log(1./x) - [1]/x)",0.00001,12);
   fit->SetParameters(i,sum);

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);
   fit->SetTitle("LogLikelihood");
   fit->GetXaxis()->SetTitle("#Tau");
   fit->GetYaxis()->SetTitle("-2ln(L)");
   fit->Draw();

   canvas->Print("Fit.zad4.pdf");

   tau = fit->GetMinimumX();
   err_down = tau - fit->GetX( fit->GetMinimum(0.00001,12) + 1,0.00001,tau);
   err_up = fit->GetX( fit->GetMinimum(0.00001,12) + 1,tau,12) - tau;

   cout << "4.Zadatak Tau = " << tau << " - " << err_down << " + " << err_up << endl;
}

