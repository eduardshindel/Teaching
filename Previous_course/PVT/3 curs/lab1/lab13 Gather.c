#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    int rank, commsize;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t = MPI_Wtime();

    int count = 1024;
    char *sbuf = malloc(sizeof(*sbuf) * count);
    sbuf[0] = rank;
    char *rbuf = malloc(sizeof(*rbuf) * count * commsize);

    if (rank == 0) {
      size_t nbytes = count * sizeof(char);
      for (int i = 0; i < commsize; i++) {
        if (rank == i) memcpy(rbuf, sbuf, nbytes);
        else {
          MPI_Status status;
          MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
          char* p = rbuf + nbytes * status.MPI_SOURCE;
          MPI_Recv(p, count, MPI_CHAR, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &status);
        }
      }
    } else MPI_Send(sbuf, count, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

    t = MPI_Wtime() - t;
    double total_t = 0;
    MPI_Reduce(&t, &total_t, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    printf("\n%d process - %f\n",rank, t);

    if (rank == 0) printf("\nrank 0 feedback = %f\n", total_t);
    
    MPI_Finalize();
    return 0;
}
