//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov  6 10:35:35 2023 by ROOT version 6.24/08
// from TTree Tree/My Higgs boson decay data
// found on file: Analysis.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include<iostream>
#include<cmath>
#include<TLegend.h>
#include<TLorentzVector.h>

// Header file for the classes stored in the TTree if any.
using namespace std;

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Counter;
   string          *particle_name;
   Float_t         mass;
   Int_t           isBoson;
   Float_t         px;
   Float_t         py;
   Float_t         pz;
   Float_t         p;
   Float_t         E;
   string          *particle_name1;
   Float_t         mass1;
   Int_t           isBoson1;
   Float_t         px1;
   Float_t         py1;
   Float_t         pz1;
   Float_t         p1;
   Float_t         E1;
   string          *particle_name2;
   Float_t         mass2;
   Int_t           isBoson2;
   Float_t         px2;
   Float_t         py2;
   Float_t         pz2;
   Float_t         p2;
   Float_t         E2;

   // List of branches
   TBranch        *b_counter;   //!
   TBranch        *b_particle_name;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_isBoson;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_p;   //!
   TBranch        *b_E;   //!
   TBranch        *b_particle_name1;   //!
   TBranch        *b_mass1;   //!
   TBranch        *b_isBoson1;   //!
   TBranch        *b_px1;   //!
   TBranch        *b_py1;   //!
   TBranch        *b_pz1;   //!
   TBranch        *b_p1;   //!
   TBranch        *b_E1;   //!
   TBranch        *b_particle_name2;   //!
   TBranch        *b_mass2;   //!
   TBranch        *b_isBoson2;   //!
   TBranch        *b_px2;   //!
   TBranch        *b_py2;   //!
   TBranch        *b_pz2;   //!
   TBranch        *b_p2;   //!
   TBranch        *b_E2;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   void PlotHistrogram();
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Analysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Analysis.root");
      }
      f->GetObject("Tree",tree);

   }
   Init(tree);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   particle_name = 0;
   particle_name1 = 0;
   particle_name2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Counter", &Counter, &b_counter);
   fChain->SetBranchAddress("particle_name", &particle_name, &b_particle_name);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("isBoson", &isBoson, &b_isBoson);
   fChain->SetBranchAddress("px", &px, &b_px);
   fChain->SetBranchAddress("py", &py, &b_py);
   fChain->SetBranchAddress("pz", &pz, &b_pz);
   fChain->SetBranchAddress("p", &p, &b_p);
   fChain->SetBranchAddress("E", &E, &b_E);
   fChain->SetBranchAddress("particle_name1", &particle_name1, &b_particle_name1);
   fChain->SetBranchAddress("mass1", &mass1, &b_mass1);
   fChain->SetBranchAddress("isBoson1", &isBoson1, &b_isBoson1);
   fChain->SetBranchAddress("px1", &px1, &b_px1);
   fChain->SetBranchAddress("py1", &py1, &b_py1);
   fChain->SetBranchAddress("pz1", &pz1, &b_pz1);
   fChain->SetBranchAddress("p1", &p1, &b_p1);
   fChain->SetBranchAddress("E1", &E1, &b_E1);
   fChain->SetBranchAddress("particle_name2", &particle_name2, &b_particle_name2);
   fChain->SetBranchAddress("mass2", &mass2, &b_mass2);
   fChain->SetBranchAddress("isBoson2", &isBoson2, &b_isBoson2);
   fChain->SetBranchAddress("px2", &px2, &b_px2);
   fChain->SetBranchAddress("py2", &py2, &b_py2);
   fChain->SetBranchAddress("pz2", &pz2, &b_pz2);
   fChain->SetBranchAddress("p2", &p2, &b_p2);
   fChain->SetBranchAddress("E2", &E2, &b_E2);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyzer_cxx
