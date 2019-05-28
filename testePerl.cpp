#include <iostream>
#include <string>
#include "perlWrapper.h"

using namespace std;

int main(){
    perlWrapper pw;
    pw.interpretador();
    cout << pw.salvaPerfil("dadosTeste.txt",  "raposo", 6666, 6.6)  << endl;

    return 0;
}