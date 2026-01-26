#include <iostream>
#include "Pilechar.h"

using namespace std;


int main(){
//    Pilechar pile(5);
//    for(int i=0; i<10; i+=1){
//        pile.empiler('a'+i);
//    }
//    pile.afficher();
//    pile.depiler();
//    cout << endl;
//    pile.afficher();
//
//    Pilechar pile1(0);
//    cout << pile1.depiler();

    unsigned int n;
    char elem;
    Pilechar pile(n);
    for(int i=0; i<n; i+=1){
        cin >> elem;
        pile.empiler(elem);
    }
    return 0;
}
















