#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#define _XOPEN_SOURCE 700
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
#include <sys/select.h>
#include <stropts.h>
#include <sys/ioctl.h>

#include <string>
#include <iostream>
#include <fstream>




/// Controle de entradas mais complexas
class InputManager {

public:
    /// Espera pela entrada de uma tecla pausando a execucao e retorna qual tecla foi pressionada
    static int getkeyPause();

    /// Espera pela entrada de uma tecla sem pausar a execucao e retorna qual tecla foi pressionada
    static int getKey();

    /// Espera por uma tecla qualquer sem pausar o tempo de execucao
    static int _kbhit();

    /// Le de maneira adequada a entrada do usuaria que for numerica ("cin >>" se mostrou um problema)
    static int getNumber();

    /// Checa se um arquivo ja existe
    static bool arquivoExiste(std::string nomeArquivo);
};


#endif
