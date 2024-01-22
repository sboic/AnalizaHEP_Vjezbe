#include "Analyzer.h"

Analyzer::Analyzer(){

}

void Analyzer::Max_lambda(int N, float eps){
    lambda = 0.;
    P = 0.;
    while(P < eps){
        P=0.;
        for(int r = N; r <= N*N*N ; r++){ // N*N*N mi imitira beskonačnost
            P += TMath::Poisson(r,lambda);
        }
        lambda+= 0.01;
    }

 cout << "Maksimalna lambda je " << lambda - 0.01 << endl;
 cout << "N = " << N << endl;
 cout << "Eps = " << eps << endl;
}
