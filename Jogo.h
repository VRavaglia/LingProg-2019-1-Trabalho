#include "Engine.h"
#include "Entidade.h"

#ifndef TRABALHO_JOGO_H
#define TRABALHO_JOGO_H


class Jogo {
public:
    Jogo();
    Jogo(unsigned dificuldade);
    unsigned dificuldade;
    void criaObstaculo(Engine &engine, float x, float y, unsigned z);
};


#endif //TRABALHO_JOGO_H
