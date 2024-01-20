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

void Analyzer::ReconstuctMass(TString file_name){

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);

   histo = new TH1F("Rekonstruirana masa","Rekonstruirana masa",100,0,500);

for (Long64_t jentry = 0; jentry < fChain->GetEntries(); jentry++) {
        LoadTree(jentry);
        fChain->GetEntry(jentry);

      P1.SetPxPyPzE(particle1_px,particle1_py,particle1_pz,particle1_E);
      P2.SetPxPyPzE(particle2_px,particle2_py,particle2_pz,particle2_E);

      P3 = P1 + P2;
      histo->Fill(P3.M());
}
   gStyle->SetOptStat(0);
   histo->Draw("EP");
   theory->FixParameter(1,100.);
   histo->Fit(theory);

   canvas->Print("Rekonstruirana masa.pdf");
}

void Analyzer::NullH(){

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);
   r3 = new TRandom3();

   histo_theory = new TH1F("Teoretski PDF","Teoretski PDF",200,0,50);

   theory = new TF1("Theory","[0] * TMath::Exp(-x/[1])",0.,100.);
   theory->SetParameters(100.,100.); 
   
   mH = 0.;
   
   for(int i=0; i<1000 ; i++){ //broj eksperimenata
         
        TString temp = "experiment" + to_string(i);
        experiment = new TH1F(temp,"experiment",100,0.,100.);
         
        for(int j=0; j<10000; j++){ // broj događaja
            experiment->Fill(r3->Exp(100));
        }
        
        theory->FixParameter(1,100);
        for (int j=10; j<90; j+=5){ //uzimam interval iz theory-a
			mH = j/1.0;
			experiment->Fit(theory,"Q","",mH-10,mH+10); // 20 GeV-a mi je interval
			chi2=theory->GetChisquare();
			histo_theory->Fill(chi2);
		}
      
    }
   gStyle->SetOptStat(0);
	histo_theory->Scale(1./histo_theory->Integral());
   histo_theory->Draw("HIST");

   canvas->Print("Nulta hipoteza.pdf");
}

void Analyzer::PValue(){
   canvas = new TCanvas();
	canvas->SetCanvasSize(900,900);
	r3 = new TRandom3();
   expected = new TGraph();
   observed = new TGraph();
   sigma = 0.0236;
   mH = 0;

   theory = new TF1("Theory","[0] * TMath::Exp(-x/[1])",0.,500.);
   theory->SetParameters(500.,100.);

   for (int i=10; i<490; i+=5){
	
		TString temp = "experiment2" + to_string(i);
      experiment = new TH1F(temp,"experiment2",200,0.,500.);	
	
		mH = i/1.0;
		
		for(int j=0; j<10000;j++) {
            if(r3->Rndm() > a_SM*TMath::Power((mH + b_SM),2) + c_SM ) experiment->Fill(r3->Exp(100)); // Generate SM process for probability given by theory
            else experiment->Fill(r3->Gaus(mH,sigma*mH)); // otherwise generate Higgs boson according to theoretical PDF
        }

		theory->FixParameter(1, 100.);
      experiment->Fit(theory,"Q","",mH-10,mH+10);
      chi2=theory->GetChisquare();
		p_value=histo_theory->Integral(histo_theory->FindBin(chi2),histo_theory->GetNbinsX())/histo_theory->Integral();
		expected->SetPoint(i/5,mH,p_value);


      theory->FixParameter(1,100.);
      histo->Fit(theory,"Q","",mH-10.,mH+10.);
      chi2_2=theory->GetChisquare();
      p_value_2=histo_theory->Integral(histo_theory->FindBin(chi2_2),histo_theory->GetNbinsX())/histo_theory->Integral();
      observed->SetPoint(i/5-2,mH,p_value_2);
	}

   observed->SetLineColor(kBlack);
   expected->SetLineColor(kRed);
   observed->Draw();
   expected->Draw("SAME");	
	canvas->Print("P-value.pdf");

}
