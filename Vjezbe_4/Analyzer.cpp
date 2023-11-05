#include "Analyzer.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Analyzer::Analyzer() {
    // Inicijalizacija članova klase ako je potrebno
}

void Analyzer::AnalyzeData(const string& filename) {
  ifstream myReadFile;
  myReadFile.open(filename.c_str());
  string line;

  _skipFirstLine = true;

  if (myReadFile.is_open())
  {
    // Read the file line by line
    while(getline(myReadFile, line))
    {
        stringstream   linestream(line);

        // Since we know that first line of the file only describes data skip reading it into variables
        if (_skipFirstLine)
        {
          _skipFirstLine = false;
          continue;
        }

        // Read output and send it to dedicated variables
        linestream >> counter >> particle_name >> mass >> isBoson >> px >> py >> pz >> p >> E 
                   >> particle_name1 >> mass1 >> isBoson1 >> px1 >> py1 >> pz1 >> p1 >> E1
                   >> particle_name2 >> mass2 >> isBoson2 >> px2 >> py2 >> pz2 >> p2 >> E2;
    }
  }
  myReadFile.close();
}

void Analyzer::ConvertTxtToRootFile(const string& inputFile, const TString& outputFile){
    ifstream myReadFile;
    myReadFile.open(inputFile.c_str());
    _skipFirstLine = true;
     string line;

    //stvaramo root file
    TFile *hfile = TFile::Open(outputFile,"RECREATE");
    //stvaramo tree
    tree = new TTree("Tree","My Higgs boson decay data");

    //izrada branchova
    tree->Branch("Counter",&counter,"&counter/I");
    tree->Branch("particle_name",&particle_name);
    tree->Branch("mass",&mass,"&mass/F");
    tree->Branch("isBoson",&isBoson);
    tree->Branch("px",&px,"&px/F");
    tree->Branch("py",&py,"&py/F");
    tree->Branch("pz",&pz,"&pz/F");
    tree->Branch("p",&p,"&p/F");
    tree->Branch("E",&E,"&E/F");

    tree->Branch("particle_name1", &particle_name1);
    tree->Branch("mass1", &mass1, "mass1/F");
    tree->Branch("isBoson1", &isBoson1);
    tree->Branch("px1", &px1, "px1/F");
    tree->Branch("py1", &py1, "py1/F");
    tree->Branch("pz1", &pz1, "pz1/F");
    tree->Branch("p1", &p1, "p1/F");
    tree->Branch("E1", &E1, "E1/F");

    tree->Branch("particle_name2", &particle_name2);
    tree->Branch("mass2", &mass2, "mass2/F");
    tree->Branch("isBoson2", &isBoson2);
    tree->Branch("px2", &px2, "px2/F");
    tree->Branch("py2", &py2, "py2/F");
    tree->Branch("pz2", &pz2, "pz2/F");
    tree->Branch("p2", &p2, "p2/F");
    tree->Branch("E2", &E2, "E2/F");

     if (myReadFile.is_open())
  {
    while(getline(myReadFile, line))
    {
        stringstream linestream(line);

        // Since we know that first line of the file only describes data skip reading it into variables
        if (_skipFirstLine)
        {
          _skipFirstLine = false;
          continue;
        }

        // Read the file line and store it in dedicated variables
        linestream >> counter >> particle_name >> mass >> isBoson >> px >> py >> pz >> p >> E 
                   >> particle_name1 >> mass1 >> isBoson1 >> px1 >> py1 >> pz1 >> p1 >> E1
                   >> particle_name2 >> mass2 >> isBoson2 >> px2 >> py2 >> pz2 >> p2 >> E2;
        // Fill one instance in the tree with branch values taking their values from addresses of dedicated variables
        tree->Fill();
    }
  }
  // Write our TTree in the currently opened ROOT file
  tree->Write();

  delete hfile;
  myReadFile.close();

}