#include "Analyzer.h"

int main(){

    Analyzer *analyzer = new Analyzer();
    analyzer -> TestStatistic(164.7,7.1);
    analyzer -> HypothesisTesting("France",164.7,7.1);
    //analyzer -> HypothesisTesting("Italy",166.1,6.5);
    analyzer-> HypothesisTesting("Spain",168.,7.);
    analyzer -> HypothesisTesting("Netherlands",170.3,7.5);

    delete analyzer;

    return 0;
}