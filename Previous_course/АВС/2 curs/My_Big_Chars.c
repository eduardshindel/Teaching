#include "My_Big_Chars.h"

int zero[2] = {1246118460, 1010983506};
int one[2] = {137893896, 1040713736};
int two[2] = {33702460, 2114979844};
int three[2] = {67634302, 1010958850};
int four[2] = {1210587144, 134744188};
int five[2] = {41697406, 1010958850};
int six[2] = {2084577308, 1010975298};
int seven[2] = {134480510, 269488144};
int eight[2] = {1010975292, 1010975298};
int nine[2] = {1111638588, 939786814};
int bigA[2] = {1111638588, 1111638654};
int bigB[2] = {2084717180, 2084717122};
int bigC[2] = {1077952574, 1044398144};
int bigD[2] = {1111638652, 2084717122};
int bigE[2] = {2118140030, 2118139968};
int bigF[2] = {2118140030, 1077952576};
int plus[2] = {4279769112, 404232447};
int minus[2] = {4278190080, 255};

int bc_printA(char *str) {
    printf("\E(0%s\E(B", str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    int x, y;
    mt_getscreensize(&x, &y);
    mt_setfgcolor(white);
    
    if ((x1 < 0) || (y1 < 0) || (x2 > x) || (y2 > y) || (x2 - x1 < 1) || (y2 - y1 < 1)) return -1;
    
    mt_gotoXY(x1, y1);
    bc_printA(TOP_LEFT_CORNER);

    mt_gotoXY(x2, y1);
    bc_printA(BOTTOM_LEFT_CORNER);
    
    mt_gotoXY(x1, y2);
    bc_printA(TOP_RIGHT_CORNER);
    
    mt_gotoXY(x2, y2);
    bc_printA(BOTTOM_RIGHT_CORNER);

    for (int i = x1 + 1; i < x2; i++) {
        mt_gotoXY(i, y1);
        bc_printA(VERTICAL_LINE);
        mt_gotoXY(i, y2);
        bc_printA(VERTICAL_LINE);
    }
    
    for (int i = y1 + 1; i < y2; i++) {
        mt_gotoXY(x1, i);
        bc_printA(HORIZONTAL_LINE);
        mt_gotoXY(x2, i);
        bc_printA(HORIZONTAL_LINE);
    }
    return 0;
}

int bc_printbigchar(int *big, int x1, int y1, enum colors fgcolor, enum colors bgcolor) {
    int x, y;
    mt_getscreensize(&x, &y);
    x1++;

    if ((x1 < 0) || (y1 < 0) || (x1 + 8 > x) || (y1 + 8 > y)) return -1;
    int bit = 0;
    
    mt_setfgcolor(fgcolor);
    mt_setbgcolor(bgcolor);

    for (int i = 0, j = 0, k = 8; i < 32; i++, k--) {
        if (k == 0) {
            k = 8;
            j++;
        }
        bit = (big[0] >> i) & 1;
        mt_gotoXY(x1 + j, y1 + k);
        if (bit == 0) bc_printA(" ");
        else bc_printA(PAINT);
    }
    for (int i = 0, j = 4, k = 8; i < 32; i++, k--) {
        if (k == 0) {
            k = 8;
            j++;
        }
        bit = (big[1] >> i) & 1;
        mt_gotoXY(x1 + j, y1 + k);
        if (bit == 0) bc_printA(" ");
        else bc_printA(PAINT);
    }
    mt_setfgcolor(white);
    mt_setbgcolor(black);
    return 0;    
}

int bc_setbigcharpos(int *big, int x, int y, int value) {
    if ((x < 0) || (x > 7) || (y < 0) || (y > 7) || (value < 0) || (value > 1)) return -1;

    int pos;
    if (x >= 4) pos = 1;
    else pos = 0;

    y = 7 - y;
    if (value == 0) big[pos] &= ~(1 << (8 * x + y));
    else big[pos] |= 1 << (8 * x + y);
    return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value) {
    if ((x < 0) || (x > 7) || (y < 0) || (y > 7)) return -1;

    int pos;
    if (x >= 4) pos = 1;
    else pos = 0;

    y = 7 - y;
    *value = (big[pos] >> (8 * x + y) & 1);
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count) {  //O_WRONLY
    int res;
    if (res = (write(fd, big, count * (sizeof(int) * 2))) == -1) return -1;
    return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count) {  //O_RDONLY
    int res;
    *count = 0;
    if ((res = read(fd, big, need_count * sizeof(int) * 2)) == -1) return -1;
    *count = res / (sizeof(int) * 2);
    return 0;
}