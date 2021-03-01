#ifndef LAB4_H
#define LAB4_H

#include <stdio.h>
#include <stdlib.h>

double function(int x);
double Lagrange(double *mx, double *my, int X);
double Aitken(double *mx, double *my, int X);
double Newton(double *mx, double *my, int X);

#endif