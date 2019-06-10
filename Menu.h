
#ifndef TRABALHO_MENU_H
#define TRABALHO_MENU_H

#include "Engine.h"
#include "VariaveisConfig.h"

class Menu {
public:
    explicit Menu(Engine &engine);
    
    //Exibe o menu com as opcoes possiveis
    void exibe();

private:
    string msgAdicional;
};


#endif
