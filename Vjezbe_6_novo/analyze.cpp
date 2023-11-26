#include "Analyzer.h"

int main(void){

    Analyzer *analyzer = new Analyzer();
    analyzer -> PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");

    return 0;
}