#include "ElementaryParticle.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {


    // sjeme randoma
    srand(static_cast<unsigned>(time(0)));
    // otvaranje datoteke za pisanje
    ofstream outputFile("Analysis.txt");
    if (!outputFile.is_open()) {
        cerr << "Nemoguce otvoriti datoteku za pisanje." << endl;
        return 1;
    }
        outputFile << "Br. / Ime cestice / masa / bozon ";
        outputFile <<"/ px / py / pz / p /E ";
        outputFile << "/ part1 / masa / bozon ";
        outputFile <<"/ px1 / py1 / pz1 / p1 / E1";
        outputFile << "/ part2 / masa / bozon ";
        outputFile <<"/ px2 / py2 / pz2 / p2 / E2" << endl;

    for(int i = 1; i <= 10000; i++){

       ElementaryParticle* higgs = new ElementaryParticle("Higgsov bozon", 125.1, true);
        higgs-> setRandMomentum();
        //higgs-> setMomentum(5.0,3.0,1.0);
        //higgs-> printInfo();
        //higgs-> transmomentum();

        // cestice za raspad
        ElementaryParticle* Particle1 = new ElementaryParticle();
        ElementaryParticle* Particle2 = new ElementaryParticle();    
    
        // pohrana u datoteku
        outputFile << i << " ";
        higgs-> writetofile(outputFile);
        higgs-> bosonDecay(*Particle1, *Particle2, outputFile);
        outputFile << endl;


        delete higgs;
        delete Particle1;
        delete Particle2;
    }

    outputFile.close();
    return 0;
}

