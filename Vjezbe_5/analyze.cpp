#include <Analyzer.h>

int main(){

    Analyzer *analyzer = new Analyzer();
    analyzer->Loop();
    analyzer->PlotHistrogram();

    return 0;
}