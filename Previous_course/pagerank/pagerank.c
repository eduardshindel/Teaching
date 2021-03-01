#include "pagerank.h"

int calculate_links(matrix* m, int row)
{
	int counter = 0;
	for (int i = 0; i < m->size; ++i)
	{
		counter += m->elements[i][row]; 
	}
	if(counter == 0)
	{
		return m->size;
	}

	return counter;
}

double calculate_probability(matrix* m, int i, int j)
{
	double d = 0.85;
	int r = calculate_links(m, i);

	float a = (1 - d) + d * (m->elements[i][j] / r);

	return a;
}

void gen_web_matrix(matrix* m)
{
	for (int i = 0; i < m->size; ++i)
	{
		for(int j = 0; j < m->size; ++j)
		{
			m->elements[i][j] = rand() % 2;
		}
	}
}

void gen_google_matrix(matrix* a, matrix* m)
{
	int i = 0;
	int j = 0;
	int size = a->size;

	#pragma omp parallel for default(none) shared(a, m, size) private(i, j)
	for (i = 0; i < size; ++i)
	{
		for(j = 0; j < size; ++j)
		{
			a->elements[i][j] = calculate_probability(m, i, j);
		}
	}
}

void matrix_solve(vector* v, matrix* m)
{
	int size = m->size;

	vector tmp_vec;
	vector_init(&tmp_vec, size);

	for (int i = 0; i < size; ++i)
	{
		v->elements[i] = 1.0;
		tmp_vec.elements[i] = 0.0;
	}

	for(int x = 0; x < 3; ++x)
	{
		matrix_multiply(&tmp_vec, m, v);

		vector_normalize(&tmp_vec);

		for (int i = 0; i < size; ++i)
		{
			v->elements[i] = tmp_vec.elements[i];
			tmp_vec.elements[i] = 0.0;
		}
	}
	vector_free(&tmp_vec);
}

void page_rank(int size)
{
	matrix w;
	matrix_init(&w, size);
	gen_web_matrix(&w);

	matrix g;
	matrix_init(&g, size);
	gen_google_matrix(&g, &w);
	matrix_free(&w);

	vector p;
	vector_init(&p, size);
	matrix_transpose(&g);
	matrix_solve(&p, &g);
	vector_sort(&p);

	matrix_free(&g);
	vector_free(&p);
}

