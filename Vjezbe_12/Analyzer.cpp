#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
	histo_signal[0] = new TH1F("ele_pt_signal", "ele_pt_signal", 100, 0., 90.);
	histo_background[0] = new TH1F("ele_pt_background", "ele_pt_background", 100, 0., 90.);

	histo_signal[1] = new TH1F("scl_eta_signal", "scl_eta_signal", 100, -3.5, 3.5);
   histo_background[1] = new TH1F("scl_eta_background", "scl_eta_background", 100, -3.5, 3.5);

	histo_signal[2] = new TH1F("ele_hadronicOverEm_signal", "ele_hadronicOverEm_signal", 100, -0.001, 0.1);
   histo_background[2] = new TH1F("ele_hadronicOverEm_background", "ele_hadronicOverEm_background", 100, -0.001, 0.1);

	histo_signal[3] = new TH1F("ele_gsfchi2_signal", "ele_gsfchi2_signal", 100, 0., 3.5);
   histo_background[3] = new TH1F("ele_gsfchi2_background", "ele_gsfchi2_background", 100, 0., 3.5);

	histo_signal[4] = new TH1F("ele_fbrem_signal", "ele_fbrem_signal", 100, -0.2, 1.);
   histo_background[4] = new TH1F("ele_fbrem_background", "ele_fbrem_background", 100, -0.2, 1.);
	
	histo_signal[5] = new TH1F("ele_ep_signal", "ele_ep_signal", 100, 0., 2.5);
   histo_background[5] = new TH1F("ele_ep_background", "ele_ep_background", 100, 0., 2.5);

	histo_signal[6] = new TH1F("ele_eelepout_signal", "ele_eelepout_signal", 100, 0., 3.5);
   histo_background[6] = new TH1F("ele_eelepout_background", "ele_eelepout_background", 100, 0., 3.5);

	histo_signal[7] = new TH1F("ele_pfChargedHadIso_signal", "ele_pfChargedHadIso_signal", 100, 0., 0.02);
   histo_background[7] = new TH1F("ele_pfChargedHadIso_background", "ele_pfChargedHadIso_background", 100, 0., 0.02);

   Init(signal);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;


      histo_signal[0] -> Fill(ele_pt);
      histo_signal[1] -> Fill(scl_eta);
      histo_signal[2] -> Fill(ele_hadronicOverEm);
      histo_signal[3] -> Fill(ele_gsfchi2);
      histo_signal[4] -> Fill(ele_fbrem);
      histo_signal[5] -> Fill(ele_ep);
      histo_signal[6] -> Fill(ele_eelepout);
      histo_signal[7] -> Fill(ele_pfChargedHadIso);
      
   }

   Init(background);

   nentries = fChain->GetEntriesFast();

   nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;


      histo_background[0] -> Fill(ele_pt);
      histo_background[1] -> Fill(scl_eta);
      histo_background[2] -> Fill(ele_hadronicOverEm);
      histo_background[3] -> Fill(ele_gsfchi2);
      histo_background[4] -> Fill(ele_fbrem);
      histo_background[5] -> Fill(ele_ep);
      histo_background[6] -> Fill(ele_eelepout);
      histo_background[7] -> Fill(ele_pfChargedHadIso);

   }

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,1800);
   canvas->Divide(2,4);

   canvas->cd(1);
   histo_signal[0]->SetLineColor(kRed);
   histo_background[0]->SetLineColor(kBlue);
   histo_signal[0]->SetTitle("ele_pt");
   histo_signal[0]->SetStats(0);
   histo_signal[0]->Draw();
   histo_background[0]->Draw("SAME");

   canvas->cd(2);
   histo_signal[1]->SetLineColor(kRed);
   histo_background[1]->SetLineColor(kBlue);
   histo_signal[1]->SetTitle("scl_eta");
   histo_signal[1]->SetStats(0);
   histo_signal[1]->Draw();
   histo_background[1]->Draw("SAME");

   canvas->cd(3);
   histo_signal[2]->SetLineColor(kRed);
   histo_background[2]->SetLineColor(kBlue);
   histo_signal[2]->SetTitle("ele_hadronicOverEm");
   histo_signal[2]->SetStats(0);
   histo_signal[2]->Draw();
   histo_background[2]->Draw("SAME");

   canvas->cd(4);
   histo_signal[3]->SetLineColor(kRed);
   histo_background[3]->SetLineColor(kBlue);
   histo_signal[3]->SetTitle("ele_gsfchi2");
   histo_signal[3]->SetStats(0);
   histo_signal[3]->Draw();
   histo_background[3]->Draw("SAME");

   canvas->cd(5);
   histo_signal[4]->SetLineColor(kRed);
   histo_background[4]->SetLineColor(kBlue);
   histo_signal[4]->SetTitle("ele_fbrem");
   histo_signal[4]->SetStats(0);
   histo_signal[4]->Draw();
   histo_background[4]->Draw("SAME");

   canvas->cd(6);
   histo_signal[5]->SetLineColor(kRed);
   histo_background[5]->SetLineColor(kBlue);
   histo_signal[5]->SetTitle("ele_ep");
   histo_signal[5]->SetStats(0);
   histo_signal[5]->Draw();
   histo_background[5]->Draw("SAME");

   canvas->cd(7);
   histo_signal[6]->SetLineColor(kRed);
   histo_background[6]->SetLineColor(kBlue);
   histo_signal[6]->SetTitle("ele_eelepout");
   histo_signal[6]->SetStats(0);
   histo_signal[6]->Draw();
   histo_background[6]->Draw("SAME");
    
   canvas->cd(8);
   histo_signal[7]->SetLineColor(kRed);
   histo_background[7]->SetLineColor(kBlue);
   histo_signal[7]->SetTitle("ele_pfChargedHadIso");
   histo_signal[7]->SetStats(0);
   histo_signal[7]->Draw();
   histo_background[7]->Draw("SAME");


   canvas-> Print("Distributions.pdf");
   canvas-> Print("Distributions.png");


}

void Analyzer::MVATraining(TString method){

 	TMVA::Tools::Instance();

	TString output("TMVA.root");
	output_file = TFile::Open(output, "RECREATE");

	TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", output_file,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G;D:AnalysisType=Classification");

	TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
	
	dataloader -> AddVariable("ele_pt", "Variable 1", "", 'F');
	dataloader -> AddVariable("scl_eta", "Variable 2", "", 'F');
	dataloader -> AddVariable("ele_fbrem", "Variable 3", "", 'F');
	dataloader -> AddVariable("ele_eelepout", "Variable 4", "", 'F');
	
	dataloader -> AddVariable("ele_hadronicOverEm", "Variable 5", "", 'F');
	dataloader -> AddVariable("ele_gsfchi2", "Variable 6", "", 'F');
	dataloader -> AddVariable("ele_pfChargedHadIso", "Variable 7", "", 'F');
	dataloader -> AddVariable("ele_ep", "Variable 8", "", 'F');

	dataloader -> AddSignalTree(signal, 1.);
	dataloader -> AddBackgroundTree(background, 1.);

	dataloader -> PrepareTrainingAndTestTree("", "", "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V");

	
	factory -> BookMethod(dataloader, TMVA::Types::kBDT, method, "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2");
	
	factory -> TrainAllMethods();
	factory -> TestAllMethods();
	factory -> EvaluateAllMethods();

	cout << "==> Wrote root file: " << output_file -> GetName() << endl;
	cout << "==> TMVAClassification is done!" << endl;   
   output_file -> Close();
}

void Analyzer::PlotMVA(){

   canvas = new TCanvas();
   canvas->SetCanvasSize(900,900);

   file = new TFile("TMVA.root","READ");

   MVA_signal = (TH1D*) file -> Get("dataset/Method_BDT/GBDT/MVA_GBDT_S");
	MVA_background = (TH1D*) file -> Get("dataset/Method_BDT/GBDT/MVA_GBDT_B");
   eff = (TH1F*) file -> Get("dataset/Method_BDT/GBDT/MVA_GBDT_effBvsS");
		
   MVA_background -> SetLineColor(kBlue);
	MVA_signal -> SetLineColor(kRed);
	MVA_signal -> SetStats(0);
   MVA_signal -> SetTitle("MVA Score");

	MVA_signal -> Draw("HIST");
	MVA_background -> Draw("HIST SAME");


   canvas -> Print("MVAScore.pdf");
	cout << "Propuštam " << eff->Interpolate(0.9) * 100 << "% pozadine za 90%signala." << endl;

}
