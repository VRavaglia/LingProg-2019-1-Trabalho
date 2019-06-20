#include "perlWrapper.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

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
    char _MYARGV_PERL_MODULE_NAME[] = "gerenciamento.pl"; //retira warnings
    char _MYARGV_NOTHING_NAME[] = ""; //retira warnings
    char *my_argv[] = {static_cast<char*> (_MYARGV_NOTHING_NAME), static_cast<char*> (_MYARGV_PERL_MODULE_NAME)};
    perl_parse(my_perl, 0, 2, my_argv, (char **)NULL);
    perl_run(my_perl);
}

//my @pontuacoes = GerenciamentoDeDados::listaPontuacoesMaiores($arquivo, $n);
int perlWrapper::listaPontuacoesMaiores(string nomeArquivo, unsigned max, vector<pair<string, unsigned>> &pontuacoes) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);

    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));
    XPUSHs(sv_2mortal(newSViv(max)));

    PUTBACK;
    int count = call_pv("listaPontuacoesMaiores", G_ARRAY);
    SPAGAIN;

    pontuacoes.reserve(count/2);
    unsigned pontos;

    for (int i = 1; i < count + 1; ++i) {
        if(i % 2 == 0){
            pair<string, unsigned > par(POPp, pontos);
            pontuacoes.push_back(par);
        }
        else{
            pontos = POPu;
        }
    }

    PUTBACK;
    FREETMPS;
    LEAVE;

    return 0;
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
    XPUSHs(sv_2mortal(newSViv(dificuldade)));
    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));
    PUTBACK;
    call_pv("leJogoEmAndamento", G_ARRAY);
    SPAGAIN;

    string status = POPp;
    pontuacao = POPi;

    PUTBACK;
    FREETMPS;
    LEAVE;

    if(status != "ok"){
        return -1;
    }
    return 0;
}

//(@pontuacao, $status) = GerenciamentoDeDados::listaPontuacoesDeJogador($nome, $restricao, $arquivo);
int perlWrapper::listaPontuacoesJogador(string nome, int restricao, string nomeArquivo, vector<unsigned> &listaPontos) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(nome.c_str(),nome.length())));
    XPUSHs(sv_2mortal(newSViv(restricao)));
    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));
    PUTBACK;
    int count = call_pv("listaPontuacoesDeJogador", G_ARRAY);
    SPAGAIN;


    for (int i = 1; i < count; ++i) {
        listaPontos.push_back(POPi);
    }
    int status = POPi;

    PUTBACK;
    FREETMPS;
    LEAVE;

    return status;
}

//@aparencias = GerenciamentoDeDados::configuraAparencia($arquivoPlayer, $arquivoObstaculo);
vector <vector<string>> perlWrapper::configuraAparencia(string nomeArquivoPlayer, string nomeArquivoObstculo) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(nomeArquivoPlayer.c_str(),nomeArquivoPlayer.length())));
    XPUSHs(sv_2mortal(newSVpv(nomeArquivoObstculo.c_str(),nomeArquivoObstculo.length())));
    PUTBACK;
    int count = call_pv("configuraAparencia", G_ARRAY);
    SPAGAIN;

    vector<vector<string>> sprites;
    vector<string> sprite;
    for (int i = 0; i < count; ++i) {
        string linha = POPp;
        if(linha == "#"){
            std::reverse(sprite.begin(), sprite.end());
            sprites.push_back(sprite);
            sprite.clear();
        } else{
            sprite.push_back(linha);
        }
    }




    PUTBACK;
    FREETMPS;
    LEAVE;

    for(auto &spriteNovo : sprites){
        for(auto it = spriteNovo.begin(); it != spriteNovo.end() - 1; it++){
            it->pop_back();
        }
    }



    std::reverse(sprites.begin(), sprites.end());
    return sprites;
}

//@todas = GerenciamentoDeDados::vetorPalavras($nomeArquivo);
vector<tuple<string, unsigned, float>> perlWrapper::vetorPalavras(string nomeArquivo) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);

    XPUSHs(sv_2mortal(newSVpv(nomeArquivo.c_str(),nomeArquivo.length())));

    PUTBACK;
    int count = call_pv("vetorPalavras", G_ARRAY);
    SPAGAIN;

    vector<tuple<string, unsigned, float>> pontuacoes;
    pontuacoes.reserve(count/3);
    string nome;
    unsigned pontos;
    float dificuldade;

    for (int i = 1; i < count + 1; ++i) {
        switch (i % 3){
            case 2:
                pontos = POPu;
                break;
            case 1:
                dificuldade = POPn;
                break;
            case 0:
                nome = POPp;
                tuple <string, unsigned, float> tupla = {nome, pontos, dificuldade};
                pontuacoes.emplace_back(tupla);
                break;
        }
    }

    PUTBACK;
    FREETMPS;
    LEAVE;

    return pontuacoes;
}
