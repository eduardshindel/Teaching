#ifndef MY_BIG_CHARS
#define MY_BIG_CHARS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "My_Term.h"

#define VERTICAL_LINE "x"            // │
#define HORIZONTAL_LINE "q"          // ─
#define BOTTOM_RIGHT_CORNER "j"      // ┘
#define TOP_RIGHT_CORNER "k"         // ┐
#define BOTTOM_LEFT_CORNER "m"       // └
#define TOP_LEFT_CORNER "l"          // ┌
#define PAINT "a"                    // ▒

extern int zero[2];
extern int one[2];
extern int two[2];
extern int three[2];
extern int four[2];
extern int five[2];
extern int six[2];
extern int seven[2];
extern int eight[2];
extern int nine[2];
extern int bigA[2];
extern int bigB[2];
extern int bigC[2];
extern int bigD[2];
extern int bigE[2];
extern int bigF[2];
extern int plus[2];
extern int minus[2];

int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *big, int x1, int y1, enum colors fgcolor, enum colors bgcolor);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int *big, int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);

#endif