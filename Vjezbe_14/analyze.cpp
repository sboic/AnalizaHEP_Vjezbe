#include "Analyzer.h"

int main(void){

    Analyzer *analyzer = new Analyzer();
    analyzer->TestStatistics();
    analyzer->Pvalue();
    delete analyzer;


    return 0;
}