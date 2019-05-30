#include <iostream>
#include "Menu.h"

Menu::Menu(Engine &engine) {

}

void Menu::exibe() {
    system("clear");
    cout << "|===================================|\n";
    cout << "|       Trabalho 3 - Dinojogo       |\n";
    cout << "|===================================|\n";
    cout << "| 0 --------------------------- Sair|\n";
    cout << "| 1 ---------------------- Novo Jogo|\n";
    cout << "| 2 ------------------ Carregar Jogo|\n";
    cout << "| 3 ----- Lista N maiores pontuacoes|\n";
    cout << "| 4 - Lista pontuacoes de um jogador|\n";
    cout << "|===================================|\n";
}
