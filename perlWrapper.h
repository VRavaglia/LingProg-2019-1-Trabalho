#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class perlWrapper{
public:
    perlWrapper();
    ~perlWrapper();

    void interpretador();

    vector<pair<string, unsigned>> listaPontuacoesMaiores(string nomeArquivo, unsigned max);
    int salvaPerfil(string nomeArquivo, string nome, unsigned pontos, float dificuldade);
    int leJogo(string nome, float dificuldade, string nomeArquivo, unsigned &pontuacao);
    int listaPontuacoesJogador(string nome, int restricao, string nomeArquivo, vector<unsigned> &listaPontos);
    vector<string> configuraAparencia(string nomeArquivoPlayer, string nomeArquivoObstculo);

    // Versao no perl:
    //my @pontuacoes = GerenciamentoDeDados::listaPontuacoesMaiores($arquivo, $n);
    //my $status = GerenciamentoDeDados::salvaPerfil($arquivo, $nome, $pontos, $dificuldade);
    //($pontuacao, $status) = GerenciamentoDeDados::leJogoEmAndamento($nome, $dificuldade, $arquivo);
    //(@pontuacao, $status) = GerenciamentoDeDados::listaPontuacoesDeJogador($nome, $restricao, $arquivo);
    //@aparencias = GerenciamentoDeDados::configuraAparencia($arquivoPlayer, $arquivoObstaculo);

private:
    PerlInterpreter *my_perl;
    char *my_argv[2];
};