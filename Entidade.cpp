#include "Entidade.h"
#include "Utilidades.h"
#include "Engine.h"

bool contemComponente(Componente componente, unsigned componentes){

    if(componentes % componente == 0){
        return true;
    }

    return false;
}

Entidade::Entidade(): velocidade (vec2<float>(0,0)){
}

void Entidade::emForaDaTela(Engine *engine) {
}

void Entidade::emColisao(Engine *engine) {

}

void Entidade::addComponente(Componente componente) {
    componentes = componentes * componente;
}

void Entidade::removeComponente(Componente componente) {
    if (contemComponente(componente, componentes)){
        componentes = componentes/componente;
    }
}

unsigned Entidade::getComponentes() {
    return componentes;
}

void Player::emColisao(Engine *engine) {
    //engine->status = Status::sair;
}
