#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

void omp_dgemm_blas(double **A, double **B, double **C, int size, int num_threads)
{
    omp_set_num_threads(num_threads);
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int size, num_threads;
    if (argc != 3) {
        printf("./(prog_name) (size) (num_threads)\n");
        return 1;
    }
    size = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    srand(time(NULL));

    double **A = (double **) malloc(sizeof(double *) * size);
    double **B = (double **) malloc(sizeof(double *) * size);
    double **C = (double **) malloc(sizeof(double *) * size);
    for (int i = 0; i < size; i++) {
        A[i] = (double *) malloc(sizeof(double) * size);
        B[i] = (double *) malloc(sizeof(double) * size);
        C[i] = (double *) malloc(sizeof(double) * size);
        for (int j = 0; j < size; j++) { 
            A[i][j] = (double) (rand() % 201 - 100);
            B[i][j] = (double) (rand() % 201 - 100);
            C[i][j] = 0.0;
        }
    }

    double t = omp_get_wtime();
    omp_dgemm_blas(A, B, C, size, num_threads);
    t = omp_get_wtime() - t;

    printf("Time (%d threads) = %.2f sec\n", num_threads, t);
    free(A);
    free(B);
    free(C);
    return 0;
}