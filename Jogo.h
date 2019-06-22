#include "Utilidades.h"
#include "Engine.h"
#include "Entidade.h"
#include "VariaveisConfig.h"
#include <map>

#ifndef TRABALHO_JOGO_H
#define TRABALHO_JOGO_H


/// Conjunto de metodos que atuam no jogo
class Jogo {
public:

    /// Cria uma instancia com ou sem uma dificuldade definida
    Jogo() = default;
    Jogo(unsigned dificuldade);

    /// Dificuldade do jogo
    unsigned dificuldade = 1;

    /// Cria o obstaculo basico do jogo
    void criaObstaculo(Engine &engine, float x, float y, unsigned z);

    /// Cria instancia do jogador
    void criaPlayer(Engine &engine);

private:
    // Fase do jogo que controla as aparencias
    int lvl;
};


#endif //TRABALHO_JOGO_H
