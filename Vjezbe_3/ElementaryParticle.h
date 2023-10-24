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
	double momentum;
	double Energy;


	ElementaryParticle(string a, double b, bool c);
	ElementaryParticle();

	void printInfo();
	void setMomentum(double x, double y, double z);
	void transmomentum();
	void bosonDecay(ElementaryParticle p1,ElementaryParticle p2, ofstream& outputFile);
	void setRandMomentum();
	void writetofile(ofstream& outputFile);
};

#endif

