// Exercice 1
#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int tab[5] = {1, 2, 4, 7, 9};
    for(int i=0; i<5; i+=1){
        cout << "Element n°" << i+1 << " : " << tab[i] << endl;
    }
    cout << "Saisissez les nouvelles valeurs : " << endl;
    int entier;
    for(int i=0; i<5; i+=1){
        cout << "Valeur n°" << i+1 << " : ";
        cin >> entier;
        tab[i] = entier;
    }

    return 0;
}



// Exercice 2
int main(){
    int tab[10] = {4, 7, 8, 2, 2, 1, 5, 3, 8, 6};
    int val = 8;

    // Version 1
    int i = 0;
    while(tab[i]!=val && i<10){
        i+=1;
    }
    if(i>=10){
        cout << val << " n'a pas ete trouve";
    }
    else{
        cout << val << " a ete trouve";
    }

    // Version 2
    bool trouve = false;
    for(int j=0; j<10; j+=1){
        if(tab[j]==val){
            cout << "La valeur " << val << " est presente a la position " << j << endl;
            trouve = true;
        }
    }
    if(!trouve){
        cout << val << " n'a pas ete trouve";
    }

    // Version 3
    int occurences = 0;
    for(int k=0; k<10; k+=1){
        if(tab[k]==val){
            occurences += 1;
        }
    }
    cout << "La valeur " << val << " a ete trouvee " << occurences << " fois";

    return 0;
}


// Exercice 3
int main(){
    float notes[50];
    int nb_notes=0;
    do{
        cout << "Entrez le nombre de notes que vous souhaitez saisir (entre 1 et 50) : ";
        cin >> nb_notes;
    }while(nb_notes>50);
    float note;
    cout << "**** Saisie des notes ****" << endl;
    for(int i=0; i<nb_notes; i+=1){
        cout << "Saisisez la " << i+1 << "e note : ";
        cin >> note;
        notes[i] = note;
    }
    float somme;
    for(int j=0; j<nb_notes; j+=1){
        somme += notes[j];
    }
    float moyenne = somme/nb_notes;
    cout << "La moyenne est de " << moyenne;

    return 0;
}


// Exercice 4
int tab[15] = {5, 2, 11, 13, 1, 7, 5, 15, 5, 8, 7, 10, 6, 12, 7};
    int max = tab[0];
    int pos = 0;
    for(int i=1; i<15; i+=1){
        if(tab[i] > max){
            max = tab[i];
            pos = i;
        }
    }
    cout << "Le maximum est de " << max << " atteint a la position " << pos;
}


// Exercice 5
int main(){
    int n=4;
    char text[n] = {'T', 'e', 's', 't', '\0', 'a'};
    // Methode 1
    cout << "Methode 1 : " << endl;
    cout << text << endl;
    // Methode 2
    cout << "Methode 2 : " << endl;
    int i=0;
    while(text[i]!='\0' && i<n){
        cout << text[i];
        i+=1;
    }
}


// Exercice 6
int main(){
    int n=100;
    int m=13;
    char tab[n] = {'Q', 'u', 'e', 'l', 'q', 'u', 'e', 's', ' ', 'm', 'o', 't', 's', '\0'};
    // Version basique
    int nb_espaces = 0;
    for(int i=0; i<m; i+=1){
        if(tab[i]==' '){
            nb_espaces += 1;
        }
    }
    cout << "Ce texte contient " << nb_espaces+1 << " mots";

    // Amelioration
    int nb_espaces = 0;
    int nb_ponctu;
    for(int i=0; i<m; i+=1){
        if(tab[i]==' '){
            nb_espaces += 1;
        }
        else if(tab[i] == ',' || tab[i] == ';'){
            nb_ponctu += 1;
        }
    }
    cout << "Ce texte contient " << nb_espaces+1-nb_ponctu << " mots";
}
