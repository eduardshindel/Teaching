#include "matrix.h"

void matrix_init(matrix* m, int size)
{
	m->size = size;
	m->elements = (double**)malloc(sizeof(double*) * size);

	for (int i = 0; i < size; ++i)
	{
		m->elements[i] = malloc(sizeof(double) * size);
	}
}

void matrix_free(matrix* m)
{
	for (int i = 0; i < m->size; ++i)
	{
		free(m->elements[i]);
	}

	free(m->elements);
	m->elements = NULL;
	m->size = 0;
	m = NULL;
}

void matrix_transpose(matrix* m)
{
	double tmp = 0.0;

	for (int i = 0; i < m->size; ++i)
	{
		for (int j = i+1; j < m->size; ++j)
		{
			tmp = m->elements[i][j];
			m->elements[i][j] = m->elements[j][i];
			m->elements[j][i] = tmp;
		}
	}
}

void matrix_multiply(vector* tmp, matrix* m, vector* v)
{
	int size = tmp->size;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			tmp->elements[i] += m->elements[i][j] * v->elements[j]; 
		}
	}
}

