// Exercice 1
int main() {
    int a=12;
    cout << "Variable = " << a << endl;

    return 0;
}

// Exercice 2
int main() {
    char nom;
    char prenom;
    int age;
    cout << "Saisissez la premiere lettre de votre nom : ";
    cin >> nom;
    cout << "Saisissez la premiere lettre de votre prenom : ";
    cin >> prenom;
    cout << "Saisissez votre age : ";
    cin >> age;
    cout << "Bonjour " << prenom << "." << nom << "., vous avez " << age << " ans.";
    return 0;
}

// Exercice 3
const double PI = 3.14159265;
int main() {
    int rayon;
    cout << "Saisissez le rayon du disque : ";
    cin >> rayon;
    cout << "Le perimetre de ce disque est " << 2*PI*rayon;
    return 0;
}

// Exercice 4
// f1 = 3
// f2 = 3.3333

// explicites : (float)i1

int main() {
 int i1, i2, i3;
 float f1, f2;
 i1 = 10;
 i2 = 3;
 f1 = i1 / i2;
 f2 = (float)i1 / i2;
 i3 = i1 % i2;
 cout << "f1 = i1 / i2 = " << f1 << endl;
 cout << "f1 = (float)i1 / i2 " << f2 << endl;
 cout << "i3 = modulo(i1 / i2) = " << i3 << endl;
 return 0;
}

// Exercice 5
int main() {
    cout << "Le nombre d'octets pour :" << endl <<
    "- un char : " << sizeof(char) << endl <<
    "- un int : " << sizeof(int) << endl <<
    "- un float : " << sizeof(float) << endl <<
    "- un double : " << sizeof(double);
    
    return 0;
}
