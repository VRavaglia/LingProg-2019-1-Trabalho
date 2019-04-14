#include "Desenhador.h"
#include <algorithm>
#include <iostream>
using namespace std;

const size_t maxX = 100;
const size_t maxY = 100;


// Compara a dimensão z ou profundidade dos sprites para ordena-los
struct {
    bool operator()(Sprite &sprite1, Sprite &sprite2) const
    {
        return sprite1.z < sprite2.z;
    }
} spriteLessZ;

Sprite::Sprite(string &arquivo, int x_, int y_, int z_) {
    sprite = Sprite::arquivoParaSprite(arquivo);
    x = x_;
    y = y_;
    z = z_;
}

vector <vector <char>> Sprite::arquivoParaSprite(string &arquivo){
    vector <vector <char>> spriteNovo;
    //Ler arquivo texto e converter para uma matriz de caracteres
    return spriteNovo;
};

void ListaSprites::addSprite(Sprite &sprite) {
    sprites.push_back(sprite);
}

std::vector<Sprite> ListaSprites::getSprites() {
    return sprites;
}

void ListaSprites::ordenaSpritesPorZ() {
    // Classifica os sprites por ordem de profundidade
    sort(sprites.begin(), sprites.end(), spriteLessZ);
}

Tela::Tela() {
    // Inicializa a matriz de caracteres (evitar re-alocação)
    tela.reserve(maxX);
    for (size_t i = 0; i < tela.size(); ++i) {
        tela[i].reserve(maxY);
    }
}

size_t Tela::H() {
    return tela.size();
}

size_t Tela::L() {
    return tela[0].size();
}

void Tela::setPixel(size_t x, size_t y, char pixel) {
    tela[x][y] = pixel;
}

char Tela::getPixel(size_t x, size_t y) {
    return tela[x][y];
}

void Tela::limpa() {
    //Itera na matriz preenchendo-a com ' '
    for (size_t i = 0; i < Tela::H(); ++i) {
        size_t comprimento = Tela::L();
        for (size_t j = 0; j < comprimento; ++j) {
            Tela::setPixel(i, j, ' ');
        }
    }
}

void Desenhador::escreveTela(Tela &tela) {
    // Imprime os caracteres da tela no console
    for (size_t i = 0; i < tela.H(); ++i) {
        size_t L = tela.L();
        for (size_t j = 0; j < L; ++j) {
            cout << tela.getPixel(i,j);
        }
        cout << endl;
    }
}

void Desenhador::desenha(ListaSprites &sprites, Tela &tela) {
    tela.limpa();
    size_t tamanhoLista = sprites.getSprites().size();

    // Adiciona as informações de cada sprite na tela
    for (size_t i = 0; i < tamanhoLista; ++i) {
        //Adiciona os caracteres do sprite a tela
    }
    escreveTela(tela);
}

