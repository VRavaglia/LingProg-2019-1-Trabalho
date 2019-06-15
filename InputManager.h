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



class InputManager {

public:
    static int getkeyPause();
    static int getKey();
    static int _kbhit();
};


#endif
