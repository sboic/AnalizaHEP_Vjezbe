#include "Generator.h"

int main (void){

    //sjeme za random
    srand(static_cast<unsigned>(time(0)));

    Generator *generator = new Generator();
    generator->GeneratePDF();

    delete generator;
    return 0;
}
