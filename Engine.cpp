#include "Engine.h"
#include "Utilidades.h"
#include <vector>
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace std;

Engine::Engine() {
    rodando = true;
    frequencia = 10;
    escalaDeTempo = 1.0;

}

void Engine::novoJogo() {

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
    cubo.velocidade = vec2<float>(50,0);
    Engine::addEntidade(cubo);

    Tela tela;

    unsigned periodo = (unsigned int)(10E5/frequencia);
    unsigned ciclos = 1;
    unsigned fps = 0;
    time_t now = time(0);

    // Loop do jogo
    while(rodando){
        update();
        desenhador.desenha(batch, tela);
        ciclos++;
        usleep(periodo);
        if (time(0) - now >= 1){
            now = time(0);
            fps = ciclos;
            ciclos = 0;
        }
        if (entidades[0].sprite.x > 80){
            entidades[0].sprite.x = 0;
        }
        cout <<"FPS = " << fps << endl;
        cout << "spd (" << entidades[0].velocidade.x << "," << entidades[0].velocidade.y << ") "<< " pos(" << entidades[0].sprite.x << "," << entidades[0].sprite.y << ") ";
    }
}

void Engine::addEntidade(Entidade &entidade) {
    entidades.push_back(entidade);
}

void Engine::attFisica(Entidade &entidade) {
    entidade.sprite.x += entidade.velocidade.x * escalaDeTempo*(1/frequencia);
    entidade.sprite.y += entidade.velocidade.y * escalaDeTempo*(1/frequencia);
}

void Engine::attGrafica(Entidade &entidade) {
    // Por enquanto reescrevendo todos os sprites a cada frame
    // posteriormente possivelmente fazer isso apenas em caso de alteração
    batch.addSprite(entidade.sprite);
}

void Engine::update() {
    batch.limpa();
    for (size_t i = 0; i < entidades.size(); ++i) {
        attFisica(entidades[i]);
        attGrafica(entidades[i]);
    }

}
