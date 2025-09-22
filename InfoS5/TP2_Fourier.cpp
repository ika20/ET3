#include <iostream>
#include <cmath>

using namespace std;

const unsigned int N = 100;
const float PI = 3.14159265359;


float a0(double tab[]){
    float somme = 0;
    for(unsigned int i=0; i<N; i+=1){
        somme += tab[i];
    }
    return somme/N;
}


double ap(double tab[], int p){
    double somme = 0;
    for(unsigned int i=0; i<N; i+=1){
        somme += ((double)tab[i])*cos(((float)p*i*2*PI)/N);
    }
    return 2*(somme/N);
}

double bp(double tab[], int p){
    double somme = 0;
    for(unsigned int i=0; i<N; i+=1){
        somme += ((double)tab[i])*sin(((float)p*i*2*PI)/N);
    }
    return 2*(somme/N);
}




int main(){
    double tab1[N];
    double tab2[N];
    double tab3[N];
    double tab4[N];

    // Remplissage des tableaux
    for(unsigned int i=0; i<(N/4); i+=1){
        tab1[i] = sin(2*PI*((float)i/N));
        tab2[i] = 0;
        tab3[i] = 200*((float)i/N);
        tab4[i] = 0;
    }

    for(unsigned int i=(N/4); i<(N/2); i+=1){
        tab1[i] = sin(2*PI*((float)i/N));
        tab2[i] = 0;
        tab3[i] = -200*((float)i/N)+100;
        tab4[i] = 50;
    }

    for(unsigned int i=(N/2); i<((3*N)/4); i+=1){
        tab1[i] = sin(2*PI*((float)i/N));
        tab2[i] = 50;
        tab3[i] = -200*((float)i/N)+100;
        tab4[i] = 50;
    }

    for(unsigned int i=((3*N)/4); i<N; i+=1){
        tab1[i] = sin(2*PI*((float)i/N));
        tab2[i] = 50;
        tab3[i] = 200*((float)i/N)-200;
        tab4[i] = 50;
    }

    // Calcul de a0 pour chaque fonction
    cout << "a01 : " << a0(tab1) << endl;
    cout << "a02 : " << a0(tab2) << endl;
    cout << "a03 : " << a0(tab3) << endl;
    cout << "a04 : " << a0(tab4) << endl;

    // Calcul de ap pour chaque fonction
    int p = 1;
    cout << "ap1 : " << ap(tab1, p) << endl;
    cout << "ap2 : " << ap(tab2, p) << endl;
    cout << "ap3 : " << ap(tab3, p) << endl;
    cout << "ap4 : " << ap(tab4, p) << endl;

    cout << "bp1 : " << bp(tab1, p) << endl;





}


