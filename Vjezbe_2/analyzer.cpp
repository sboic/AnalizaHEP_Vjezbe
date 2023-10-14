#include "ElementaryParticle.h"
#include <iostream>
using namespace std;

int main() {
    ElementaryParticle higgs("Higgsov bozon", 125.1, true);
    ElementaryParticle tq("Top kvark", 173.2, false);

    higgs.printInfo();
    tq.printInfo();

    ElementaryParticle* z = new ElementaryParticle();
    z-> particle_name = "Z bozon";
    z-> mass = 91.2;
    z-> Boson = true;
    z-> printInfo();
    delete z;

    ElementaryParticle* w = new ElementaryParticle("W bozon", 80.4, true);
    w-> printInfo();
    delete w;

    return 0;
}

