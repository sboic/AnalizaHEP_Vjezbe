#include "Analyzer.h"

int main() {

    Analyzer* analyzer = new Analyzer();
    
    //analyzer -> AnalyzeData("Analysis.txt");
    analyzer-> ConvertTxtToRootFile("Analysis.txt", "Analysis.root");

    delete analyzer;
    return 0;
}
