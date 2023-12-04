#include "Generator.h"

//konstruktor
Generator::Generator() {
}

void Generator::GeneratePDF() {

    // Stvaranje histograma sa 48 binova u intervalu od -3 do 9
    histogram = new TH1F("histogram", "Histogram funkcije f(x) = -(x+3)*(x-9)", 48, -3.0, 9.0);
    i=0; //brojac za spremljene vrijednosti
    while (i < 100000) {
        x = -3 + (rand() / (RAND_MAX / 12.0));  // Generiranje slučajne vrijednosti x od -3 do 9
        y = static_cast<double>(rand()) / RAND_MAX; // Generiranje vrijednosti od 0 do 1
        f = - ( x + 3 ) * ( x - 9 ) / 288.0; // racunamo vrijednost funkcije u x
        //288 je normalizacija odnosno integral ove funkcije u danom intervalu

        // Provjera je li točka unutar funkcije f(x) = -(x+3)*(x-9)
        if (y < f) {
            histogram->Fill(x);  // Dodavanje vrijednosti u histogram
            i++;
        }
    }

    // Crtanje histograma
    canvas = new TCanvas("canvas", "canvas", 800, 600); // stvaranje platna
    histogram->Draw(); //crtanje
  
    // bojanje
    histogram->SetFillColor(kGreen);
    histogram->SetFillStyle(3001);
    histogram->SetLineColor(kBlue);
    histogram->SetLineStyle(2);

    // Spremanje histograma u PDF format
    canvas->Print("histogram.pdf");
    canvas->Print("histogram.root");
    canvas->Print("histogram.png");

    delete histogram;
    delete canvas;
}
