#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <iostream>
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <THStack.h>
#include <TGraph.h>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <TApplication.h>
#include <string>
#include <TF1.h>

using namespace std;

class Analyzer{

public:
    Analyzer();
    void Binominal(int r,float p,int N);
    int Faktorijela(int x);
    void Binom(int r, float p, int N);
    void ClopperPearson(int N);
    float Binom_CL(int r, float p, int N);
    void DiceThrowing();

private:
    int y;
    float P;
    float CL = 0.6827; //ili 1 sigma
    float sum_up, sum_down, p_up, p_down, dp = 0.001;
    TCanvas *canvas;
    TH1F *histo_up, *histo_down;
    float p1[10], p2[10];
};

#endif