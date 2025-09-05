#include <iostream>
#include <cmath>
using namespace std;

// Exercice 1
int main() {
    float a, b, c;
    cout << "Entrez la valeur de a : ";
    cin >> a;
    cout << "Entrez la valeur de b : ";
    cin >> b;
    cout << "Entrez la valeur de c : ";
    cin >> c;
    
    float delta = b*b-4*a*c;
    
    if(delta > 0){
        float x1 = (-b-sqrt(delta))/(2*a);
        float x2 = (-b+sqrt(delta))/(2*a);
        cout << "Les solutions de l'equation sont " << x1 << " et " << x2;
    }
    else if(delta == 0){
        float x0 = (-b)/(2*a);
        cout << "L'unique solution de l'equation est " << x0;
    }
    else{
        cout << "Il n'existe pas de solution reelle a cette equation";
    }
}


// Exercice 2
// 1)
int main() {
    int robinet;
    cout << "Saisissez la valeur de robinet : ";
    cin >> robinet;
    
    switch(robinet){
        case 1:
            cout << "CHAUD";
            break;
        case 2:
            cout << "TIEDE";
            break;
        case 3:
            cout << "FROID";
            break;
        default:
            cout << "Valeur inconnue";
    }
}

// 2)
int main() {
    char couleur;
    cout << "Saisissez la valeur de couleur : ";
    cin >> couleur;
    
    switch(couleur){
        case 'r':
            cout << "ROUGE";
            break;
        case 'R':
            cout << "ROUGE";
            break;
        case 'v':
            cout << "VERT";
            break;
        case 'V':
            cout << "VERT";
            break;
       case 'b':
            cout << "BLEU";
            break;
        case 'B':
            cout << "BLEU";
            break;
        default:
            cout << "NOIR";
    }
}

// 3) Non. Alternative :
int main() {
    float temperature;
    cout << "Saisissez la valeur de temperature : ";
    cin >> temperature;
    
    if(temperature <= 0){
        cout << "GLACE";
    }
    else if((temperature > 0) and (temperature < 100)){
        cout << "EAU LIQUIDE";
    }
    else{
        cout << "VAPEUR";
    }
}
