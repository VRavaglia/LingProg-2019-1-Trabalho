#include "Desenhador.h"
#include <algorithm>
#include <iostream>

using namespace std;

const size_t maxX = 80;
const size_t maxY = 16;


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

Sprite::Sprite(string &arquivo, int x_, int y_, int z_) {
    Sprite::setSprite(arquivo);
    x = x_;
    y = y_;
    z = z_;
}

Sprite::Sprite(vector <vector <char>> &sprite, int x_, int y_, int z_) {
    Sprite::setSprite(sprite);
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
}

std::vector<Sprite> ListaSprites::getSprites() {
    return sprites;
}

void ListaSprites::ordenaSpritesPorZ() {
    // Classifica os sprites por ordem de profundidade
    sort(sprites.begin(), sprites.end(), spriteLessZ);
}

Tela::Tela() {
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
    tela[x][y] = pixel;
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
                tela.setPixel(x + sprite.x,y + sprite.y, sprite.getSprite()[x][y]);
            }
        }
    }
    system("clear");
    escreveTela(tela);
}

