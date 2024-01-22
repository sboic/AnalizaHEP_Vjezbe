
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
#include <TH2.h>
#include <TGraph.h>
#include <TF1.h>
#include <TLine.h>
#include <TGraphErrors.h>
#include <TRandom3.h>


using namespace std;

class Analyzer{

public:
    Analyzer();
    virtual void Max_lambda(int N, float eps);

private:
    float P,lambda;
};

#endif