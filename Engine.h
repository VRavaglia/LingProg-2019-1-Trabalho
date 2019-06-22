#ifndef TRABALHO_ENGINE_H
#define TRABALHO_ENGINE_H

#include "Utilidades.h"
#include "Desenhador.h"
#include "Entidade.h"
#include "VariaveisConfig.h"
#include <vector>

void pressioneEnter();

/// Defini se o jogo ja acabou
enum Status{rodando, sair};

/// Classe que controla o andamento do jogo
class Engine {
public:
    Engine();
    /// Atualiza valores que mudam com o tempo
    void update(float fps);

    /// Velocidade de reprodução do jogo
    float escalaDeTempo;

    /// Fator que altera a velocidade vertical simulando a gravidade
    float gravidade;

    /// Adiciona ou remove entidades do jogo
    void addEntidade(Entidade *entidade);
    void removeEntidade(Entidade *entidade);

    /// Jogo em si, criado com base nas informacoes do jogar
    void novoJogo(string nomeArquivo, float dificuldade, unsigned pontos);
    void carregaJogo(string nomeArquivo, float dificuldadeP, unsigned pontuacao);

    /// Parametros de inicialização do jogador
    int pXInicio = 0;
    int pYInicio = 30;
    int pZInicio = 1;

    // Inicia os sprites de player e obstaculos
    int inicializaSprites();

    /// Sprites do Player e Obstaculos
    vector<vector<char>> matrizPlayer[3];
    vector<vector<char>> matrizObstaculo[3];

    /// Pontos obtidos por segundo
    unsigned pontosPorSegundo = 10;

    /// Status do jogo
    Status  status;

private:

    /// Cuida da parte visual, desenha na tela
    Desenhador desenhador;

    /// Atualizações relacionadas a física do jogo
    void attFisica(Entidade *entidade, float fps);

    /// Detecta se houve colisao entre duas entidades
    bool colidem(Entidade *a, Entidade *b);

    /// Atualizações relacionadas a parte gráfica
    void attGrafica(Entidade *entidade);

    /// Chamada quando uma entidade se encontra fora da tela
    void emForaDaTela(Entidade *entidade);

    /// Conjunto de sprites que serao escritos na tela a cada instante
    ListaSprites batch;

    /// Frequência de atualização do jogo (tentativa de fps)
    float frequencia;

    /// Lista de entidades ativas no jogo
    std::vector <Entidade *> entidades;

    /// Lista de colisoes
    vector <pair<Entidade *, Entidade*>> colisoes;

    /// Troca de aparencias ao passar de nivel
    void lvlup(int lvl);

    /// Salva a pontuacao final em caso de derrota
    int appendSave(string nomeArquivo, string perfil,  unsigned pontuacao);

    /// Pontuacao que sera salva
    unsigned pontos;

    /// Arquivo contendo as pontuacoes
    string nomeArquivoDados;

};


#endif //TRABALHO_ENGINE_H
