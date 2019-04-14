#ifndef TRABALHO_ENTIDADE_H
#define TRABALHO_ENTIDADE_H

#include "Desenhador.h"
#include "Utilidades.h"

class Entidade {
public:
    Entidade();
    /// Entidade do jogo que tem aparencia e velocidade
    /// Aparencia
    Sprite sprite;

    /// Velocidade em que se move na tela
    vec2<float> velocidade;
};


#endif
