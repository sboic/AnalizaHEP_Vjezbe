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
#include <TRandom3.h>

using namespace std;

class Analyzer{
public:
    Analyzer();
    void    TestStatistics();
    void    Pvalue();

private:
    TCanvas *canvas;
    TH1F *histo, *experiment;
    TF1 *theory;
    float chi2,mH;
    TRandom3 *r3;
    float sigma;
    TGraph *graph;
    float  a_SM = -1., b_SM = -190.,c_SM = 0.02;
    float p_value;

};
#endif