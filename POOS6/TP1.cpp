// main Exercice 1
#include <iostream>
#include <cmath>

#include "Complexe.h"

float const PI = 3.14159265;

using namespace std;

Complexe somme(Complexe z1, Complexe z2){
    Complexe z(z1.re()+z2.re(), z1.im()+z2.im());
    return z;
}

Complexe difference(Complexe z1, Complexe z2){
    Complexe z(z1.re()-z2.re(), z1.im()-z2.im());
    return z;
}

Complexe conversion(float r, float theta){
    Complexe z(round(1000*r*cos(theta))/1000.0, round(1000*r*sin(theta))/1000.0);
    return z;
}

Complexe produit(Complexe z1, Complexe z2){
    float mod = z1.module()*z2.module();
    float th = z1.argument()+z2.argument();
    Complexe z = conversion(mod, th);
    return z;
}



int main(){
    Complexe x(0.707, 0.707);
    Complexe y(0.866, 0.5);
    Complexe z = produit(x, y);
    //z=somme(x, y);
    z.affiche_exp();
//    cout << z.module();

    //Complexe x(1, 2);
    //Complexe y(2, 3);
    //cout << "Partie reelle : " << x.partie_reelle() << endl;
    //cout << "Partie imaginaire : " << x.partie_imaginaire();
    //x.affiche();
    //Complexe z;
    //z=somme(x, y);
//    Complexe z = somme(x, y);
//    z.affiche();

//    x.affiche();
//    cout << endl << "partie reelle : " << x.re() << endl;
//    cout << "partie imaginaire : " << x.im() << endl;
//    cout << "module : " << x.module() << endl;
//    cout << "arg : " << x.argument() << endl;
//    x.affiche_exp();

    //Complexe z = conversion(1, 3.1415/2);
    //z.affiche();

//    x.affiche_exp();
//    cout << endl;
//    y.affiche_exp();

    return 0;
}
















