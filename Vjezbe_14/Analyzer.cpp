#include "Analyzer.h"

Analyzer::Analyzer(){

}

void Analyzer::TestStatistics(){

    canvas = new TCanvas();
    canvas->SetCanvasSize(900,900);
    r3 = new TRandom3();

    histo = new TH1F("TestStatistics","TestStatistics",200,0.,50.);
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
			histo->Fill(chi2);
		}
    }
	cout << "Parametar " << theory->GetParameter(0) << endl;

    gStyle->SetOptStat(0);
	histo->Scale(1./histo->Integral());
    histo->Draw("HIST");
    canvas->Print("TestStatistics.pdf");
    delete theory;
	delete experiment;
}
void Analyzer::Pvalue(){
    
    canvas = new TCanvas();
	canvas->SetCanvasSize(900,900);
	r3 = new TRandom3();
	graph = new TGraph();

    sigma = 0.0236;
    mH = 0;
	
	for (int i=10; i<290; i+=5){
	
		theory = new TF1("Theory","[0] * TMath::Exp(-x/[1])",0.,300.);
		theory->SetParameters(300.,100.);
		
		TString temp = "experiment2" + to_string(i);
        experiment = new TH1F(temp,"experiment2",100,0.,300.);	
	
		mH = i/1.0;
		
		for(int j=0; j<10000;j++) {
            if(r3->Rndm() > a_SM*TMath::Power((mH + b_SM),2) + c_SM ) experiment->Fill(r3->Exp(100)); // Generate SM process for probability given by theory
            else experiment->Fill(r3->Gaus(mH,sigma*mH)); // otherwise generate Higgs boson according to theoretical PDF
        }

		theory->FixParameter(1, 100.);
        experiment->Fit(theory,"Q","",mH-10,mH+10);
        chi2=theory->GetChisquare();
		p_value=histo->Integral(histo->FindBin(chi2),histo->GetNbinsX())/histo->Integral();
		graph->SetPoint(i/5,mH,p_value);
	}

	cout << "P_value " << p_value << endl;

	graph->Draw();	
	canvas->Print("P-value.pdf");
}