#include "ElementaryParticle.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;


// Konstruktori
ElementaryParticle::ElementaryParticle(string a, double b, bool c) : particle_name(a), mass(b), Boson(c) {}
ElementaryParticle::ElementaryParticle() : particle_name(""), mass(0.0), Boson(false), px(0.0), py(0.0), pz(0.0), momentum(0.0), Energy(0.0) {}

// Funkcije

void ElementaryParticle::printInfo() {
	cout << "Ime cestice je " << particle_name << ", mase " << mass << " i ona " << (Boson ? "je bozon." : "nije bozon.") << endl;
	cout << "Komponente momenta:" << "px = " << px << ", py = " << py << ", pz = " << pz << endl;
	cout << "Ukupni moment je " << momentum << endl;
	cout << "Energija je " << Energy << endl;
}

void ElementaryParticle::setMomentum(double x, double y, double z) {
	px = x;
	py = y;
	pz = z;

	momentum = pow(x,2) + pow(y,2) + pow(z,2);
	Energy = sqrt(momentum + pow(mass,2));
}

void ElementaryParticle::setRandMomentum(){
	px = -100 + (rand() / (RAND_MAX / 200.0)); // nasumicna vrijednost između -100 i 100 GeV
    py = -100 + (rand() / (RAND_MAX / 200.0));
	pz = -100 + (rand() / (RAND_MAX / 200.0));

	momentum = pow(px,2) + pow(py,2) + pow(pz,2);
	Energy = sqrt(momentum + pow(mass,2));
}

void ElementaryParticle::transmomentum(){

	double tmoment = sqrt( pow(px,2) + pow(py,2));
	cout << "Transverzalni moment je " << tmoment << endl;
}

void ElementaryParticle::bosonDecay(ElementaryParticle particle1, ElementaryParticle particle2, ofstream& outputFile){
	if (Boson == false){
		cout << "Raspad nije moguc jer cestica nije bozon." << endl;
	}

// raspad
	double random = static_cast<double>(rand()) / RAND_MAX; //random od 0 do 1
	if (random < 0.214){ // u 21.4% slucaja raspad ide preko W
		particle1.particle_name = "W bozon";
		particle2.particle_name = "W bozon";
		particle1.mass = 80.4;
		particle2.mass = 80.4;
		particle1.Boson = true;
		particle2.Boson = true;
	}
	else if(random < 0.278){ // u 6.4 % preko tau leptona
		particle1.particle_name = "Tau lepton";
		particle2.particle_name = "Tau lepton";
		particle1.mass = 1.777;
		particle2.mass = 1.777;
		particle1.Boson = false;
		particle2.Boson = false;
	} 
	else if(random < 0.304){ // u 2.6% slucaja ide preko Z bozona
		particle1.particle_name = "Z bozon";
		particle2.particle_name = "Z bozon";
		particle1.mass = 91.2;
		particle2.mass = 91.2;
		particle1.Boson = true;
		particle2.Boson = true;
	}
	else{ // sve ostalo preko b kvarkova
		particle1.particle_name = "B kvark";
		particle2.particle_name = "B kvark";
		particle1.mass = 4.18;
		particle2.mass = 4.18;
		particle1.Boson = false;
		particle2.Boson = false;
	}

// raspodjela kolicine gibanja
	double px1 = static_cast<double>(rand()) / RAND_MAX * px;
	double py1 = static_cast<double>(rand()) / RAND_MAX * py;
	double pz1 = static_cast<double>(rand()) / RAND_MAX * pz;

	double px2 = px - px1;
	double py2 = py - py1;
	double pz2 = pz - pz1;

// četvervektor momenta novih cestica
	particle1.setMomentum(px1, py1, pz1);
	particle2.setMomentum(px2, py2, pz2);
	cout << "Cestica se raspala na " << particle1.particle_name << " i " << particle2.particle_name << "." << endl;

	//particle1.printInfo();
	//particle2.printInfo();

	particle1.writetofile(outputFile);
	particle2.writetofile(outputFile);
}

void ElementaryParticle::writetofile(ofstream& outputFile){
	outputFile << particle_name << " " << mass << " " << (Boson ? "Da" : "Ne") << " ";
	outputFile << px << " " << py << " " << pz << " " << momentum << " " << Energy << " ";
}
