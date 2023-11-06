#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include <TString.h>

using namespace std;

class Analyzer {
public:

    string particle_name, particle_name1, particle_name2;
    int counter;
    float mass, mass1, mass2;
    bool isBoson, isBoson1, isBoson2;
    float px, px1, px2;
    float py, py1, py2;
    float pz, pz1, pz2;
    float p, p1, p2;
    float E, E1, E2;

    bool _skipFirstLine;

    TTree *tree;

    Analyzer();
    void AnalyzeData(const string& filename);
    void ConvertTxtToRootFile(const string& inputFile,const TString& outputFile);
    

};

#endif
