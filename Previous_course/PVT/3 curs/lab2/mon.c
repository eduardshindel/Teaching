#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

const double PI = 3.14159265358979323846;
const int n = 10000000;

double getrand()
{ 
    int r = rand();
    while (r == 0 || r == RAND_MAX) r = rand();
    return (double)r / RAND_MAX;
}

double func(double x, double y)
{ 
    return x / pow(y, 2); 
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    
    srand(rank);
    int in = 0;
    double s = 0.0;

    double t = MPI_Wtime();
    for (int i = rank; i < n; i += commsize) {
        double x = getrand(); /* x in (0, 1) */
        double y = getrand() * 5; /* y in (2, 5) */
        if ((y > 2) && (y < 5)) {
            in++;
            s += func(x, y);
        }
    }
    int gin = 0;
    MPI_Reduce(&in, &gin, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    double gsum = 0.0;
    MPI_Reduce(&s, &gsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double v = PI * gin / n;
        double res = v * gsum / gin;
        t = MPI_Wtime() - t;
        printf("Result: %.12f, n %d\n", res, n);
        printf("Time (%d proc) = %.6fs\n", commsize, t);
    }
    MPI_Finalize();
    return 0;
}