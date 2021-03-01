#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, commsize;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t = MPI_Wtime();

    int count = 1024;
    char *sbuf = malloc(sizeof(*sbuf) * count);
    sbuf[0] = rank;
    char *rbuf = mallocsizeof(*rbuf) * count);

    if(rank == 0) {
        for(int i = 0; i < commsize; i++) {
            size_t nbytes = count * sizeof(char);
            char *p = rbuf + i * nbytes;
            if(rank == i) memcpy(p, sbuf, nbytes);
            else MPI_Send(sbuf, count, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else MPI_Recv(rbuf, count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    t = MPI_Wtime() - t;
    double total_t = 0;
    MPI_Reduce(&t, &total_t, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    printf("%d process - %f\n",rank, t);

    if(rank == 0) printf("\nrank 0 feedback = %f", total_t);

    MPI_Finalize();
    return 0;
}