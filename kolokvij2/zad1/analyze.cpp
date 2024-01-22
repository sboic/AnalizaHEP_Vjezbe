#include "Analyzer.h"

int main(void){

    Analyzer *analyzer = new Analyzer();
    analyzer->Max_lambda(5, 0.1);

    delete analyzer;
    return 0;
}