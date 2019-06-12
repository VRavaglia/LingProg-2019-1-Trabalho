#ifndef TRABALHO_ENTIDADE_H
#define TRABALHO_ENTIDADE_H

#include "Utilidades.h"
#include "Desenhador.h"
#include "VariaveisConfig.h"

/// Lista de características especiais que classificam a entidade
enum Componente {OBSTACULO = 2, COLISAO = 3, PLAYER = 5, GRAVIDADE = 7};

/// Checa se um componente pertence a lista
bool contemComponente(Componente componente, unsigned componentes);

class Entidade {
public:
    Entidade();
    /// Entidade do jogo que tem aparencia e velocidade
    /// Aparencia
    Sprite sprite;

    /// Velocidade em que se move na tela
    vec2<float> velocidade;

    /// Chamada quando a entidade se encontra fora da tela
    virtual void emForaDaTela();

    /// Chamada quando colide
    virtual void emColisao();

    void addComponente(Componente componente);
    void removeComponente(Componente componente);
    unsigned getComponentes();

private:
    /// Soma de todos os componentes
    unsigned componentes = 1;

};

class Player: public Entidade{
    virtual void emColisao();
};


#endif
