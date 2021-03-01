#include "My_Term.h"

int mt_clrscr() {
    printf("=\E[H\E[J");
    return 0;
}

int mt_getscreensize(int *rows, int *cols) {
    struct winsize ws;

    if (!ioctl(1, TIOCGWINSZ, &ws)) {
        *rows = ws.ws_row;
        *cols = ws.ws_col;
        return 0;
    } else {
        return 1;
    }
}

int mt_gotoXY(int x, int y) {
    int rows, cols;

    mt_getscreensize(&rows, &cols);
    if ((x >= 0) && (x <= rows) && (y >= 0) && (y <= cols)) {
        printf("\E[%d;%dH", x, y);
        return 0;
    }
    else {
        return 1;
    }
}

int mt_setfgcolor(enum colors color) {
    switch (color) {
		case black:
			printf("\E[30m");
			break;
		case red:
			printf("\E[31m");
			break;
		case green:
			printf("\E[32m");
			break;
		case yellow:
			printf("\E[33m");
			break;	
		case blue:
			printf("\E[34m");
			break;
		case violet:
			printf("\E[35m");
			break;
		case light_blue:
			printf("\E[36m");
			break;
		case white:
			printf("\E[37m");
			break;
		default:
			return -1;
	}
	return 0;
}

int mt_setbgcolor(enum colors color) {
    switch (color) {
		case black:
			printf("\E[40m");
			break;
		case red:
			printf("\E[41m");
			break;
		case green:
			printf("\E[42m");
			break;
		case yellow:
			printf("\E[43m");
			break;	
		case blue:
			printf("\E[44m");
			break;
		case violet:
			printf("\E[45m");
			break;
		case light_blue:
			printf("\E[46m");
			break;
		case white:
			printf("\E[47m");
			break;
		default:
			return -1;
	}
	return 0;
}