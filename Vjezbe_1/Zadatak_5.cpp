#include <iostream>

// Funkcija za računanje kuba realnog broja

double _my_cube(double realni_broj){

	return realni_broj*realni_broj*realni_broj; 
}

int main(){
	double realni_broj, rezultat;
	
	// Unos realnog broja
	std::cout << "Unesite realni broj za kubiranje: ";
	std::cin >> realni_broj;

	// Pozivanje funkcije za kubiranje
	rezultat = _my_cube(realni_broj);
	std::cout << "Kub unesenog broja " << realni_broj << " je " << rezultat << std::endl;

	return 0;

}
