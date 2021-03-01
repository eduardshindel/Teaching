#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, commsize;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t = MPI_Wtime();

    int count = 1;
    char *sbuf = malloc(sizeof(*sbuf) * count);
    sbuf[0] = rank;
    char *rbuf = malloc(sizeof(*rbuf) * count);

    int left = (rank - 1 + commsize) % commsize;
    int right = (rank + 1) % commsize;

    for (int i = 0; i < commsize; i++) {
        MPI_Status s[2];
        MPI_Request reqs[2];
        MPI_Isend(sbuf, count, MPI_CHAR, right, 0, MPI_COMM_WORLD, &reqs[0]);
        MPI_Irecv(rbuf, count, MPI_CHAR, left, 0, MPI_COMM_WORLD, &reqs[1]);

        MPI_Waitall(2, reqs, s);

        char *p = sbuf;
        sbuf = rbuf;
        rbuf = p;
    } 

    t = MPI_Wtime() - t;
    printf("ring communication scheme - %f\n", t);

    MPI_Finalize();
    return 0;
}
