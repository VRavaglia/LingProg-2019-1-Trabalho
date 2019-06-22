
#ifndef TRABALHO_MENU_H
#define TRABALHO_MENU_H

#include "Utilidades.h"

#include "Engine.h"
#include "VariaveisConfig.h"


/// Menu exibido para selecao de opcoes
class Menu {
public:
    explicit Menu(Engine &engine);
    
    //Exibe o menu com as opcoes possiveis
    void exibe();

private:
    string msgAdicional;
};


#endif
