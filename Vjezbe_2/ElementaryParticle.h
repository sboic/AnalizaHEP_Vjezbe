#ifndef ELEMENTARYPARTICLE_H
#define ELEMENTARYPARTICLE_H
#include <string>
using namespace std;

class ElementaryParticle {

//Javne varijable
public:
	string particle_name;
	double mass;
	bool Boson;
	double px;
	double py;
	double pz;
	double Energy;


	ElementaryParticle(string a, double b, bool c);
	ElementaryParticle();

	void printInfo();
	void momentum(double x, double y, double z);
};

#endif
