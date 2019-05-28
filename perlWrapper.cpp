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

//my @pontuacoes = GerenciamentoDeDados::listaPontuacoesMaiores($arquivo, $n);
vector<pair<string, unsigned>> perlWrapper::listaPontuacoesMaiores(string nomeArquivo, unsigned max) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);

    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));
    XPUSHs(sv_2mortal(newSViv(max)));

    PUTBACK;
    call_pv("listaPontuacoesMaiores", G_ARRAY);
    SPAGAIN;

    vector<pair<string, unsigned>> resultado;
    while(auto temp = POP){
        resultado.push_back(temp, temp);
    }

    PUTBACK;
    FREETMPS;
    LEAVE;

    return resultado;
}

//my $status = GerenciamentoDeDados::salvaPerfil($arquivo, $nome, $pontos, $dificuldade);
int perlWrapper::salvaPerfil(string nomeArquivo, string nome, unsigned pontos, float dificuldade) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));
    XPUSHs(sv_2mortal(newSVpv(nome.c_str(),nome.length())));
    XPUSHs(sv_2mortal(newSViv(pontos)));
    XPUSHs(sv_2mortal(newSViv(dificuldade)));
    PUTBACK;
    call_pv("salvaPerfil", G_SCALAR);
    SPAGAIN;

    int resultado = POPi;
    PUTBACK;
    FREETMPS;
    LEAVE;

    return resultado;
}

//($pontuacao, $status) = GerenciamentoDeDados::leJogoEmAndamento($nome, $dificuldade, $arquivo);
int perlWrapper::leJogo(string nome, float dificuldade, string nomeArquivo, unsigned &pontuacao) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(nome.c_str(),nome.length())));
    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));
    PUTBACK;
    int count = call_pv("leJogoEmAndamento", G_ARRAY);
    SPAGAIN;

    pontuacao = POPi;
    int status = POPi;
    cout << pontuacao << endl;
    cout << status << endl;

    PUTBACK;
    FREETMPS;
    LEAVE;

    return status;
}

//(@pontuacao, $status) = GerenciamentoDeDados::listaPontuacoesDeJogador($nome, $restricao, $arquivo);
int perlWrapper::listaPontuacoesJogador(string nome, int restricao, string nomeArquivo, vector<unsigned> &listaPontos) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(nome.c_str(),nome.length())));
    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));
    PUTBACK;
    call_pv("listaPontuacoesDeJogador", G_ARRAY);
    SPAGAIN;


    int status = POPi;
    while(int pontos = POPi){
        listaPontos.push_back(pontos);
    }
    PUTBACK;
    FREETMPS;
    LEAVE;

    return status;
}

//@aparencias = GerenciamentoDeDados::configuraAparencia($arquivoPlayer, $arquivoObstaculo);
vector<string> perlWrapper::configuraAparencia(string nomeArquivoPlayer, string nomeArquivoObstculo) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(nomeArquivoPlayer.c_str(),nomeArquivoPlayer.length())));
    XPUSHs(sv_2mortal(newSVpv(nomeArquivoObstculo.c_str(),nomeArquivoObstculo.length())));
    PUTBACK;
    call_pv("configuraAparencia", G_ARRAY);
    SPAGAIN;

    vector<string> sprites;
    string sprite;
    while(true){
        sprite = POPp;
        if(!sprite.empty()){
            sprites.push_back(sprite);
        } else{
            break;
        }}
    PUTBACK;
    FREETMPS;
    LEAVE;

    return sprites;
}
