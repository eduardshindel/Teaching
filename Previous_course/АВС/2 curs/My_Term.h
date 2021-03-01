#ifndef MY_TERM
#define MY_TERM

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>

enum colors {
    black,
	red,
	green,
	yellow,
	blue,
	violet,
	light_blue,
	white
};

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);

#endif
