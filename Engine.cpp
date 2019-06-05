#include "Engine.h"
#include "Utilidades.h"
#include "Jogo.h"
#include <vector>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include "perlWrapper.h"

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
    if (entidade.sprite.x + entidade.sprite.L() < 0){
        return true;
    }
    if (entidade.sprite.y + entidade.sprite.H() < 0){
        return true;
    }

    return false;
}

Engine::Engine() {
    rodando = true;
    frequencia = 10;
    escalaDeTempo = 1.0;
    gravidade = 5.0;

}

void Engine::novoJogo(unsigned dificuldade = 1, unsigned pontos = 0) {

    Jogo jogo(dificuldade);
    Tela tela(maxX, maxY, true);

    unsigned periodo = (unsigned int)(10E5/frequencia);
    unsigned ciclos = 1;
    float fps = 0;
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
        pontos += (int)(escalaDeTempo*(1/frequencia)/performace*dificuldade*pontosPorSegundo);
        cout << "Pontuacao: " << pontos << '\n';
        cout << "Dificuldade: " << dificuldade << '\n';
        cout <<"FPS = " << fps << '\n';
        cout <<"Entidades = " << entidades.size() << '\n';
        cout <<"Escala de tempo = " << escalaDeTempo << '\n';
        cout << f << endl;
        cout << "Pos Player: (" << entidades.at(0).sprite.x << "," << entidades.at(0).sprite.y << ")" << '\n';
        usleep(periodo);
        if (time(0) - now >= 1){
            now = time(0);
            fps = ciclos;
            ciclos = 0;
            performace = fps/frequencia;
        }
        if (f >= 30){
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
    if(contemComponente(Componente::GRAVIDADE, entidade.getComponentes()) && entidade.sprite.y < (maxY)){
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

int Engine::inicializaSprites() {
    perlWrapper pw;
    pw.interpretador();

    cout << "Insira o nome do arquivo com a aparencia do Jogador: " << endl;
    string aparenciaP;
    cin >> aparenciaP;

    cout << "Insira o nome do arquivo com a aparencia dos Obstaculos: " << endl;
    string aparenciaO;
    cin >> aparenciaO;

    if(aparenciaP == "1"){
        aparenciaP = "playerTeste.txt";
    }

    if(aparenciaO == "1"){
        aparenciaO = "obstaculoTeste.txt";
    }

    vector<vector<string>> aparencias = pw.configuraAparencia(aparenciaP,aparenciaO);


    for (int i = 0; i < 6; ++i) {
        if(i < 3){
            matrizPlayer[i] = Desenhador::listaStringParaMatrizChar(aparencias.at(i));
        }
        else{
            matrizObstaculo[i-3] = Desenhador::listaStringParaMatrizChar(aparencias.at(i));
        }
    }
    return 0;
}

void Engine::carregaJogo(string nome, float dificuldadeP, unsigned pontuacao) {

}
