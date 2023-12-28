#include "Analyzer.h"

int main (void){

    Analyzer *analyzer = new Analyzer();
    //analyzer -> Binominal(5,0.4,10);
    analyzer -> Binom(5,0.4,10);
    analyzer -> ClopperPearson(10);
    analyzer -> DiceThrowing();

    delete analyzer;

    return 0;
}