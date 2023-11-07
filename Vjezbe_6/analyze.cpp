// C++
#include <iostream>
#include <fstream>

#include <Analyzer.h>

int main(){

    Analyzer *analyzer = new Analyzer();
    analyzer->Loop();
    analyzer->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
    analyzer->PlotMass();

    delete analyzer;
    return 0;
}