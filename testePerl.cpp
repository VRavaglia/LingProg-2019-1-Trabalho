#include "PerlWrapper.h"
#include <iostream>
#include <string>
int main ()
{
    PerlWrapper tst("");
    tst.Interpretador();
    cout << tst.FuncaoUm("estou", "testando") << endl;
    cout << tst.FuncaoDois() << endl;
    return 0;
}