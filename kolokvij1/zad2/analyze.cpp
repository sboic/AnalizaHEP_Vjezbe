#include "Analyzer.h"

int main(void){

    Analyzer *analyzer = new Analyzer();
    analyzer -> PlotHistogram("/home/public/data/JPsi/TnPpairs_MC.root");

    delete analyzer;
    return 0;
}