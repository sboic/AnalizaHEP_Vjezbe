#include "Analyzer.h"

Analyzer::Analyzer(){

}

int Analyzer::Faktorijela(int x){

    y=1;
    for(int i=1; i<=x ; i++){
        y *= i;
    }
    return y;    
}

void Analyzer::Binominal(int r, float p, int N){

    P = Faktorijela(N)/(Faktorijela(r)*Faktorijela(N-r))*pow(p,r)*pow(1-p,N-r);
    cout << "Vjerojatnost je " << P << endl;
}

void Analyzer::Binom(int r, float p, int N){

    P = TMath::Binomial(N,r) * pow(p,r) * pow(1-p,N-r);
    cout << "Vjerojatnost je " << P << endl;
}

float Analyzer::Binom_CL(int r, float p, int N){
    return  TMath::Binomial(N,r) * pow(p,r) * pow(1-p,N-r);
}

void Analyzer::ClopperPearson(int N){

    canvas = new TCanvas();
    canvas-> SetCanvasSize(900,900);
    histo_up = new TH1F("up","up",10,0,10);
    histo_down = new TH1F("down","down",10,0,10);

    //treba nam 10 događaja
    for (int m=1; m<= 10; m++){
        p_up = 1;
        sum_up=0;
        while(sum_up < (1-CL)/2){
            sum_up=0;
            for(int r=0; r<=m; r++){
                sum_up += Binom_CL(r,p_up,N);
            }
            p_up -= dp;
        }
        p_down=0;
        sum_down=0;
        while(sum_down < (1-CL)/2){
            sum_down=0;
            for(int r=m; r<=N; r++){
                sum_down += Binom_CL(r,p_down,N);
            }
            p_down += dp;
        }

        if(p_down < 0){
            p_down = 0;
        }
        else if(p_up > 1){
            p_up = 1;
        }
        cout << "Interval je: " << p_up << " " << p_down << endl;
        histo_up->SetBinContent(m, p_up);
        histo_down->SetBinContent(m, p_down);
        p1[m-1] = p_down;
        p2[m-1] = p_up;
    }

    histo_up->SetTitle("CL interval");
    histo_down->SetLineColor(kBlack);
    histo_up->SetLineColor(kBlack);
    histo_up -> GetYaxis() -> SetRangeUser(0, 1);
    histo_up->SetStats(0);
    
    histo_up->Draw("");
    histo_down->Draw("SAME");

	histo_up -> GetXaxis() -> SetTitle("m");
	histo_up -> GetYaxis() -> SetTitle("p");

    canvas->Print("CL_interval.png");
    canvas->Print("CL_interval.pdf");
}

void Analyzer::DiceThrowing(){

    srand(static_cast<unsigned>(time(0)));
    int r_in = 0;
    for (int i=0; i < 1000; i++){
        int r = 0;
        for(int j=0; j <10; j++){
            if(rand() / (RAND_MAX / 6) + 1 == 6){
                r++;
            }
        } 
        float p = r/10.;

        if(p > p1[r-1] && p < p2[r+1] ){
            r_in++;
        }
    }
    cout << "Vjerojatnost da se u intervalu nalazi p je " << r_in/1000. << endl;
}