#include "Engine.h"
#include "Utilidades.h"
#include <vector>
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace std;

Engine::Engine() {
    rodando = true;
    frequencia = 15;
    escalaDeTempo = 1.0;

}

void Engine::jogo() {

    // Simples sprites para teste
    vector <vector <char>> triangle {{' ',' ','0'},
                                     {' ','0','0'},
                                     {'0','*','0'},
                                     {' ','0','0'},
                                     {' ',' ','0'}};

    vector <vector <char>> box {{'&','&','&'},
                                {'&','$','&'},
                                {'&','&','&'}};



    Sprite sprite1(box, 10, 10, 2);
    Sprite sprite2(triangle, 12, 10, 1);

    Entidade cubo;
    cubo.sprite = sprite1;
    cubo.velocidade = vec2<float>(1,0);

    Tela tela;
    ListaSprites batch;
    batch.addSprite(cubo.sprite);
    batch.addSprite(sprite2);

    unsigned periodo = (unsigned int)(10E5/frequencia);
    unsigned ciclos = 1;
    unsigned fps = 0;
    time_t now = time(0);

    // Loop do jogo
    while(rodando){
        desenhador.desenha(batch, tela);
        ciclos++;
        usleep(periodo);
        if (time(0) - now >= 1){
            now = time(0);
            fps = ciclos;
            ciclos = 0;
        }
        cout <<"FPS = " << fps;
    }
}

void Engine::addEntidade(Entidade &entidade) {
    entidades.push_back(entidade);
}

void Engine::update(unsigned ciclos) {
    for (Entidade entidade : entidades) {
        entidade.sprite.x = entidade.sprite.x + (entidade.velocidade.x * escalaDeTempo*(1/frequencia));
        entidade.sprite.y = entidade.sprite.y + (entidade.velocidade.y * escalaDeTempo*(1/frequencia));

    }

}
