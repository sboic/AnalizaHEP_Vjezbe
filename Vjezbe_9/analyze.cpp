#include "Analyzer.h"

int main(){

    Analyzer *analyzer = new Analyzer();
    analyzer -> PlotHistogram("/home/public/data/Lifetime/Lifetime.root");
    analyzer -> Likelihood();
    analyzer -> DetermineParameter();
    analyzer -> LogLikelihood();

    delete analyzer;

    return 0;
}