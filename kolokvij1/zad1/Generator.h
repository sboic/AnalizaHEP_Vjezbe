#ifndef Generator_h
#define Generator_h

//potrebne i nepotrebne biblioteke
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

using namespace std;

class Generator{
public:
    Generator(); //konstruktor
    void GeneratePDF(); //funkcija
private:
    TH1F *histogram;
    int i;
    double x, y, f;
    TCanvas *canvas;
};

#endif