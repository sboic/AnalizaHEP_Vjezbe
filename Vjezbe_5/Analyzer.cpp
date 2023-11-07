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

      // Ovdje možete pristupiti podacima za trenutni događaj
      //cout << "Event " << jentry << " - Particle names: " << *particle_name << " " << *particle_name1 << " " << *particle_name2 << std::endl;


   }
}

void Analyzer::PlotHistrogram(){
   
   TH1F* histogram1 = new TH1F("transverse_momentum_1", "Transverse Momentum of Particle 1", 100, 0, 150);
   TH1F* histogram2 = new TH1F("transverse_momentum_2", "Transverse Momentum of Particle 2", 100, 0, 150);
   TH1F* histogramHiggs = new TH1F("transverse_momentum_Higgs", "Transverse Momentum of Higgs",100, 0, 150);

   TLorentzVector P1,P2,PH;

     for (Long64_t jentry = 0; jentry < fChain->GetEntries(); jentry++) {
        LoadTree(jentry);
        fChain->GetEntry(jentry);

        P1.SetPxPyPzE(px1, py1, pz1, E1);
        P2.SetPxPyPzE(px2, py2, pz2, E2);
        PH = P1 + P2;    
         
        histogramHiggs->Fill(PH.Pt());    

        Float_t TransverseMomentum1 = sqrt(px1*px1 + py1*py1);
        histogram1->Fill(TransverseMomentum1);

        Float_t TransverseMomentum2 = sqrt(px2*px2 + py2*py2);
        histogram2->Fill(TransverseMomentum2);     
     }
   TCanvas* canvas = new TCanvas("canvas","Transverse Momentum",1300,600);
   
   histogram1->GetXaxis()->SetTitle("pT (GeV/c)");
   histogram1->GetYaxis()->SetTitle("Counts");
   
   histogram1->SetFillColor(kBlue);
   histogram1->SetFillStyle(3004); 
   histogram2->SetLineColor(kRed);
   histogram2->SetLineStyle(1);
  // histogram2->SetLineWidth(3);
   
   gStyle->SetOptStat(0);
   histogram1->SetTitle("Transverse Momentum Distribution of Particle 1");

   TLegend* legend = new TLegend(0.6, 0.75, 0.9, 0.9);
   legend->AddEntry(histogram1, "Simulated Data of particle 1", "f"); // "f" označava da je histogram ispunjen
   legend->AddEntry(histogram2, "Simulated Data of particle 2", "l"); //l je za liniju
   
   canvas->Divide(2,1);
   canvas->cd(1);
   histogram1->Draw();
   histogram2->Draw("same");
   legend->Draw();
   canvas->cd(2);
   histogramHiggs->SetTitle("Transverse Momentum Distribution of Higgs boson");
   histogramHiggs->GetXaxis()->SetTitle("pT (GeV/c)");
   histogramHiggs->GetYaxis()->SetTitle("Counts");
   histogramHiggs->Draw();

   canvas->Print("transverse_momentum.png");
   canvas->Print("transverse_momentum.pdf");
   TFile* rootFile = new TFile("transverse_momentum.root", "RECREATE");
   histogram1->Write();
   histogram2->Write();
   histogramHiggs->Write();
   rootFile->Close();


   delete histogram1;
   delete histogram2;
   delete canvas;
   delete rootFile;
}