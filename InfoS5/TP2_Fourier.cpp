#include <iostream>
#include <cmath>

using namespace std;

const unsigned int N = 1000;


float a0(float tab[]){
    float somme = 0;
    for(int i=0; i<N; i+=1){
        somme += tab[i];
    }
    return somme/N;
}


float ap(float tab[], int p){
    float somme = 0;
    for(int i=0; i<N; i+=1){
        somme += tab[i]+sin(p*)
    }
}




int main(){
    float tab1[N];
    float tab2[N];
    float tab3[N];
    float tab4[N];

    // Remplissage des tableaux
    for(int i=0; i<(N/4); i+=1){
        tab1[i] = sin(i/N);
        tab2[i] = 0;
        tab3[i] = 0.2*(i/N);
        tab4[i] = 0;
    }

    for(int i=(N/4); i<(N/2); i+=1){
        tab1[i] = sin(i/N);
        tab2[i] = 0;
        tab3[i] = -0.2*(i/N)+100;
        tab4[i] = 50;
    }

    for(int i=(N/2); i<((3*N)/4); i+=1){
        tab1[i] = sin(i/N);
        tab2[i] = 50;
        tab3[i] = -0.2*(i/N)+100;
        tab4[i] = 50;
    }

    for(int i=((3*N)/4); i<N; i+=1){
        tab1[i] = sin(i/N);
        tab2[i] = 50;
        tab3[i] = 0.2*(i/N)-200;
        tab4[i] = 50;
    }

    cout << "a01 : " << a0(tab1) << endl;
    cout << "a02 : " << a0(tab2) << endl;
    cout << "a03 : " << a0(tab3) << endl;
    cout << "a04 : " << a0(tab4) << endl;



}



