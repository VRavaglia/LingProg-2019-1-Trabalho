#include "Engine.h"
#include "Entidade.h"
#include <map>

#ifndef TRABALHO_JOGO_H
#define TRABALHO_JOGO_H



class Jogo {
public:
    Jogo() = default;
    Jogo(unsigned dificuldade);

    /// Dificuldade do jogo
    unsigned dificuldade = 1;

    /// Cria o obstaculo basico do jogo
    void criaObstaculo(Engine &engine, float x, float y, unsigned z);

    /// Cria instancia do jogador
    void criaPlayer(Engine &engine);

private:
    // Fase do jogo
    int lvl;
};


#endif //TRABALHO_JOGO_H
