#include "Analyzer.h"

int main (void){

    Analyzer *analyzer = new Analyzer();
    analyzer -> Fit();
    analyzer -> LeastSquares();
    analyzer -> FromGraph();

    delete analyzer;

    return 0;
}