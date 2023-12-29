#include "Analyzer.h"

int main (void){

    Analyzer *analyzer = new Analyzer();
    analyzer->Loop();
    analyzer->MVATraining("GBDT");
    analyzer->PlotMVA();

    delete analyzer;
    return 0;
}