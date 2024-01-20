#include "Analyzer.h"

int main(void){

    Analyzer *analyzer = new Analyzer();
    analyzer->NullH();
    analyzer->ReconstuctMass("/home/public/data/HiggsSearch/CMSData.root");
    analyzer->PValue();

    delete analyzer;
    return 0;
}