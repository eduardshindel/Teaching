#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

typedef struct vector
{
    double* elements;
    int size;
} vector;

void vector_init(vector* v, int size);
void vector_free(vector* v);
void vector_normalize(vector* v);
void vector_sort(vector* v);
int double_compare(const void* a, const void* b);

#endif