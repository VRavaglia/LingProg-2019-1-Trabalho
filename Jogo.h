#include "Engine.h"
#include "Entidade.h"
#include <map>

#ifndef TRABALHO_JOGO_H
#define TRABALHO_JOGO_H


class Jogo {
public:
    Jogo();
    Jogo(unsigned dificuldade);

    /// Dificuldade do jogo
    unsigned dificuldade;

    /// Cria o obstaculo basico do jogo
    void criaObstaculo(Engine &engine, float x, float y, unsigned z);

private:
    // Lista contendo os respectivos arquivos para cada sprite
    const std::map<std::string, std::string> arquivosSprites ={
            {"barreira", "barreira.txt"},
    };
};


#endif //TRABALHO_JOGO_H
