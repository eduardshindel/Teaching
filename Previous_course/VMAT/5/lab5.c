#include "lab5.h"

double function(int x) {
    return x * x;
}

double Lagrange(double *mx, double *my, int X) {
    double Y = 0.0, diff = 1.0;

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < X; j++) {
            if (j != i) diff *= (X - mx[j]) / (mx[i] - mx[j]);
        }
        Y += my[i] * diff;
        diff = 1.0;
    }
    return Y;
}

double Aitken(double *mx, double *my, int X) {
    double ma[X];
    for (int i = 0; i < X; i++) ma[i] = my[i];
    
    for (int k = 0; k < X; k++) {
        int XX = X - k;
        for (int i = 0, j = k + 1; j < X; i++, j++) {
            ma[i] = (ma[i] * (X - mx[j]) - ma[j - k] * (X - mx[i])) / (mx[i] - mx[j]);
        }
    }
    return ma[0];
}

double Newton(double *mx, double *my, int X) {
    double mn[X], Px = my[0], diff = 1.0;
    for (int i = 0; i < X; i++) mn[i] = my[i];
    
    for (int k = 0; k < X; k++) {
        int XX = X - k;
        for (int i = 0, j = k + 1; j < X; i++, j++) {
            mn[i] = (mn[j - k] - mn[i]) / (mx[j] - mx[i]);
        }
        for (int f = 0; f <= k; f++) diff *= X - mx[f];
        Px += mn[0] * diff;
        diff = 1.0;
    }
    return Px;
}
