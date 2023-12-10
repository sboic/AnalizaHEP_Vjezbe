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
   //priprema platna
   canvas = new TCanvas();
   canvas-> SetCanvasSize(900,900);
   canvas-> Divide(2,2);
   canvas-> cd(1);
   if(input_file.Contains("ggH125")){
         Mass_histo_signal = new TH1F("Mass_histo_signal", "Reconstructed four lepton invariant mass", 50, 70., 170.);
         Dkin_histo_signal = new TH1F("Dkin_histo_signal", "Kinematic discriminant", 1000, 0., 1.);
         histo_signal = new TH2F("histo_signal", "Mass vs KD", 50, 70., 170., 20, 0., 1.0);
      }
   if(input_file.Contains("qqZZ")){
         Mass_histo_background = new TH1F("Mass_histo_background", "Reconstructed four lepton invariant mass", 50, 70., 170.);
         Dkin_histo_background = new TH1F("Dkin_histo_background", "Kinematic discriminant", 1000, 0., 1.);
         histo_background = new TH2F("histo_background", "Mass vs KD", 50, 70., 170., 20, 0., 1.0);
      }

   //petlja u kojoj inicializiramo histograme 4 svojstva za 4 leptona

   for(int i=0;i<4;i++){
      hist_name = "LeptonPt_hist" + to_string(i+1);
      LeptonPt_hist[i] = new TH1F(hist_name,"Transverzalni moment", 50,0.,150);
      
      hist_name = "LeptonEta_hist" + to_string (i+1);
      LeptonEta_hist[i] = new TH1F (hist_name, "Rapiditet", 50, -2.5, 2.5);
		
      hist_name = "LeptonPhi_hist" + to_string (i+1);
      LeptonPhi_hist[i] = new TH1F (hist_name, "Azimutalni kut", 40, -4., 4.);
		
      hist_name = "LeptonBDT_hist" + to_string (i+1);
      LeptonBDT_hist[i] = new TH1F (hist_name, "BDT score", 20, -1., 1.);
   }

   entries = fChain -> GetEntriesFast();
   input = new TFile (input_file);

   //counteri za skaliranje po tezini
   hCounters = (TH1F*) input -> Get ("ZZTree/Counters");
   sum_weight = (Float_t)hCounters -> GetBinContent (40);
	input_tree = (TTree*) input -> Get ("ZZTree/candTree");
	Init (input_tree);

   //petlja po događajima s skaliranjem po težini
   for(int i=0;i<entries;i++){
      fChain -> GetEntry(i);
      event_weight = (137. * 1000 * xsec * overallEventWeight) / sum_weight;
      for (int j = 0; j < 4; j++){
         LeptonPt_hist[j] -> Fill (LepPt -> at (j), event_weight);
         LeptonEta_hist[j] -> Fill (LepEta -> at (j), event_weight);
         LeptonPhi_hist[j] -> Fill (LepPhi -> at (j), event_weight);
         LeptonBDT_hist[j] -> Fill (LepBDT -> at (j), event_weight);
      }

      lept1.SetPtEtaPhiM(LepPt -> at (0), LepEta -> at (0), LepPhi -> at (0), 0.);
      lept2.SetPtEtaPhiM(LepPt -> at (1), LepEta -> at (1), LepPhi -> at (1), 0.);
      lept3.SetPtEtaPhiM(LepPt -> at (2), LepEta -> at (2), LepPhi -> at (2), 0.);
      lept4.SetPtEtaPhiM(LepPt -> at (3), LepEta -> at (3), LepPhi -> at (3), 0.);

      if (LepLepId -> at (0) + LepLepId -> at (1) == 0 && LepLepId -> at (2)+ LepLepId -> at (3) == 0){
         Z1 = lept1 + lept2;
         Z2 = lept3 + lept4;
         Higgs = Z1 + Z2;
      }

      if(input_file.Contains("ggH125")){
         Mass_histo_signal->Fill(Higgs.M(),event_weight);
         Dkin = 1/(1+p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
         Dkin_histo_signal->Fill(Dkin, event_weight);
         histo_signal->Fill(Higgs.M(),Dkin, event_weight );
      }
      if(input_file.Contains("qqZZ")){
         Mass_histo_background->Fill(Higgs.M(),event_weight);
         Dkin = 1/(1+70*p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
         Dkin_histo_background->Fill(Dkin, event_weight);
         histo_background->Fill(Higgs.M(),Dkin, event_weight );
      }
   }
for (int i = 0; i < 4; i++){
		LeptonPt_hist[i] -> SetStats (0);
      LeptonEta_hist[i] -> SetStats (0);
      LeptonPhi_hist[i] -> SetStats (0);
      LeptonBDT_hist[i] -> SetStats (0);
		
		LeptonPt_hist[i] -> GetXaxis() -> SetTitle ("p_{T} [GeV]");
      LeptonPt_hist[i] -> GetYaxis() -> SetTitle ("Events / 3 GeV");
		LeptonPt_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
		LeptonPt_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
		LeptonPt_hist[i] -> GetXaxis() -> SetTitleOffset (1.9);
		LeptonPt_hist[i] -> SetMaximum (1.6 * LeptonPt_hist[3] -> GetMaximum());		

		LeptonEta_hist[i] -> GetXaxis() -> SetTitle ("#Eta");
      LeptonEta_hist[i] -> GetYaxis() -> SetTitle ("Events / 0.1");
		LeptonEta_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
      LeptonEta_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
      LeptonEta_hist[i] -> GetXaxis() -> SetTitleOffset (1.8);
      LeptonEta_hist[i] -> SetMaximum (1.8 * LeptonEta_hist[3] -> GetMaximum());

		LeptonPhi_hist[i] -> GetXaxis() -> SetTitle ("#Phi");
      LeptonPhi_hist[i] -> GetYaxis() -> SetTitle ("Events / 0.2");
		LeptonPhi_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
      LeptonPhi_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
      LeptonPhi_hist[i] -> GetXaxis() -> SetTitleOffset (1.8);
      LeptonPhi_hist[i] -> SetMaximum (1.8 * LeptonPhi_hist[3] -> GetMaximum());

		LeptonBDT_hist[i] -> GetXaxis() -> SetTitle ("BDT score");
      LeptonBDT_hist[i] -> GetYaxis() -> SetTitle ("Events / 0.1");
		LeptonBDT_hist[i] -> GetXaxis() -> SetLabelSize (0.04);
      LeptonBDT_hist[i] -> GetYaxis() -> SetLabelSize (0.04);
      LeptonBDT_hist[i] -> GetXaxis() -> SetTitleOffset (1.8);
      LeptonBDT_hist[i] -> SetMaximum (200 * LeptonBDT_hist[3] -> GetMaximum());
	}
	LeptonPt_hist[0] -> SetLineColor (kRed);
	LeptonEta_hist[0] -> SetLineColor (kRed);
   LeptonPhi_hist[0] -> SetLineColor (kRed);
   LeptonBDT_hist[0] -> SetLineColor (kRed);	
	
	LeptonPt_hist[0] -> SetFillColorAlpha (kRed,0.35);
   LeptonEta_hist[0] -> SetFillColorAlpha (kRed,0.35);
   LeptonPhi_hist[0] -> SetFillColorAlpha (kRed,0.35);
   LeptonBDT_hist[0] -> SetFillColorAlpha (kRed,0.35);  

   LeptonPt_hist[1] -> SetLineColor (kBlue);
   LeptonEta_hist[1] -> SetLineColor (kBlue);
   LeptonPhi_hist[1] -> SetLineColor (kBlue);
   LeptonBDT_hist[1] -> SetLineColor (kBlue);

	LeptonPt_hist[1] -> SetFillColorAlpha (kBlue,0.35);
   LeptonEta_hist[1] -> SetFillColorAlpha (kBlue,0.35);
   LeptonPhi_hist[1] -> SetFillColorAlpha (kBlue,0.35);
   LeptonBDT_hist[1] -> SetFillColorAlpha (kBlue,0.35);

   LeptonPt_hist[2] -> SetLineColor (kGreen);
   LeptonEta_hist[2] -> SetLineColor (kGreen);
   LeptonPhi_hist[2] -> SetLineColor (kGreen);
   LeptonBDT_hist[2] -> SetLineColor (kGreen);

	LeptonPt_hist[2] -> SetFillColorAlpha (kGreen,0.35);
   LeptonEta_hist[2] -> SetFillColorAlpha (kGreen,0.35);
   LeptonPhi_hist[2] -> SetFillColorAlpha (kGreen,0.35);
   LeptonBDT_hist[2] -> SetFillColorAlpha (kGreen,0.35);

	LeptonPt_hist[3] -> SetLineColor (kBlack);
   LeptonEta_hist[3] -> SetLineColor (kBlack);
   LeptonPhi_hist[3] -> SetLineColor (kBlack);
   LeptonBDT_hist[3] -> SetLineColor (kBlack);

	LeptonPt_hist[3] -> SetFillColorAlpha (kBlack,0.35);
   LeptonEta_hist[3] -> SetFillColorAlpha (kBlack,0.35);
   LeptonPhi_hist[3] -> SetFillColorAlpha (kBlack,0.35);
   LeptonBDT_hist[3] -> SetFillColorAlpha (kBlack,0.35);

   gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);	

	LeptonPt_hist[0] -> Draw ("HIST");
	LeptonPt_hist[1] -> Draw ("HIST SAME");
	LeptonPt_hist[2] -> Draw ("HIST SAME");
	LeptonPt_hist[3] -> Draw ("HIST SAME");     
	legend = CreateLegend (LeptonPt_hist[0], LeptonPt_hist[1], LeptonPt_hist[2], LeptonPt_hist[3]);
	legend -> Draw ();

	canvas -> cd (2);
	gPad -> SetLeftMargin(0.15);
	gPad -> SetBottomMargin (0.15);
	LeptonEta_hist[0] -> Draw ("HIST");
   LeptonEta_hist[1] -> Draw ("HIST SAME");
   LeptonEta_hist[2] -> Draw ("HIST SAME");
   LeptonEta_hist[3] -> Draw ("HIST SAME");

   legend = CreateLegend (LeptonEta_hist[0], LeptonEta_hist[1], LeptonEta_hist[2], LeptonEta_hist[3]);
   legend -> Draw ();

	canvas -> cd (3);
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);
	LeptonPhi_hist[0] -> Draw ("HIST");
   LeptonPhi_hist[1] -> Draw ("HIST SAME");
   LeptonPhi_hist[2] -> Draw ("HIST SAME");
   LeptonPhi_hist[3] -> Draw ("HIST SAME");

   legend = CreateLegend (LeptonPhi_hist[0], LeptonPhi_hist[1], LeptonPhi_hist[2], LeptonPhi_hist[3]);
   legend -> Draw ();

	canvas -> cd (4);
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);
	gPad -> SetLogy();
	LeptonBDT_hist[0] -> Draw ("HIST");
   LeptonBDT_hist[1] -> Draw ("HIST SAME");
   LeptonBDT_hist[2] -> Draw ("HIST SAME");
   LeptonBDT_hist[3] -> Draw ("HIST SAME");

   legend = CreateLegend (LeptonBDT_hist[0], LeptonBDT_hist[1], LeptonBDT_hist[2], LeptonBDT_hist[3]);
   legend -> Draw ();

   if(input_file.Contains("ggH125")) canvas-> Print("Leptons_signal.pdf");
   if(input_file.Contains("qqZZ")) canvas-> Print("Leptons_background.pdf");
}

   TLegend* Analyzer::CreateLegend (TH1F *lepton1, TH1F *lepton2, TH1F *lepton3, TH1F *lepton4){
	TLegend *leg = new TLegend (0.5, 0.7, 0.9, 0.9);
	leg -> AddEntry (lepton1, "1. lepton", "f");
	leg -> AddEntry (lepton2, "2. lepton", "f");
	leg -> AddEntry (lepton3, "3. lepton", "f");
	leg -> AddEntry (lepton4, "4. lepton", "f");
	
	return leg;

}

void Analyzer::PlotMass(){
   
   canvas = new TCanvas();
  //TLorentzVector lept1,lept2,lept3,lept4,Z1,Z2,Higgs;
   stack = new THStack("stack", "stack");
	canvas -> SetCanvasSize (900,900);
	gPad -> SetLeftMargin (0.15);
	gPad -> SetBottomMargin (0.15);

	Mass_histo_signal -> SetLineColor (kGreen);
   Mass_histo_signal -> SetFillColor (kGreen);
   Mass_histo_signal -> SetStats (0);
      
   Mass_histo_background -> SetLineColor (kRed);
	Mass_histo_background -> SetFillColor (kRed);
   Mass_histo_background -> SetStats (0);

   stack->SetTitle("Reconstructed four-lepton mass");

	cout << "Ocekivani broj signal Higgs bozona za 137/fb je " << Mass_histo_signal -> Integral () << endl;
   cout << "Ocekivani broj pozadinskih Higgs bozona za 137/fb je " << Mass_histo_background -> Integral () << endl;

  stack->Add(Mass_histo_background);
  stack->Add(Mass_histo_signal);

  stack->Draw("HIST");

  stack->SetMaximum(1.4*stack->GetMaximum());
  stack->GetXaxis()->SetTitle("m_{4l} [GeV]");
  stack->GetYaxis()->SetTitle("Events / 2 GeV");

  TLegend *leg;
  leg = new TLegend(0.5, 0.7, 0.9, 0.9);
  leg->AddEntry(Mass_histo_signal, "gluon-gluon fusion", "f");
  leg->AddEntry(Mass_histo_background, "q#bar{q} #rightarrow ZZ", "f");
  leg->SetTextSize(0.03);
  leg->Draw ();
  //canvas->Update();
  canvas->Print("Mass.histogram.pdf");
}

void Analyzer::PlotDkin(){
   canvas = new TCanvas();
   canvas-> Divide(2,2);

   canvas->cd(2);
   gPad->SetLeftMargin(0.15);

   TGraph *ROC = new TGraph();

   Dkin_histo_signal->Scale(1./Dkin_histo_signal->Integral());
   Dkin_histo_background->Scale(1./Dkin_histo_background->Integral());

  for(int i=0; i < 1000; i++)
  {
      float x = 1. - Dkin_histo_background->Integral(1, i+1);
      float y = 1. - Dkin_histo_signal->Integral(1,i+1);
      if ( x > 0.001 && y > 0.001 && x < 1.0 && y < 1.0) ROC->SetPoint(int(i),x,y);
  }
  ROC->SetMinimum(0.95);
  ROC->SetMaximum(1.0);

  ROC->SetMarkerStyle(20);
  ROC->SetMarkerSize(0.4);

  ROC->Draw("ap");

  ROC->GetXaxis()->SetLimits(0.00,0.05);
  ROC->GetXaxis()->SetTitle("Background efficiency");
  ROC->GetXaxis()->SetTitleFont(61);
  ROC->GetYaxis()->SetTitle("Signal efficiency");
  ROC->GetYaxis()->SetTitleFont(61);
  ROC->SetTitle("ROC curve");
  ROC->Draw("ap");
  canvas->Update();


  canvas->cd(1);
  gPad->SetLeftMargin(0.15);

  Dkin_histo_signal->Rebin(50);
  Dkin_histo_signal->SetLineColor(kRed - 2);
  Dkin_histo_signal->SetLineWidth(4);
  Dkin_histo_signal->SetStats(0);

  Dkin_histo_signal->GetXaxis()->SetTitle("D_{kin}");
  Dkin_histo_signal->GetYaxis()->SetTitle("Events / 0.1");


  Dkin_histo_background->Rebin(50);
  Dkin_histo_background->SetLineColor(kBlue - 2);
  Dkin_histo_background->SetLineWidth(4);
  Dkin_histo_background->SetStats(0);

  Dkin_histo_background->GetXaxis()->SetTitle("D_{kin}");
  Dkin_histo_background->GetYaxis()->SetTitle("Events / 0.1");

  Dkin_histo_signal->Draw("HIST");
  Dkin_histo_background->Draw("HIST SAME");

  Dkin_histo_signal->SetMaximum(1.1);

  TLegend *leg;
  leg = new TLegend(0.5,0.8,0.9,0.9);

  leg->AddEntry(Dkin_histo_signal, "gluon-gluon fusion", "f");
  leg->AddEntry(Dkin_histo_background, "q#bar{q} #rightarrow ZZ", "f");
  leg->SetTextSize(0.03);

  leg->Draw();

  canvas->cd(3);
  histo_background->Draw("COLZ");
  histo_background->SetMinimum(-0.01);
  histo_background->SetStats(0);
  histo_background->SetTitle("m_{4l} vs D_{kin} for background");
  histo_background->GetXaxis()->SetTitle("m_{4l} [GeV]");
  histo_background->GetYaxis()->SetTitle("D_{kin}");

  canvas->cd(4);
  histo_signal->Draw("COLZ");
  histo_signal->SetMinimum(-0.01);
  histo_signal->SetStats(0);
  histo_signal->SetTitle("m_{4l} vs D_{kin} for signal");
  histo_signal->GetXaxis()->SetTitle("m_{4l} [GeV]");
  histo_signal->GetYaxis()->SetTitle("D_{kin}");

  canvas->Print("Dkin.pdf");
}

void Analyzer::FitHiggsMass(){
 canvas = new TCanvas();
 canvas-> SetCanvasSize(1200,800);
 canvas-> Divide(2,1);
 canvas-> cd(1);

 fit_histo = new TH1F("FitHiggsMass","FitHiggsMass", 50, 70., 170.);
 fit_histo->Add(Mass_histo_background);
 fit_histo->Add(Mass_histo_signal);

 signal_function = new TF1("signal_function","[0]*[1] / ((x*x - [2]*[2])*(x*x - [2]*[2]) + 0.25*[1]*[1])",110,150);
 background_function = new TF1("background_function","[0] + [1]*x + [2]*x*x",110,150);

 signal_function->SetParameters(1.53541e+04,4.50573e+02,1.24269e+02 ); // visina širina i centar mase 1000 10 125
 background_function->SetParameters(5.30533e+01,-3.52892e-01,5.42850e-04);

 total_function = new TF1("total_function","[0]*[1] / ((x*x - [2]*[2])*(x*x - [2]*[2]) + 0.25*[1]*[1]) + [3] + [4]*x + [5]*x*x",110,150);
 total_function->SetParameters(1.53541e+04,4.50573e+02,1.24269e+02,5.30533e+01,-3.52892e-01,5.42850e-04);

 signal_function->SetLineColor(kRed);
 background_function->SetLineColor(kBlue);
 total_function->SetLineColor(kGreen);

 signal_function->SetTitle("Fit");
 signal_function->Draw();
 background_function->Draw("SAME");
 total_function->Draw("SAME");

 canvas->cd(2);
 gPad->SetLeftMargin(0.15);

 fit_histo->SetAxisRange(110,150,"X");
 fit_histo->GetXaxis()->SetTitle("m_{4l} [GeV]");
 fit_histo->GetYaxis()->SetTitle("Events / 2 GeV");

 fit_histo->Fit(total_function);

 gStyle->SetOptFit();
 fit_histo->Draw ("p E1 X0"); 

 canvas->Print("FitHiggsMass.pdf");
 canvas->Print("FitHiggsMass.png");
 canvas->Print("FitHiggsMass.root");
}

void Analyzer::FitHiggsML(){
 canvas = new TCanvas();
 canvas-> SetCanvasSize(1200,800);

 fit_histo = new TH1F("FitHiggsMass","FitHiggsMass", 50, 70., 170.);
 fit_histo->Add(Mass_histo_background);
 fit_histo->Add(Mass_histo_signal);

//moramo dodati jos jednog BW na peak oko 90
 total_function = new TF1("total_function","[0]*[1] / ((x*x - [2]*[2])*(x*x - [2]*[2]) + 0.25*[1]*[1]) + [3] + [4]*x + [5]*x*x + [6]*[7] / ((x*x - [8]*[8])*(x*x - [8]*[8]) + 0.25*[7]*[7])",70.,170.);
 total_function->SetParameters(1.53541e+04,4.50573e+02,1.24269e+02,5.30533e+01,-3.52892e-01,5.42850e-04,3.11118e+04,7.89863e+02,9.07704e+01);
 
 fit_histo->Fit(total_function,"L");
 
 fit_histo->SetAxisRange(70,170,"X");
 fit_histo->SetAxisRange(0,200,"Y");
 fit_histo->GetXaxis()->SetTitle("m_{4l} [GeV]");
 fit_histo->GetYaxis()->SetTitle("Events / 2 GeV");

 gStyle->SetOptFit();
 fit_histo->Draw ("p E1 X0"); 

 canvas->Print("FitHiggsMassML.pdf");
 canvas->Print("FitHiggsMassML.png");
 canvas->Print("FitHiggsMassML.root");
}