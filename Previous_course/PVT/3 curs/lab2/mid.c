#include <stdio.h>
#include <math.h>
#include <mpi.h>

const double eps = 1E-6;
const int n0 = 100000000;
const double a = 1.0;
const double b = 2.0;

double func(double x)
{
    return ((1 - exp(0.7 / x)) / (2 + x));
}

int main(int argc, char **argv)
{
    int commsize, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int n = n0, k;
    double sq[2], delta = 1;

    double t = MPI_Wtime();
    for (k = 0; delta > eps; n *= 2, k ^= 1) {
        int points_per_proc = n / commsize;
        int lb = rank * points_per_proc;
        int ub = (rank == commsize - 1) ? (n - 1) : (lb + points_per_proc - 1);
        double h = (b - a) / n;
        
        double s = 0.0;
        for (int i = lb; i <= ub; i++) s += func(a + h * (i + 0.5));
        MPI_Allreduce(&s, &sq[k], 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        sq[k] *= h;
        if (n > n0) delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
    }

    if (rank == 0) {
        t = MPI_Wtime() - t;
        printf("Result Pi: %.12f; Runge rule: EPS %e, n %d\n", sq[k] * sq[k], eps, n / 2);
        printf("Time (%d proc) = %.6fs\n", commsize, t);
    }

    MPI_Finalize();
    return 0;
}