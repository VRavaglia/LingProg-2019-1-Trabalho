#include <iostream>
#include <string>
#include "perlWrapper.h"

using namespace std;

int main(){
    perlWrapper pw;
    pw.interpretador();
    cout << pw.Um(5,6) << endl;
    cout << pw.Dois("teste") << endl;

    return 0;
}