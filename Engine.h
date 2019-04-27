#ifndef TRABALHO_ENGINE_H
#define TRABALHO_ENGINE_H

#include "Desenhador.h"
#include "Entidade.h"
#include <vector>

/// Classe que controla o andamento do jogo
class Engine {
public:
    Engine();
    /// Atualiza valores que mudam com o tempo
    void update(float fps);

    /// Velocidade de reprodução do jogo
    float escalaDeTempo;

    void addEntidade(Entidade &entidade);
    void removeEntidade(Entidade &entidade);

    /// Jogo em si
    void novoJogo();

    /// Parametros de inicialização do jogador
    int pXInicio = 0;
    int pYInicio = 30;
    int pZInicio = 1;
private:

    /// Cuida da parte visual, desenha na tela
    Desenhador desenhador;

    /// Atualizações relacionadas a física do jogo
    void attFisica(Entidade &entidade, float fps);

    /// Atualizações relacionadas a parte gráfica
    void attGrafica(Entidade &entidade);

    /// Chamada quando uma entidade se encontra fora da tela
    void emForaDaTela(Entidade &entidade);

    ListaSprites batch;

    /// Ainda sem implementação, status se o jogo deve continuar rodando
    bool rodando;

    /// Frequência de atualização do jogo (tentativa de fps)
    float frequencia;

    /// Lista de entidades ativas no jogo
    std::vector <Entidade> entidades;



};


#endif //TRABALHO_ENGINE_H
