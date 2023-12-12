#include "Analyzer.h"

Analyzer::Analyzer(){

    F = { 1., 2., 3., 4., 5.};
    a = { 9.8, 21.2, 34.5, 39.9, 48.5};
    err = { 1.0, 1.9, 3.1, 3.9, 5.1};
}

void Analyzer::Fit(){

    canvas = new TCanvas();
    canvas->SetCanvasSize(900,900);

    graph = new TGraphErrors(F.size(), F.data(), a.data(), nullptr, err.data());

    fit = new TF1("fit","x/[0]",0,50);
    fit->SetParameter(0,0.1);
    fit->SetParName(0,"Masa");
        
    graph->Fit("fit");

    graph -> SetTitle ("Masa kuglice; Sila; Akceleracija");

    graph->Draw("AP");
    fit->Draw("SAME");

    canvas->Draw();
   
    canvas->Print("Masakuglice.pdf");

    mass = fit->GetParameter(0);
    mass_err = fit->GetParError(0);
    cout << "1.Zad Masa kuglice: " << mass << " ± " << mass_err << endl;

    delete canvas;
    delete graph;
    delete fit;
}
void Analyzer::LeastSquares(){

    xy = 0;
    x2 = 0;
    y2 = 0;

    for( int i = 0; i < 5; i++){
        xy += a[i] * F[i];
        x2 += F[i] * F[i];
        y2 += a[i] * a[i];
    }
  
    theta = xy/x2;
    theta_err = sqrt((y2/x2 - theta*theta) / 5);
    mass = 1/theta;
    mass_err = theta_err / (theta*theta);

    cout << "2.Zad Masa kuglice: " << mass << " ± " << mass_err << endl;
}
void Analyzer::FromGraph(){

    canvas = new TCanvas();
    canvas->SetCanvasSize(900,900);

    graph = new TGraphErrors(F.size(), F.data(), a.data(), nullptr, err.data());
   
    fit = new TF1("fit","([0]-[1]*x)*([0]-[1]*x)/([2]*[2]) + ([3]-[4]*x)*([3]-[4]*x)/([5]*[5]) + ([6]-[7]*x)*([6]-[7]*x)/([8]*[8]) + ([9]-[10]*x)*([9]-[10]*x)/([11]*[11]) +([12]-[13]*x)*([12]-[13]*x)/([14]*[14])",8,12);
    fit->SetParameter(0,a[0]);
    fit->SetParameter(1,F[0]);
    fit->SetParameter(2,err[0]);
    fit->SetParameter(3,a[1]);
    fit->SetParameter(4,F[1]);
    fit->SetParameter(5,err[1]);
    fit->SetParameter(6,a[2]);
    fit->SetParameter(7,F[2]);
    fit->SetParameter(8,err[2]);
    fit->SetParameter(9,a[3]);
    fit->SetParameter(10,F[3]);
    fit->SetParameter(11,err[3]);
    fit->SetParameter(12,a[4]);
    fit->SetParameter(13,F[4]);
    fit->SetParameter(14,err[4]);

    theta = fit->GetMinimumX();
    theta_err_down = theta - fit->GetX( fit->GetMinimum(8,12) + 1,8,theta);
    theta_err_up = fit->GetX( fit->GetMinimum(8,12) + 1,theta,12) - theta;
    
    mass = 1/theta;
    mass_err_up = theta_err_up / (theta*theta);
    mass_err_down = theta_err_down / (theta*theta);

    fit->SetTitle("LeastSquares");
    fit->Draw();
    canvas->Draw();

    min = new TLine(theta,0,theta,fit->GetMinimum());
    min->SetLineStyle(kDashed);
    min->Draw();

    err_up = new TLine(theta_err_up + theta,0,theta_err_up + theta,fit->GetMinimum()+1);
    err_up->SetLineStyle(kDashed);
    err_up->Draw();

    err_down = new TLine(theta - theta_err_down,0,theta - theta_err_down,fit->GetMinimum()+1);
    err_down->SetLineStyle(kDashed);
    err_down->Draw();
   
    canvas->Print("LeastSquares.pdf");

    cout << "3.Zad Masa kuglice: " << mass << " - " << mass_err_down << " + " << mass_err_up << endl;

    delete canvas;
    delete graph;
    delete fit;
}