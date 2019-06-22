#ifndef PERL_WRAPPER_H
#define PERL_WRAPPER_H

#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include "VariaveisConfig.h"

using namespace std;

/// Classe que cuida da interacao entre Perl e C++
class perlWrapper{
public:
    perlWrapper();
    ~perlWrapper();

    void interpretador();

    int listaPontuacoesMaiores(string nomeArquivo, unsigned max, vector<pair<string, unsigned>> &pontuacoes);
    int salvaPerfil(string nomeArquivo, string nome, unsigned pontos, float dificuldade);
    int leJogo(string nome, float dificuldade, string nomeArquivo, unsigned &pontuacao);
    int listaPontuacoesJogador(string nome, int restricao, string nomeArquivo, vector<unsigned> &listaPontos);
    vector <vector<string>> configuraAparencia(string nomeArquivoPlayer, string nomeArquivoObstculo);
    vector <tuple<string, unsigned, float>> vetorPalavras(string nomeArquivo);

    // Versao no perl:
    //my @pontuacoes = GerenciamentoDeDados::listaPontuacoesMaiores($arquivo, $n);
    //my $status = GerenciamentoDeDados::salvaPerfil($arquivo, $nome, $pontos, $dificuldade);
    //($pontuacao, $status) = GerenciamentoDeDados::leJogoEmAndamento($nome, $dificuldade, $arquivo);
    //(@pontuacao, $status) = GerenciamentoDeDados::listaPontuacoesDeJogador($nome, $restricao, $arquivo);
    //@aparencias = GerenciamentoDeDados::configuraAparencia($arquivoPlayer, $arquivoObstaculo);
    //@todas = GerenciamentoDeDados::vetorPalavras($nomeArquivo);

private:
    PerlInterpreter *my_perl;
    char *my_argv[2];
};

#endif