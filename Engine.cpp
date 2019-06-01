#include "Engine.h"
#include "Utilidades.h"
#include "Jogo.h"
#include <vector>
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace std;

const unsigned maxX = 140;
const unsigned maxY = 30;

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
    gravidade = 4.0;

}

void Engine::novoJogo(unsigned dificuldade = 1) {

    Jogo jogo(dificuldade);
    Tela tela(maxX, maxY);

    unsigned periodo = (unsigned int)(10E5/frequencia);
    unsigned ciclos = 1;
    unsigned fps = 0;
    time_t now = time(0);

    float f = 0;
    float t = 0;

    float performace = 1;

    jogo.criaPlayer(*this);

    // Loop do jogo
    while(rodando){
        update(performace);
        desenhador.desenha(batch, tela);
        ciclos++;
        f += escalaDeTempo;
        cout <<"FPS = " << fps << '\n';
        cout <<"Entidades = " << entidades.size() << '\n';
        cout <<"Escala de tempo = " << escalaDeTempo << endl;
        cout << f << endl;
        //usleep(periodo);
        if (time(0) - now >= 1){
            now = time(0);
            fps = ciclos;
            ciclos = 0;
            performace = fps/frequencia;
        }
        if (f >= 50){
            jogo.criaObstaculo(*this, maxX, maxY, 2);
            f = 0;
        }

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

void Engine::attFisica(Entidade &entidade, float performace) {
    entidade.sprite.x += entidade.velocidade.x * escalaDeTempo*(1/frequencia)/performace;
    entidade.sprite.y += entidade.velocidade.y * escalaDeTempo*(1/frequencia)/performace;
    if(entidade.sprite.y < maxY){
        entidade.sprite.y += gravidade * escalaDeTempo*(1/frequencia)/performace;
    }
}

void Engine::attGrafica(Entidade &entidade) {
    // Por enquanto reescrevendo todos os sprites a cada frame
    // posteriormente possivelmente fazer isso apenas em caso de alteração
    batch.addSprite(entidade.sprite);
}

void Engine::emForaDaTela(Entidade &entidade) {
    if (contemComponente(Componente::OBSTACULO, entidade.getComponentes())){
        removeEntidade(entidade);
    }
}

void Engine::update(float performace) {
    batch.limpa();
    for (size_t i = 0; i < entidades.size(); ++i) {
        Entidade *entidade = &entidades[i];
        attFisica(*entidade, performace);
        attGrafica(*entidade);
        if (checaForaDaTela(*entidade, maxX, maxY)){
            entidade->emForaDaTela();
            Engine::emForaDaTela(*entidade);

        }
    }

}

int Engine::inicializaSprites(string nomeArquivoP, string nomeArquivoO) {

    return 0;
}
