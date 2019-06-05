#include "Jogo.h"
#include <string>

using namespace std;



Jogo::Jogo(unsigned dificuldade_) {
    lvl = 1;
    dificuldade = dificuldade_;
}

void Jogo::criaObstaculo(Engine &engine, float x, float y, unsigned z) {
    //string nomeArquivo = "Sprites/" + arquivosSprites.at("barreira");
    Entidade obstaculo;
    Sprite sprite(engine.matrizObstaculo[lvl - 1], x, y, z);
    obstaculo.sprite = sprite;
    obstaculo.velocidade = vec2<float>(-50, 0);
    obstaculo.addComponente(Componente::OBSTACULO);
    obstaculo.addComponente(Componente::COLISAO);
    engine.addEntidade(obstaculo);
}

void Jogo::criaPlayer(Engine &engine) {
    //string nomeArquivo = "Sprites/" + arquivosSprites.at("player");
    Entidade player;
    Sprite sprite(engine.matrizPlayer[lvl - 1], engine.pXInicio, engine.pYInicio, engine.pZInicio);
    player.sprite = sprite;
    player.addComponente(Componente::PLAYER);
    player.addComponente(Componente::COLISAO);
    player.addComponente(Componente::GRAVIDADE);
    engine.addEntidade(player);
}
