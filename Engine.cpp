#include "Engine.h"
#include "Jogo.h"
#include <vector>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "perlWrapper.h"
#include "InputManager.h"



using namespace std;

const unsigned maxX = maxXTela;
const unsigned maxY = maxYTela;

int tecla;


void pressioneEnter() {
    std::cout << "Aperte {ENTER} para continuar..." << flush;
    InputManager::getkeyPause();
    while(InputManager::getkeyPause() != 10){ // 10 = ENTER
    }

}

bool checaForaDaTela(Entidade *entidade, unsigned maxX, unsigned maxY){
    if (entidade->sprite.x > maxX){
        return true;
    }
    if (entidade->sprite.y > maxY){
        return true;
    }
    if (entidade->sprite.x + entidade->sprite.L() < 0){
        return true;
    }
    if (entidade->sprite.y + entidade->sprite.H() < 0){
        return true;
    }

    return false;
}

Engine::Engine() {
    frequencia = 10;
    escalaDeTempo = 1.0;
    gravidade = 20.0;

}

void Engine::novoJogo(string nomeArquivo, float dificuldade = 1, unsigned pontos_ = 0) {
    srand((int)time(0));

    cout << "Insira o nome do perfil que sera salvo: " << endl;
    string perfil;
    cin >> perfil;

    pontos = pontos_;

    perlWrapper pw;
    pw.interpretador();

    Jogo jogo(dificuldade);
    Tela tela(maxX, maxY, true);

    status = Status::rodando;

    unsigned periodo = (unsigned int)(10E5/frequencia);
    unsigned ciclos = 1;
    float fps = 0;
    time_t now = time(0);

    float f = 0;
    int limF = (rand() % 20) + 21;
    float l = 0;

    float performace = 1;

    bool redimensionar = true;

    jogo.criaPlayer(*this);

    int teclaPrint = -2;

    // Loop do jogo
    while(status != Status::sair){
        update(performace);
        desenhador.desenha(batch, tela);
        ciclos++;
        f += escalaDeTempo;
        l += escalaDeTempo;
        pontos += (int)(escalaDeTempo*(1/frequencia)/performace*dificuldade*pontosPorSegundo);



        if(emDebug) {
            cout << "Pontuacao: " << pontos << '\n';
            cout << "Dificuldade: " << dificuldade << '\n';
            cout << "FPS = " << fps << '\n';
            cout << "Entidades = " << entidades.size() << '\n';
            cout << "Escala de tempo = " << escalaDeTempo << '\n';
            cout << "Tempo obstaculos: " << f << "/" << limF << ", Tempo lvl: " << l << endl;
            cout << "Pos Player: (" << entidades.at(0)->sprite.x << "," << entidades.at(0)->sprite.y << ")"
                 << " Tamanho(H,L): (" << entidades.at(0)->sprite.H() << "," << entidades.at(0)->sprite.L() << ")\n";
            cout << "Pos OBS: (" << entidades.at(entidades.size() - 1)->sprite.x << ","
                 << entidades.at(entidades.size() - 1)->sprite.y << ")" << " Tamanho(H,L): ("
                 << entidades.at(entidades.size() - 1)->sprite.H() << ","
                 << entidades.at(entidades.size() - 1)->sprite.L() << ")\n";
            cout << "Numero de colisoes: " << colisoes.size() / 2 << "\n";
            fflush(stdout);
            cout << flush;
            tecla = InputManager::_kbhit();
            if (tecla){
                teclaPrint += tecla;
                InputManager::getKey();
            }
            cout << "Tecla pressionada: " << teclaPrint << "\n";
        }
        if(redimensionar && noob){
            cout << "Redimensione o terminal ate que a moldura seja visivel sem distorcao." << endl;
            cout << "Para desabilitar esta mensagem edite o arquivo VariaveisConfig.h" << endl;
            pressioneEnter();
            redimensionar = false;
        }


        usleep(periodo);
        if (time(0) - now >= 1){
            now = time(0);
            fps = ciclos;
            ciclos = 0;
            performace = fps/frequencia;
        }
        if (f >= limF){
            jogo.criaObstaculo(*this, maxX, maxY, 2);
            f = 0;
            limF = (rand() % 20) + 21;

            update(performace);
            desenhador.desenha(batch, tela);
        }
        if (l >= 70 && dificuldade == 1){
            dificuldade++;
            pw.salvaPerfil(nomeArquivoDados, perfil, pontos, dificuldade);
            lvlup(2);
        }
        if(l >= 140 && dificuldade == 2){
            dificuldade++;
            pw.salvaPerfil(nomeArquivoDados, perfil, pontos, dificuldade);
            lvlup(3);
        }
    }

    system("clear");
    cout << "Você perdeu!" << endl;
    appendSave(nomeArquivo, perfil, pontos);
    cout << "O seguinte perfil foi adicionado: " << "|Nome: " << perfil << "|Pontuacao: " << pontos << "|" << endl;
    pressioneEnter();
}

void Engine::addEntidade(Entidade *entidade) {
    entidades.push_back(entidade);
}

void Engine::removeEntidade(Entidade *entidade) {
    int i = -1;
    // Necessita de otimização
    for (size_t j = 0; j < entidades.size(); ++j) {
        if (entidades[j] == entidade){
            i = j;
        }
    }
    if (i >= 0){
        Entidade *temp = entidade;
        entidades.erase(entidades.begin() + i);
        delete temp;
    }
}

void Engine::attFisica(Entidade *entidade, float performace) {
    if(contemComponente(Componente::PLAYER, entidade->getComponentes())){
        if(entidade->sprite.y >= maxY && InputManager::_kbhit()){
            entidade->velocidade.y -= 20;
        }
    }
    entidade->sprite.x += entidade->velocidade.x * escalaDeTempo*(1/frequencia)/performace;
    entidade->sprite.y += entidade->velocidade.y * escalaDeTempo*(1/frequencia)/performace;
    if(contemComponente(Componente::GRAVIDADE, entidade->getComponentes())){
        entidade->velocidade.y += gravidade * escalaDeTempo*(1/frequencia)/performace;
        if(entidade->sprite.y >= maxY){
            entidade->velocidade.y = 0;
            entidade->sprite.y = maxY;
        }
    }

}

void Engine::attGrafica(Entidade *entidade) {
    batch.addSprite(entidade->sprite);
}

void Engine::emForaDaTela(Entidade *entidade) {
    if (contemComponente(Componente::OBSTACULO, entidade->getComponentes())){
        removeEntidade(entidade);
    }
}

void Engine::update(float performace) {
    batch.limpa();
    colisoes.clear();
    for (size_t i = 0; i < entidades.size(); ++i) {
        for (size_t j = 0; j < entidades.size(); ++j){
            if(i != j){
                Entidade *a = entidades.at(i);
                Entidade *b = entidades.at(j);
                if(colidem(a, b)){
                    pair<Entidade *, Entidade *> p(a,b);
                    a->emColisao();
                    if(contemComponente(Componente::PLAYER, a->getComponentes())){
                        this->status = Status::sair;
                    }
                    colisoes.push_back(p);
                }
            }
        }

        Entidade *entidade = entidades[i];
        attFisica(entidade, performace);
        attGrafica(entidade);
        if (checaForaDaTela(entidade, maxX, maxY)){
            entidade->emForaDaTela();
            Engine::emForaDaTela(entidade);

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

    if(emDebug) {
        if (aparenciaP == "1") {
            aparenciaP = "playerTeste.txt";
        }

        if (aparenciaO == "1") {
            aparenciaO = "obstaculoTeste.txt";
        }
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

void Engine::carregaJogo(string nomeArquivo, float dificuldadeP, unsigned pontuacao) {
    novoJogo(nomeArquivo, dificuldadeP, pontuacao);
}

bool Engine::colidem(Entidade *a, Entidade *b) {

    if(contemComponente(Componente::COLISAO, a->getComponentes()) && contemComponente(Componente::COLISAO, b->getComponentes())){
        if((int)a->sprite.x <= (int)b->sprite.x + (int)b->sprite.L() &&
        (int)a->sprite.x + (int)a->sprite.L() >= (int)b->sprite.x &&
        (int)a->sprite.y >= (int)b->sprite.y - (int)b->sprite.H() &&
        (int)a->sprite.y - (int)a->sprite.H() <= (int)b->sprite.y){
            return true;
        }
    }
    return false;
}

void Engine::lvlup(int lvl) {
    escalaDeTempo += 0.3;
    for(Entidade *entidade : entidades){
        if(contemComponente(Componente::PLAYER, entidade->getComponentes())){
            entidade->sprite.setSprite(matrizPlayer[lvl - 1]);
        }
        else if(contemComponente(Componente::OBSTACULO, entidade->getComponentes())){
            entidade->sprite.setSprite(matrizObstaculo[lvl - 1]);
        }
    }
}

int Engine::appendSave(string nomeArquivo, string perfil,  unsigned pontuacao){
    ofstream outfile;
    outfile.open(nomeArquivo, std::ios_base::app);
    outfile << (perfil + "|" + to_string(pontuacao) + "\n");
    outfile.close();
    return 0;
}

