#include "lab4.h"

double f1(double x, double y, int i) {
    double f;
    if (i == 1) f = 2 * (x * x) + y - 4;
    else f = x * x + y * y - 4;
    return f;
}

double f2(double x, double y, int i, double dif) {
    double f2;
    if (i == 1) f2 = (f1(x + dif, y, 1) - f1(x - dif, y, 1)) / (2 * dif);
    else if (i == 2) f2 = (f1(x, y + dif, 1) - f1(x, y - dif, 1)) / (2 * dif);
    else if (i == 3) f2 = (f1(x + dif, y, 2) - f1(x - dif, y, 2)) / (2 * dif);
    else f2 = (f1(x, y + dif, 2) - f1(x, y - dif, 2)) / (2 * dif);
    return f2;
}

void inverse_matrix(double **m) {
    double dop, opr = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    dop = m[0][0];
    m[0][0] = m[1][1] / opr;
    m[1][1] = dop / opr;
    m[0][1] = -m[0][1] / opr;
    m[1][0] = -m[1][0] / opr;
}

double aim(int e) {
    double dif = 1.0;
    for (int i = 0; i < e; i++) dif /= 10;
    return dif;
}

void Newton(int e, double x, double y) {
    double x0, y0, dif = aim(e);
    double **W = malloc(2 * sizeof(double *));
    W[0] = malloc(2 * sizeof(double));
    W[1] = malloc(2 * sizeof(double));

    do {
        x0 = x;
        y0 = y;
        W[0][0] = f2(x, y, 1, dif);
        W[0][1] = f2(x, y, 2, dif);
        W[1][0] = f2(x, y, 3, dif);
        W[1][1] = f2(x, y, 4, dif);
        inverse_matrix(W);
        x = x - (W[0][0] * f1(x, y, 1) + W[0][1] * f1(x, y, 1));
        y = y - (W[1][0] * f1(x, y, 2) + W[1][1] * f1(x, y, 2));
    } while ((fabs(x - x0) > dif) || (fabs(y - y0) > dif));
    printf("x = %.*f\ny = %.*f\n", e, x, e, y);
} 

