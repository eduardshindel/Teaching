#ifndef MY_READ_KEY_H
#define MY_READ_KEY_H

#include "My_Big_Chars.h"
#include "My_Term.h"
#include <string.h>

enum keys {
    q,
    l,
    s,
    r,
    t,
    i,
    f5,
    f6,
    up,
    down,
    left,
    right,
    enter
};

int rk_readkey(int *key);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif