#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void dgemm_blas(double **A, double **B, double **C, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void dgemm_opt(double **A, double **B, double **C, int size)
{
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            for (int j = 0; j < size; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main (int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR!\n");
        return 1;
    }
    int size = atoi(argv[1]);
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

    double time_1 = wtime();
    dgemm_blas(A, B, C, size);
    time_1 = wtime() - time_1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = (double) (rand() % 201 - 100);
            B[i][j] = (double) (rand() % 201 - 100);
            C[i][j] = 0.0;
        }
    }

    double time_2 = wtime();
    dgemm_opt(A, B, C, size);
    time_2 = wtime() - time_2;

    printf("Time(dgemm_blas) = %.2f sec\nTime(dgemm_opt) = %.2f sec\nSpeedup = %.2f\n", time_1, time_2, time_1 / time_2);
    free(A);
    free(B);
    free(C);
    return 0;
}