#include <stddef.h>
#include <string>
#include "PerlWrapper.h"

using namespace std;


PerlWrapper::PerlWrapper(string script = "test"){
    int dummy_argc = 0;
    char*** dummy_env = 0;
    char string[] = {};
    char* dummy_argv[] = {string, &script[0]};
    PERL_SYS_INIT3(&dummy_argc, dummy_env, dummy_env);
    my_perl = perl_alloc();
    perl_construct(my_perl);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

PerlWrapper::~PerlWrapper(){
    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();
}

void PerlWrapper::Interpretador (){
    char _MYARGV_PERL_MODULE_NAME[] = "WrapperHelper.pl";
    char _MYARGV_NOTHING_NAME[] = "";
    char *my_argv[] = {static_cast<char*> (_MYARGV_NOTHING_NAME), static_cast<char*>(_MYARGV_PERL_MODULE_NAME)};
    perl_parse (my_perl, 0, 2, my_argv, NULL);
    perl_run(my_perl);
}

int
PerlWrapper::FuncaoUm(string coisa, string qualquer)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
/*OBS1*/
    int resultado;
/*OBS2*/
    XPUSHs (sv_2mortal (newSVpv(coisa.c_str(), coisa.length())));
    XPUSHs (sv_2mortal (newSVpv(qualquer .c_str(), qualquer.length())));
    PUTBACK;
/*OBS3*/
    call_pv("test", G_SCALAR);
    SPAGAIN;
/*POPi para retornar int, POPp para retornar string*/
/*OBS4*/
    resultado = POPi;
/*OBS5*/
    PUTBACK;

    FREETMPS;
    LEAVE;
    return resultado;
}

string
PerlWrapper::FuncaoDois () {
    string resultado;
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
/*OBS1*/
    PUTBACK;
    call_pv("funcaoPerl2", G_SCALAR);
    SPAGAIN;
/*OBS2*/
    resultado = POPp;
    PUTBACK;
    FREETMPS;
    LEAVE;
    return resultado;
}