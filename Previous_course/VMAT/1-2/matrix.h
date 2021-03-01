#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void printMatrix(double **m, int len);
void initMatrix(double **m, int len, int p);
int maxElement(double **m, int len, int exp);
void printAnswer(double **m, int len);
int gaussMatrix(double **m, int len);
int simple_it(double **m, int len, int eps);
int method_Z(double **m, int len, int eps);
double epsMatrix(int x);

#endif