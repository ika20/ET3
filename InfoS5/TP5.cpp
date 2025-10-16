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

