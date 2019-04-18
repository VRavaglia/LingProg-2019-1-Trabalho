#include "Engine.h"
#include "Utilidades.h"
#include <vector>
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace std;

const unsigned maxX = 80;
const unsigned maxY = 16;

bool checaForaDaTela(Entidade &entidade, unsigned maxX, unsigned maxY){
    if (entidade.sprite.x > maxX){
        return true;
    }
    if (entidade.sprite.y > maxY){
        return true;
    }
    if (entidade.sprite.x - entidade.sprite.L() < 0){
        return true;
    }
    if (entidade.sprite.y - entidade.sprite.H() < 0){
        return true;
    }

    return false;
}

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
    cubo.velocidade = vec2<float>(50,5);
    Engine::addEntidade(cubo);

    Tela tela(maxX, maxY);

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
        if (entidades[0].sprite.y > 16){
            entidades[0].sprite.y = 0;
        }
        cout <<"FPS = " << fps << endl;
        cout << "spd (" << entidades[0].velocidade.x << "," << entidades[0].velocidade.y << ") "<< " pos(" << entidades[0].sprite.x << "," << entidades[0].sprite.y << ") ";
    }
}

void Engine::addEntidade(Entidade &entidade) {
    entidades.push_back(entidade);
}

void Engine::removeEntidade(Entidade &entidade) {
    int i = -1;
    // Necessita de otimização
    for (int j = 0; j < entidades.size(); ++j) {
        if (&entidades[j] == &entidade){
            i = j;
        }
    }
    if (i >= 0){
        // Por enquanto o próprio coletor de lixo lida com a entidade removida, possivelmente tratar de maneira melhor
        entidades.erase(entidades.begin() + i);
    }
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

void Engine::emForaDaTela(Entidade &entidade) {
    if (contemComponente(Componente::OBSTACULO, entidade.getComponentes())){
        removeEntidade();
    }
}

void Engine::update() {
    batch.limpa();
    for (size_t i = 0; i < entidades.size(); ++i) {
        Entidade *entidade = &entidades[i];
        attFisica(*entidade);
        attGrafica(*entidade);
        if (checaForaDaTela(*entidade, maxX, maxY)){
            entidade->emForaDaTela();
            Engine::emForaDaTela(*entidade);

        }
    }

}
