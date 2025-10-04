// Exercice 1
#include <iostream>

using namespace std;

int main()
{
    short n;
    cout << "Saissisez un nombre de valeurs : ";
    cin >> n;

    int* ptab;
    ptab = NULL;

    ptab = new int[n];
    if(ptab != NULL){
        cout << "**** Remplissage du tableau ****" << endl;
        int val;
        for(int i=0; i<n; i+=1){
            cout << "Saisissez la " << i+1 << "e valeur : ";
            cin >> val;
            ptab[i] = val;
        }
        cout << "**** Affichage des valeurs ****" << endl;
        for(int j=0; j<n; j+=1){
            cout << j+1 << "e valeur : " << ptab[j] << endl;
        }
        delete[] ptab;
    }

    else{
        cout << "Allocation memoire impossible" << endl;
    }

    return 0;
}




// Exercice 2
int main()
{
    int n;

    cout << "Saisissez le nombre de valeurs : ";
    cin >> n;

    float* ptab;
    ptab = NULL;
    ptab = new float[n];
    if(ptab != NULL){
        cout << endl << "**** Saisie des notes ****" << endl;
        float val;
        for(int i=0; i<n; i+=1){
            cout << i+1 << "e note : ";
            cin >> val;
            ptab[i] = val;
        }
        // Calcul de la moyenne
        float somme;
        for(int j=0; j<n; j+=1){
            somme += ptab[j];
        }
        cout << endl << "La moyenne est de " << somme/n;

        delete[] ptab;
    }

    else{
        cout << "Allocation memoire impossible" << endl;
    }

    return 0;
}





// Exercice 3
int main()
{
    int n = 9;
    double tab[] = {-11, 6, 8, -4, 0, 2.5, 98, -1.25, 4.14};
    int nb_p = 0;
    int nb_n = 0;

    for(int i=0; i<n; i+=1){
        if(tab[i] < 0){
            nb_n += 1;
        }
        else{
            nb_p += 1;
        }
    }

    double* ptab_p;
    ptab_p = NULL;
    double* ptab_n;
    ptab_n = NULL;

    ptab_p = new double[nb_p];
    ptab_n = new double[nb_n];

    if((ptab_p != NULL) && (ptab_n != NULL)){
        int i1=0;
        int i2=0;
        for(int i=0; i<n; i+=1){
            if(tab[i]<0){
                ptab_n[i1] = tab[i];
                i1+=1;
            }
            else{
                ptab_p[i2] = tab[i];
                i2 += 1;
            }
        }

        // Affichage des valeurs :

        cout << "Les valeurs negatives sont : ";
        for(int i=0; i<nb_n; i+=1){
            cout << ptab_n[i] << "\t";
        }
        cout << endl << "Les valeurs positives ou nulles sont : ";
        for(int i=0; i<nb_p; i+=1){
            cout << ptab_p[i] << "\t";
        }

        // Suppression des tableaux

        delete[] ptab_n;
        delete[] ptab_p;

    }

    else{
        cout << "Allocation memoire impossible impossible";
    }

    return 0;
}













