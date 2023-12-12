#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TGraph.h>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <TApplication.h>
#include <string>
#include <TF1.h>
#include <TGraphErrors.h>
#include <vector>
#include <TLine.h>

using namespace std;

class Analyzer{

public:
    Analyzer();
    void Fit();
    void LeastSquares();
    void FromGraph();
private:
    vector<double> F;
    vector<double> a;
    vector<double> err;
    TCanvas *canvas;
    TGraphErrors *graph;
    TF1 *fit;
    double mass,mass_err,mass_err_up,mass_err_down;
    double theta,theta_err,theta_err_up, theta_err_down;
    double xy,x2,y2;
    TLine *err_up, *err_down, *min;
};

#endif