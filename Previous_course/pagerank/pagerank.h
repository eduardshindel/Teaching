#ifndef PAGERANK_H
#define PAGERANK_H

#include "matrix.h"
#include "vector.h"
#include <omp.h>

int calculate_links(matrix* m, int row);
double calculate_probability(matrix* m, int i, int j);
void gen_web_matrix(matrix* m);
void gen_google_matrix(matrix* a, matrix* m);
void matrix_solve(vector* v, matrix* m);
void page_rank(int size);

#endif