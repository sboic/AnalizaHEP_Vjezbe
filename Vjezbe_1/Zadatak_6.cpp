#include <iostream>
#include <string>

// Stvaranje klase ElementaryParticle

class ElementaryParticle{

// Javne varijable
public:
	std::string particle_name;
	double mass;
	bool Boson;

// Konstruktor klase
	ElementaryParticle(std::string a, double b, bool c) : particle_name(a), mass(b), Boson(c) {}
	ElementaryParticle() : particle_name(""), mass(0.0), Boson(false) {}

// Javna funkcija koja ispisuje podatke o cestici
	void printInfo(){
	std::cout << "Ime cestice je " << particle_name << ", mase " << mass << " i ona " << (Boson ? "je bozon." : "nije bozon.") << std::endl;
	}
};

int main(){

	// A)
	// Kreiranje 2 objekta klase
	ElementaryParticle higgs("Higgsov bozon", 125.1, true);
	ElementaryParticle tq("Top kvark", 173.2, false);
	
	// Ispis podataka
	higgs.printInfo();
	tq.printInfo();

	// B) i C)
	// Pokazivac na Z bozon
	// Potrebno je dodati novi prazni konstruktor i vrijednosti slati odvojeno
	ElementaryParticle* z = new ElementaryParticle();
	z -> particle_name = "Z bozon";
	z -> mass = 91.2;
	z -> Boson = true;
	z -> printInfo();
	delete z;

	// D) Stavit cu W bozon cisto da je razlicito 
	ElementaryParticle* w = new ElementaryParticle("W bozon", 80.4, true);
	w -> printInfo();
	delete w;
	
	// E)
	// Najveca razlika je ta sto mozemo odrediti vremenski interval dok neki objekt postoji i ocistiti memoriju
	// To bi bile prednosti opcije D) odnosno pokazivaca.
	// Za pokazivace memorija se oslobada naredbom delete a za opciju A) zavrsetkom main dijela.
	
	return 0;
}
