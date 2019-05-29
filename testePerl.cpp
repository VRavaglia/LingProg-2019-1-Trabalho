#include <iostream>
#include <string>
#include <vector>
#include "perlWrapper.h"

using namespace std;

int main(){
    perlWrapper pw;
    pw.interpretador();
    cout << "Salva Perfil" << endl;
    cout << pw.salvaPerfil("dadosTeste.txt",  "raposo", 6666, 6.6)  << endl;
    cout << "Le Jogo, status|pontos" << endl;
    unsigned temp;
    cout << pw.leJogo("raposo",6, "dadosTeste.txt", temp)  << " | " << temp << endl;
    cout << "Aparencia" << endl;
    vector <vector<string>> sprites = pw.configuraAparencia("playerTeste.txt", "obstaculoTeste.txt");
    for (vector<string> sprite : sprites) {
        for (string linha : sprite){
            cout << linha << endl;
        }
    }
    vector <pair<string, unsigned>> pontuacoes;
    pw.listaPontuacoesMaiores("dadosTeste.txt", 5, pontuacoes);
    cout << "Maiores Pontuacoes:" << endl;
    for (pair<string, unsigned> p : pontuacoes){
        cout << p.first << " | " << p.second << endl;
    }

    cout << "Lista Por nome" << endl;
    vector <unsigned > pontos;
    pw.listaPontuacoesJogador("raposo", 1, "dadosTeste.txt", pontos);
    for(unsigned p:pontos){
        cout << p << endl;
    }

    return 0;
}