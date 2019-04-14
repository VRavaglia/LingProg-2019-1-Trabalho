
#include "Desenhador.h"
#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector <vector <char>> triangle {{' ',' ','0'},
                                    {' ','0','0'},
                                    {'0','*','0'},
                                    {' ','0','0'},
                                    {' ',' ','0'}};

    vector <vector <char>> box {{'&','&','&'},
                                {'&','$','&'},
                                {'&','&','&'}};
    Sprite sprite1(box, 10, 10, 0);
    Sprite sprite2(triangle, 40, 5, 0);
    Tela tela;
    Desenhador desenhador;
    ListaSprites batch;
    batch.addSprite(sprite1);
    batch.addSprite(sprite2);
    desenhador.desenha(batch, tela);

}
