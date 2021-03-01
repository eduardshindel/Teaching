#include <time.h>
#include "matrix.h"
#include "pagerank.h"

int main()
{   
    srand(time(NULL));
    int n = 1000;

    double t = omp_get_wtime();
    page_rank(n);
    t = omp_get_wtime() - t;

    printf("Time: %.6f\n", t);

    return 0;
}