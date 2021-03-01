#include "vector.h"

void vector_init(vector* v, int size)
{
    v->size = size;
    v->elements = (double*)malloc(sizeof(double) * v->size);
}

void vector_free(vector* v)
{
    free(v->elements);
    v->elements = NULL;
    v->size = 0;
    v = NULL;
}

void vector_normalize(vector* v)
{
    double sum = 0.0;
    for (int i = 0; i < v->size; ++i)
    {
	sum += v->elements[i];
    }
    for (int i = 0; i < v->size; ++i)
    {
	v->elements[i] /= sum;
    }
}

void vector_sort(vector* v)
{
    qsort(v->elements, v->size, sizeof(double), double_compare);
}

int double_compare(const void* a, const void* b)
{
    double* arg1 = (double*) a;
    double* arg2 = (double*) b;

    if(*arg1 < *arg2) return -1;
    else if (*arg1 == *arg2) return 0;
    else return 1;
}