#include "Analyzer.h"

int main(void){

    Analyzer *analyzer = new Analyzer();
    analyzer->TestestStatistic(40,32);
    analyzer->PValue();
    
    delete analyzer;
    return 0;
}