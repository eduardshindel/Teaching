#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int count = 1024;
    char *sbuf = malloc(sizeof(*sbuf) * count);
    sbuf[0] = rank;
    char *rbuf = malloc(sizeof(*rbuf) * count * size);

    MPI_Status *stat = malloc(sizeof(*stat) * 2 * (size -1));
    MPI_Request *reqs = malloc(sizeof(*stat) * 2  * (size -1));
    int nreqs = 0;
    double t = MPI_Wtime();
    for (int i = 0; i < size; i++) {
        char *ptr = rbuf + count * sizeof(char) * i;
        if (i != rank) {
            MPI_Isend(sbuf, count, MPI_CHAR, i, 0, MPI_COMM_WORLD, &reqs[nreqs++]);
            MPI_Irecv(ptr, count, MPI_CHAR, i, 0, MPI_COMM_WORLD, &reqs[nreqs++]);
        } else memcpy(ptr, sbuf, count);
    }
    MPI_Waitall(nreqs, reqs, stat);
    t = MPI_Wtime() - t;

    double total_t = 0;
    MPI_Reduce(&t, &total_t, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    printf("\n%d process - %f\n",rank, t);

    if (rank == 0) {
        printf("\nrank 0 feedback = %f", total_t);
    }
    free(reqs);
    free(stat);
    MPI_Finalize();
    return 0;
}
