#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct thread_info {
    pthread_t thread;
    int tid;
    int num_threads;
    int size;
    double **A;
    double **B;
    double **C;
} thread_info;

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void *pthreads_dgemm_blas(void *arg) {
    thread_info *tinfo = arg;
    
    int start = tinfo->size / tinfo->num_threads * tinfo->tid;
    int end = (tinfo->tid + 1 != tinfo->size) ? (tinfo->size / tinfo->num_threads + start) : tinfo->size;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < tinfo->size; j++) {
            for (int k = 0; k < tinfo->size; k++) {
                tinfo->C[i][j] += tinfo->A[i][k] * tinfo->B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{   
    int tmp, size, num_threads;
    if (argc != 3) {
        printf("./(prog_name) (size) (num_threads)\n");
        return 1;
    }
    size = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    srand(time(NULL));
    thread_info tinfo[num_threads];
    
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

    for (int i = 0; i < num_threads; i++) {
        tinfo[i].tid = i;
        tinfo[i].num_threads = num_threads;
        tinfo[i].size = size;
        tinfo[i].A = A;
        tinfo[i].B = B;
        tinfo[i].C = C;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    double t = wtime();
    for (int i = 0; i < num_threads; i++) {
        tmp = pthread_create(&tinfo[i].thread, &attr, pthreads_dgemm_blas, (void *)&tinfo[i]);
        if (tmp != 0) {
            printf("Creating thread %d is failed\n", i);
            return 1;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        tmp = pthread_join(tinfo[i].thread, NULL);
        if (tmp != 0) {
            printf("Joining thread %d is failed", i);
            return 1;
        }
    }
    t = wtime() - t;

    printf("Time (%d threads) = %.2f sec\n", num_threads, t);
    free(A);
    free(B);
    free(C);
    return 0;
}