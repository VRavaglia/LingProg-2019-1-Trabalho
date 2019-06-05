#include <fstream>
#include <iostream>
#include "Desenhador.h"
#include "Engine.h"
#include "Menu.h"


int main(){
    Engine engine;
    Menu menu(engine);
    menu.exibe();
}
