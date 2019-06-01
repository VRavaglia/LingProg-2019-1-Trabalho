

#ifndef TRABALHO_DESENHADOR_H
#define TRABALHO_DESENHADOR_H

#include <string>
#include <vector>


/// Classe que armazena uma matriz de char para ser lido como um sprite
class Sprite{
public:
    ///Cria um sprite a partir de um arquivo texto, posições no espaço (x e y) e ordem em que vai ser desenhado (profundidade z)
    Sprite();
    Sprite(std::string &nomeArquivo, float x, float y, int z);
    Sprite(std::vector <std::vector <char>> &sprite, float x, float y, int z);

    void setSprite(std::vector <std::vector <char>> &sprite);
    void setSprite(std::string &arquivo);
    std::vector <std::vector <char>> getSprite();



    /// Retorna a largura
    size_t L();

    /// Retorna a altura
    size_t H();

    ///Posição horizontal
    float x;

    ///Posição vertical
    float y;

    ///Profundidade ou ordem em que será desenhado
    int z;

private:
    /// Armazena a largura
    size_t l;
    /// Armazena a altura
    size_t h;

    ///Le um arquivo texto contendo a informação visual do sprite e converte para uma matriz de caracteres
    std::vector <std::vector <char>> arquivoParaSprite(std::string &arquivo);

    ///Armazena a matriz de char
    std::vector <std::vector <char>> sprite;
};

/// Contém uma lista de sprites (batch) que serão desenhados na tela
class ListaSprites{
public:
    /// Adiciona um sprite a fila
    void addSprite(Sprite &sprite);

    /// Retorna a fila de sprites
    std::vector <Sprite> getSprites();

    /// Remove os sprites da lista
    void limpa();
private:

    /// Lista de sprites
    std::vector <Sprite> sprites;

    /// Ordena os sprites na fila baseado na profundidade em que aparecem na tela
    void ordenaSpritesPorZ();
};

/// Tela do console, guarda as informações do que será desenhado
class Tela{
public:
    /// Inicializa a matriz de caracteres
    Tela(unsigned maxX, unsigned maxY);

    /// Preenche a matriz com caracteres ' '
    void limpa();

    /// Retorna o tamanho horizontal da tela
    size_t H();

    /// Retorna o tamanho vertical da tela
    size_t L();

    /// Altera o caractere correspondente a um item da matriz baseando-se na sua posição
    void setPixel(size_t x, size_t y, char pixel);

    /// Retorna o caractere contido em uma determinada posição da matriz
    char getPixel(size_t x, size_t y);

private:

    /// Tamanho da tela
    unsigned maxX = 80;
    unsigned maxY = 16;

    /// Matriz de caracteres
    std::vector <std::vector<char>> tela;

};


/// Desenha sprites no console
class Desenhador{
public:
    /// Conversao de vetor de strings para matriz de caracteres
    static std::vector <std::vector<char>> listaStringParaMatrizChar(std::vector<std::string> &vetor);


    /// Insere uma lista de sprites na tela
    void desenha(ListaSprites &sprites, Tela &tela);

private:

    /// Escreve de fato as informações contidas na tela no console
    void escreveTela(Tela &tela);
};


#endif //TRABALHO_DESENHADOR_H
