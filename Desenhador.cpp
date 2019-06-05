#include "Desenhador.h"
#include<fstream>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;


// Compara a dimensão z ou profundidade dos sprites para ordena-los
struct {
    bool operator()(Sprite &sprite1, Sprite &sprite2) const
    {
        return sprite1.z < sprite2.z;
    }
} spriteLessZ;

void Sprite::setSprite(vector <vector <char>> &sprite_) {
    h = sprite_.size();
    l = 0;
    for(vector<char> &linha : sprite_){
        if(linha.size() > l){
            l = linha.size();
        }
    }
    sprite = sprite_;
}

void Sprite::setSprite(std::string &arquivo) {
    sprite = Sprite::arquivoParaSprite(arquivo);
}

vector <vector <char>> Sprite::getSprite() {
    return sprite;
}

Sprite::Sprite() {
    vector <vector <char>> pixel = {{' '}};
    setSprite(pixel);
    x = 0;
    y = 0;
    z = 0;
}

Sprite::Sprite(string &arquivo, float x_, float y_, int z_) {
    setSprite(arquivo);
    x = x_;
    y = y_;
    z = z_;
}

Sprite::Sprite(vector <vector <char>> &sprite, float x_, float y_, int z_) {
    setSprite(sprite);
    x = x_;
    y = y_;
    z = z_;
}

vector <vector <char>> Sprite::arquivoParaSprite(string &nomeArquivo){
    vector <vector <char>> spriteNovo;
    ifstream arquivo(nomeArquivo);
    size_t l_ = 0;
    if (arquivo.is_open()) {
        string linhaString;
        while (getline(arquivo, linhaString)) {
            vector<char> linhaVector;
            for(char &c : linhaString){
                if (c != '\r' && c != '\n') {
                    linhaVector.push_back(c);
                }
            }
            spriteNovo.push_back(linhaVector);
            if (linhaVector.size() > l_){
                l_ = linhaVector.size();
            }
        }
        arquivo.close();
    }
    l = l_;
    h = spriteNovo.size();
    return spriteNovo;
};

size_t Sprite::L() {
    return l;
}

size_t Sprite::H() {
    return h;
}

void ListaSprites::addSprite(Sprite &sprite) {
    sprites.push_back(sprite);
    ordenaSpritesPorZ();
}

std::vector<Sprite> ListaSprites::getSprites() {
    return sprites;
}

void ListaSprites::ordenaSpritesPorZ() {
    // Classifica os sprites por ordem de profundidade
    sort(sprites.begin(), sprites.end(), spriteLessZ);
}

void ListaSprites::limpa() {
    sprites.clear();
}

void initMatrix(){

}


Tela::Tela(unsigned maxX_, unsigned maxY_, bool frame_){
    maxX = maxX_;
    maxY = maxY_;
    frame = frame_;
    // Inicializa a matriz de caracteres
    for (size_t x = 0; x < Tela::L(); ++x) {
        size_t H = Tela::H();
        vector <char> coluna;
        coluna.reserve(maxY);
        tela.push_back(coluna);
        for (size_t y = 0; y < Tela::H(); ++y) {
            tela[x].push_back(' ');
        }

    }
}


size_t Tela::H() {
    return maxY;
}

size_t Tela::L() {
    return maxX;
}

void Tela::setPixel(size_t x, size_t y, char pixel) {
    if (x < maxX and x >= 0 and y < maxY and y > 0 ){
        tela.at(x).at(y) = pixel;
    }

}

char Tela::getPixel(size_t x, size_t y) {
    return tela[x][y];
}

void Tela::limpa() {
    //Itera na matriz preenchendo-a com ' '
    for (size_t x = 0; x < Tela::L(); ++x) {
        size_t H = Tela::H();
        for (size_t y = 0; y < H; ++y) {
            Tela::setPixel(x, y, ' ');
        }
    }
}

void Desenhador::escreveTela(Tela &tela) {
    // Imprime os caracteres da tela no console
    for (size_t y = 0; y < tela.H(); ++y) {
        for (size_t x = 0; x < tela.L(); ++x) {
            cout << tela.getPixel(x,y);
        }
        cout << '\n';
    }
}

void Desenhador::desenha(ListaSprites &sprites, Tela &tela) {
    tela.limpa();
    size_t tamanhoLista = sprites.getSprites().size();
    int f = 0;
    if (tela.frame){
        f = 1;
    }

    // Adiciona as informações de cada sprite na tela
    for (size_t i = 0; i < tamanhoLista; ++i) {
        Sprite sprite = sprites.getSprites().at(i);
        for (size_t y = 0; y < sprite.getSprite().size(); ++y)
        {
            size_t sizeY = sprite.getSprite().at(y).size();
            for (size_t x = 0; x < sizeY; ++x){
                char pixel = sprite.getSprite().at(y).at(x);
                if (pixel && pixel != ' '){
                    tela.setPixel(round(x) + sprite.x + f, round(y) + sprite.y - sprite.H() - f, pixel);
                }
            }
        }
    }
    if(tela.frame){
        for(unsigned i = 0; i < tela.maxX; i++){
            tela.setPixel(i,1,'#');
        }
        for(unsigned i = 0; i < tela.maxX; i++){
            tela.setPixel(i,tela.maxY - 1,'#');
        }
        for(unsigned i = 0; i < tela.maxY; i++){
            tela.setPixel(0,i,'#');
        }
        for(unsigned i = 0; i < tela.maxY; i++){
            tela.setPixel(tela.maxX - 1,i,'#');
        }
    }
    system("clear");
    escreveTela(tela);
}

vector<vector<char>> Desenhador::listaStringParaMatrizChar(std::vector<std::string> &vetor) {
    vector<vector<char>> sprite;
    for(string &linha : vetor){
        vector<char> linhaNova;
        for(char c : linha){
            linhaNova.push_back(c);
        }
        sprite.push_back(linhaNova);
    }

    return sprite;
}

