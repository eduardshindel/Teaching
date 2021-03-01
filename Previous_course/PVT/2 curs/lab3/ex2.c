#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double getrand(unsigned int *seed) {
    return (double)rand_r(seed) / RAND_MAX;
}

double func(double x, double y) {
    return exp(pow(x + y, 2));
}

int main()
{
    const int n = 100000000;
    printf("Numerical integration by Monte Carlo method: n = %d\n", n);
    int in = 0;
    double s = 0;
    
    double t = omp_get_wtime();
    #pragma omp parallel
    {
        double s_loc = 0;
        int in_loc = 0;
        unsigned int seed = omp_get_thread_num(); 
        
        #pragma omp for nowait
        for (int i = 0; i < n; i++) {
            double x = getrand(&seed);           /* x in (0, 1) */
            double y = getrand(&seed) * (1 - x); /* y in (0, 1 - x) */
            if ((y < 1 - x) && (y > 0) && (x > 0) && (x < 1)) {
                in_loc++;
                s_loc += func(x, y);
            }
        }

        #pragma omp atomic
        s += s_loc;

        #pragma omp atomic
        in += in_loc;

    }
    double v = in / n;
    double res = v * s / in;
    t = omp_get_wtime() - t;
    
    printf("Result: %.12f, n %d\n", res, n);
    printf("Elapsed time (sec.): %.6f\n", t);
        
    return 0;
}
