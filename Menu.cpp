#include <iostream>
#include "Menu.h"
//#include "perlWrapper.h"

Menu::Menu(Engine &engine) {
    char opcao;
    bool sair = false;
    msgAdicional = "";

//    perlWrapper pw;
//    pw.interpretador();

    while(!sair){
        exibe();

        cin >> opcao;

        switch (opcao){
            case '0':
                sair = true;
                break;
            case '1':
                cout << "Insira a dificuldade: " << endl;
                unsigned dificuldade;
                cin >> dificuldade;
                engine.novoJogo(dificuldade);

                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            default:
                msgAdicional = "A entrada nao foi entendida.";
                break;
        }
    }
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
    cout << msgAdicional << endl;
    cout << "Ensira a opcao desejada:" << endl;
}
