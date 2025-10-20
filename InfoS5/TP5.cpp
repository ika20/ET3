// Exercice 1
#include <iostream>

using namespace std;


float euroVersDollar(float valeur, float tauxChangeEuro){
    return valeur*tauxChangeEuro;
}


float dollarVersEuro(float valeur, float tauxChangeDollar){
    return valeur*tauxChangeDollar;
}

float saisie(void){
    float valeur;
    cout << "--> Saisissez un montant a convertir : ";
    cin >> valeur;
    return valeur;
}


void saisie2(float* pValeur, float* pTauxChange){
    cout << "Saisissez un montant a convertir : ";
    cin >> *pValeur;
    cout << "Saisissez le taux de change : ";
    cin >> *pTauxChange;
    *pValeur = *pTauxChange**pValeur;
}


int menu(){
    int choix=1;
    do{
        if((choix<1) || (choix>5)){
            cout << "Votre choix doit etre compris entre 1 et 4" << endl << endl;
        }
        cout << " ------------------- MENU -------------------" << endl;
        cout << "| 1 - Saisie d'un montant                    |" << endl;
        cout << "| 2 - Conversion Euro --> Dollar             |" << endl;
        cout << "| 3 - Conversion Dollar --> Euro             |" << endl;
        cout << "| 4 - Saisir une valeur et un taux de change |" << endl;
        cout << "| 5 - Quitter                                |" << endl;
        cout << " --------------------------------------------" << endl;
        cout << ">> Entrez votre choix : ";
        cin >> choix;
    }while((choix<1) || (choix>5));

    return choix;
}

int main()
{
    float tauxChangeEuro = 1.17;
    float tauxChangeDollar = 0.86;
    /*float valeur;
    valeur = saisie();
    cout << endl << "***** Conversion Euro --> Dollar *****" << endl;
    cout << valeur << " euros = " << euroVersDollar(valeur, tauxChangeEuro) << " dollars" << endl;
    cout << endl << "***** Conversion Dollar --> Euro ******" << endl;
    cout << valeur << " dollar = " << dollarVersEuro(valeur, tauxChangeDollar) << " euros" << endl;*/

    int choix = 0;
    float valeur = 0;
    float tauxChange = 0;
    do{
        choix = menu();
        if(choix == 1){
            cout << endl;
            valeur = saisie();
            cout << endl;
        }
        else if(choix == 2){
            cout << endl << "***** Conversion Euro --> Dollar *****" << endl;
            cout << valeur << " euros = " << euroVersDollar(valeur, tauxChangeEuro) << " dollars" << endl << endl;
        }
        else if(choix == 3){
            cout << endl << "***** Conversion Dollar --> Euro ******" << endl;
            cout << valeur << " dollar = " << dollarVersEuro(valeur, tauxChangeDollar) << " euros" << endl << endl;
        }
        else if(choix == 4){
            cout << endl << "***** Conversion avec taux de change *****" << endl;
            saisie2(&valeur, &tauxChange);
            cout << "Resultat : " << valeur << endl;
        }
    }while(choix != 5);

    return 0;
}


// Exercice 2
#include <iostream>

const float PI = 3.14159265;
using namespace std;


float volume(float rayon, float hauteur){
    return 0.333333333*PI*rayon*rayon*hauteur;
}

void saisie(float& rayon, float& hauteur){
    cout << ">> Entrez un rayon : ";
    cin >> rayon;
    cout << ">> Entrez une hauteur : ";
    cin >> hauteur;
}


float moy_volume(float* tab_rayon, float* tab_hauteur, int nombre){
    float sommev = 0;
    int i;
    for(i=0; i<nombre; i+=1){
        sommev += volume(tab_rayon[i], tab_hauteur[i]);
    }
    return sommev/nombre;
}

void saisie_tab(float *tab_rayon, float *tab_hauteur, int nombre){
    int i=0;
    float rayon;
    float hauteur;
    cout << "***** Saisie des valeurs *****" << endl;
    for(int i=0; i<nombre; i+=1){
        cout << "-----------------" << endl;
        cout << "Saisissez le rayon du " << i+1 << "e cone : ";
        cin >> rayon;
        cout << "Saisissez la hauteur du " << i+1 << "e cone : ";
        cin >> hauteur;
        tab_rayon[i] = rayon;
        tab_hauteur[i] = hauteur;
    }
    cout << "-----------------" << endl;
}


int main(){
    //float rayon;
    //float hauteur;
    //saisie(rayon, hauteur);
    float tab_rayon[3];
    float tab_hauteur[3];
    saisie_tab(tab_rayon, tab_hauteur, 3);
    /*for(int i=0; i<3; i+=1){
        cout << ">> Rayon " << i+1 << " : " << tab_rayon[i] << endl;
        cout << ">> Hauteur " << i+1 << " : " << tab_hauteur[i] << endl;
    }*/
    cout << ">> Moyenne : " << moy_volume(tab_rayon, tab_hauteur, 3) << endl;
    return 0;
}



// Exercice 3
#include <iostream>

using namespace std;


unsigned int cherchePosMin(int* tab, unsigned int longueur, unsigned indice_debut){
    int mini=indice_debut;
    int i;
    for(i=indice_debut+1; i<longueur; i+=1){
        if(tab[i]<tab[mini]){
            mini = i;
        }
    }
    return mini;
}

void trieTableau(int* tab, unsigned int longueur){
    int i;
    int temp;
    int mini;
    for(i=0; i<longueur-1; i+=1){
        mini = cherchePosMin(tab, longueur, i);
        temp = tab[i];
        tab[i] = tab[mini];
        tab[mini] = temp;
    }
}


void afficheTab(int* tab, unsigned int longueur){
    cout << "| ";
    for(int i=0; i<longueur; i+=1){
        cout << tab[i] << " | ";
    }
}


int main(){
    int N = 7;
    int tab[N] = {67, 34, 98, 0, 3, 1, 100};
    afficheTab(tab, N);
    trieTableau(tab, N);
    /*for(int i=0; i<N; i+=1){
        cout << i+1 << "e valeur : " << tab[i] << endl;
    }*/
    cout << endl;
    afficheTab(tab, N);

    return 0;
}




// Exercice 4
#include <iostream>

using namespace std;

int longueur(char* texte){
    int L = 0;
    int i = 0;
    while(texte[i] != '\0'){
        i+=1;
        L+=1;
    }
    return L;
}

int compare(char* texte1, char* texte2){
    if(longueur(texte1) != longueur(texte2)){
        return 0;
    }
    else{
        int i=0;
        while(i<longueur(texte1) && texte1[i]==texte2[i]){
            i+=1;
        }
        return i-1==longueur(texte1);
    }
}


void copie(char* texte1, char* texte2){
    if(longueur(texte2)>=longueur(texte1)){
        for(int i=0; i<longueur(texte1); i+=1){
            texte2[i] = texte1[i];
        }
    }
}


int cherche(char x, char* texte){
    int i=0;
    while(i<longueur(texte) && texte[i]!=x){
        i+=1;
    }

    if(i==longueur(texte)){
        return -1;
    }
    else{
        return i;
    }
}


void entier_vers_char(char* chaine, int nombre){
    if(nombre != 0){
        int chiffre;
        int i=0;
        int longueur = 1;
        int nb = nombre;

        while(nb/10 != 0){
            nb=nb/10;
            longueur += 1;
        }

        for(i; i<longueur-1; i+=1){
            chiffre = nombre%10;
            chaine[longueur-1-i] = (char)chiffre+48;
            nombre = nombre/10;
        }

        chaine[0]=(char)nombre+48;
    }
    else{
        chaine[0] = 0;
    }
}


void majuscule(char* chaine){
    for(int i=0; i<longueur(chaine); i+=1){
        if(chaine[i]>=97 && chaine[i]<=122){
            chaine[i]=chaine[i]-('a'-'A');
        }
    }
}


void supprime_car(char* texte, char car){
    /*for(int i=0; i<longueur(texte); i+=1){
        if(texte[i]==car){
            for(int j=i; j<longueur(texte)-1; j+=1){
                texte[j]=texte[j+1];
            }
            texte[longueur(texte)-1]=NULL;
        }
    }*/
    int i=0;
    int j;
    while(i<longueur(texte)){
        if(texte[i]==car){
            for(j=i; j<longueur(texte)-1; j+=1){
                texte[j]=texte[j+1];
            }
            texte[longueur(texte)-1]=NULL;
        }
        else{
            i+=1;
        }
    }
}


int main(){
    //char mot1[10] = "ihwsfwjsq";
    //cout << cherche('a', mot1);
    //char mot2[4] = "txt";
    //copie(mot1, mot2);
    //char mot[10];
    //entier_vers_char(mot, 78190);
    //cout << mot;
    char mot[40] = "aijnfsaajnfaajnfenjka";
    supprime_car(mot, 'a');
    cout << mot;
    return 0;
}

