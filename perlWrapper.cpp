#include "perlWrapper.h"
#include <string>
#include <vector>
#include <map>

perlWrapper::perlWrapper(){
    PERL_SYS_INIT3(NULL, NULL, NULL);
    my_perl = perl_alloc();
    perl_construct(my_perl);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

perlWrapper::~perlWrapper(){
    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();
}

void perlWrapper::interpretador(){
    my_argv [0] = "";
    my_argv [1] = "showtime.pl";
    perl_parse(my_perl, 0, 2, my_argv, (char **)NULL);
    perl_run(my_perl);
}

int perlWrapper::Um(int a, int b){
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSViv(a)));
    XPUSHs(sv_2mortal(newSViv(b)));
    PUTBACK;
    call_pv("um", G_SCALAR);
    SPAGAIN;

    int resultado = POPi;
    PUTBACK;
    FREETMPS;
    LEAVE;

    return resultado;
}

string perlWrapper::Dois(string palavra){
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(palavra.c_str(),palavra.length())));
    PUTBACK;
    call_pv("dois", G_SCALAR);
    SPAGAIN;

    string resultado = POPp;
    PUTBACK;
    FREETMPS;
    LEAVE;

    return resultado;
}

//my @pontuacoes = GerenciamentoDeDados::listaPontuacoesMaiores($arquivo, $n);
vector<map<string, unsigned>> &perlWrapper::listaPontuacoesMaiores(string nomeArquivo, unsigned max) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);

    XPUSHs(sv_2mortal(newSViv(a)));
    XPUSHs(sv_2mortal(newSViv(b)));

    PUTBACK;
    call_pv("listaPontuacoesMaiores", G_SCALAR);
    SPAGAIN;



    int resultado = POPi;
    PUTBACK;
    FREETMPS;
    LEAVE;

    return resultado;
}

int perlWrapper::salvaPerfil(string nomeArquivo, string nome, unsigned pontos, float dificuldade) {
    return 0;
}

int perlWrapper::leJogo(string nome, float dificuldade, string nomeArquivo, unsigned &pontuacao) {
    return 0;
}

int perlWrapper::listaPontuacoesJogador(string nome, int restricao, string nomeArquivo, vector<unsigned> &listaPontos) {
    return 0;
}

vector<vector<string>> &perlWrapper::configuraAparencia(string nomeArquivoPlayer, string nomeArquivoObstculo) {
    return <#initializer#>;
}
