#ifndef TRABALHO_ENGINE_H
#define TRABALHO_ENGINE_H

#include "Desenhador.h"
#include "Entidade.h"
#include <vector>

/// Classe que controla o andamento do jogo
class Engine {
public:
    Engine();
    /// Atualiza valores que mudam com o tempo
    void update(unsigned ciclos);

    /// Velocidade de reprodução do jogo
    float escalaDeTempo;

    void addEntidade(Entidade &entidade);

    /// Jogo em si
    void jogo();
private:

    /// Cuida da parte visual, desenha na tela
    Desenhador desenhador;

    /// Ainda sem implementação, status se o jogo deve continuar rodando
    bool rodando;

    /// Frequência de atualização do jogo (tentativa de fps)
    float frequencia;

    std::vector <Entidade> entidades;
};


#endif //TRABALHO_ENGINE_H
