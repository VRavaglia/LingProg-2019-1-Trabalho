#include "Jogo.h"
#include <string>

using namespace std;






Jogo::Jogo() {
    dificuldade = 1;

}

Jogo::Jogo(unsigned dificuldade_) {
    dificuldade = dificuldade_;
}

void Jogo::criaObstaculo(Engine &engine, float x, float y, unsigned z) {
    vector <vector <char>> box {{'&','$','&','&','$','&','&'},
                                {'&','$','&','&','$','&','&'},
                                {'&','$','&','&','$','&','&'}};
    string nomeArquivo = "Sprites/" + arquivosSprites.at("barreira");
    Entidade obstaculo;
    Sprite sprite(nomeArquivo, x, y, z);
    obstaculo.sprite = sprite;
    obstaculo.velocidade = vec2<float>(-50, 0);
    obstaculo.addComponente(Componente::OBSTACULO);
    obstaculo.addComponente(Componente::COLISAO);
    engine.addEntidade(obstaculo);
}