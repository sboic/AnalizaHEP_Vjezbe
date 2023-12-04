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

void Analyzer::PlotHistogram(TString input_file){

// priprema platna
canvas = new TCanvas();
canvas->SetCanvasSize(900,900);
histogram = new TH2F("Rekonstruirana masa i dR","Rekonstruirana masa i dR", 100.0, 2.0, 4.0, 100.0, 0.0, 1.5);

// petlja po svim događajima
for (jentry = 0; jentry < fChain->GetEntries(); jentry++) {
      LoadTree(jentry);
      fChain->GetEntry(jentry);

      // postavljanje četvervektora za elektron i pozitron mase 0
      e.SetPtEtaPhiM(ele_pt -> at (0),ele_eta -> at (0),ele_phi -> at (0),0.);
      p.SetPtEtaPhiM(ele_pt -> at (1),ele_eta -> at (1),ele_phi -> at (1),0.);
      
      // zbrojimo četvervektore
      J = e + p;

      // u histogram spremamo masu i dR
      histogram->Fill(J.M(),dR);
   }

// crtanje histograma
histogram->Draw("COLZ");
histogram->SetStats(0); // uklanjenje prozora sa statistikom
histogram->SetTitle("Rekonstruirana masa vs dR");
histogram->GetXaxis()->SetTitle("Masa u GeV");
histogram->GetYaxis()->SetTitle("dR");
gStyle->SetPalette(1);

// spremanje
canvas->Print("Histogram.png");
canvas->Print("Histogram.pdf");
canvas->Print("Histogram.root");

delete canvas;
delete histogram;
}
