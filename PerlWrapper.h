#ifndef TRABALHO_PERLWRAPPER_H
#define TRABALHO_PERLWRAPPER_H

#include <iostream>
#include <string>
#include <EXTERN.h>
#include <perl.h>

using namespace std;

class PerlWrapper {
public:
    PerlWrapper(string script);
    ~PerlWrapper();
    void Interpretador ();
    int FuncaoUm (string, string);
    string FuncaoDois ();
private:
    PerlInterpreter *my_perl;
    char *my_argv[2];

};


#endif
