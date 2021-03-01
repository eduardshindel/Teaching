#ifndef MATRIX_H
#define MATRIX_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

typedef struct matrix
{
    double** elements;
    int size;
} matrix;

void matrix_init(matrix* m, int size);
void matrix_free(matrix* m);
void matrix_transpose(matrix* m);
void matrix_multiply(vector* tmp, matrix* m, vector* v); 

#endif

