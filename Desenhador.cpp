#include "Desenhador.h"
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
    l = sprite_.size();
    h = sprite_[0].size();
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

vector <vector <char>> Sprite::arquivoParaSprite(string &arquivo){
    vector <vector <char>> spriteNovo;
    //Ler arquivo texto e converter para uma matriz de caracteres
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


Tela::Tela(unsigned maxX_, unsigned maxY_){
    maxX = maxX_;
    maxY = maxY_;
    // Inicializa a matriz de caracteres
    for (size_t x = 0; x < Tela::L(); ++x) {
        size_t H = Tela::H();
        vector <char> coluna;
        coluna.reserve(maxY);
        tela.push_back(coluna);
        for (size_t y = 0; y < Tela::L(); ++y) {
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
        tela[x][y] = pixel;
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
        cout << endl;
    }
}

void Desenhador::desenha(ListaSprites &sprites, Tela &tela) {
    tela.limpa();
    size_t tamanhoLista = sprites.getSprites().size();

    // Adiciona as informações de cada sprite na tela
    for (size_t i = 0; i < tamanhoLista; ++i) {
        Sprite sprite = sprites.getSprites()[i];
        for (size_t x = 0; x < sprite.L(); ++x) {
            for (size_t y = 0; y < sprite.H(); ++y) {
                char pixel = sprite.getSprite()[x][y];
                if (pixel != ' '){
                    tela.setPixel(round(x) + sprite.x, round(y) + sprite.y, pixel);
                }
            }
        }
    }
    system("clear");
    escreveTela(tela);
}

