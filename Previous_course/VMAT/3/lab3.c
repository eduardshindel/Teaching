#include "lab3.h"

double aim(int x) {
    double exp = 1.0;
    for (int i = 0; i < x; i++) exp /= 10;
    return exp;
}

double function(double x) {
    double f = cos(x) + 2 * sin(2 * x) - 1 / x;
    return f;
}

int check(double a, double b) {
    double f_a, f_b;
    f_a = function(a);
    f_b = function(b);
    return (((f_a * f_b) < 0) ? 0 : 1);
}

void all_in(int e) {
    double a = 0.5, b = 2.0;
    double dif = aim(e);
    if (check(a, b)) {
        printf("No roots in the interval [%.1f; %.1f]\n", a, b);
        return;
    }
    bisection(e, dif, a, b);
    chord(e, dif, a, b);
    Newton(e, dif, a, b);
}

void bisection(int e, double dif, double a, double b) {
    double x, f_a, f_x;
    int N = 0;

    do {
        x = (a + b) / 2;
        printf("x%d = %f [%f; %f]\n", N, x, a, b);
        f_a = function(a);
        f_x = function(x);
        if ((f_a * f_x) < 0) b = x;
        else a = x;
        N++;
    } while (fabs(f_x) > dif);
    printf("bisection: x = %.*f (N = %d)\n", e, x, N - 1);
}

void chord(int e, double dif, double a, double b) {
    double x0 = 0.0, x1 = 0.0;
    int N = 0;

    do {
        x0 = x1;
        x1 = (a * function(b) - b * function(a)) / (function(b) - function(a));
        printf("x%d = %f [%f; %f]\n", N, x1, a, b);
        if ((function(a) * function(x1)) < 0) b = x1;
        else a = x1;
        N++;
    } while (fabs(x1 - x0) > dif);
    printf("chord: x = %.*f (N = %d)\n", e, x1, N - 1);
}

void Newton(int e, double dif, double a, double b) {
    double x0 = 0.0, x1 = 0.0, f1, f2;
    int N = 0;

    f2 = (function(a + dif) - 2 * function(a) + function(a - dif)) / (dif * dif);
    if ((function(a) * f2) > 0) x1 = a;
    else x1 = b;

    do {
        x0 = x1;
        f1 = (function(x0 + dif) - function(x0 - dif)) / (2 * dif);
        x1 = x0 - (function(x0) / f1);
        printf("x%d = %f [%f; %f]\n", N, x1, function(x0), f1);
        N++;
    } while (fabs(function(x0) / f1) > dif);
    printf("Newton: x = %.*f (N = %d)\n", e, x0, N - 1);
}