#include "ElementaryParticle.h"
#include <iostream>
using namespace std;


// Konstruktori
ElementaryParticle::ElementaryParticle(string a, double b, bool c) : particle_name(a), mass(b), Boson(c) {}
ElementaryParticle::ElementaryParticle() : particle_name(""), mass(0.0), Boson(false) {}

// Funkcija

void ElementaryParticle::printInfo() {
	cout << "Ime cestice je " << particle_name << ", mase " << mass << " i ona " << (Boson ? "je bozon." : "nije bozon.") << endl;
	cout << "Promjena" << endl;
}

