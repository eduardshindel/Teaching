#include <stdio.h>
#include <math.h>
#include <omp.h>

double func(double x) {
    return (log(1.0 + x) / x);
}

int main()
{
    const double eps = 1E-5;
    const double a = 0.1;
    const double b = 1.0;
    const int n0 = 100000000;
    double sq[2];
    
    printf("Numerical integration: [%f, %f], n0 = %d, EPS = %f\n", a, b, n0, eps);
    
    double t = omp_get_wtime();
    #pragma omp parallel
    {
        int n = n0, k;
        double delta = 1;
        for (k = 0; delta > eps; n *= 2, k ^= 1) {
            double h = (b - a) / n;
            double s = 0.0;
            sq[k] = 0;
            #pragma omp barrier // Ждем пока все потоки закончат обнуление sq[k]
            
            #pragma omp for nowait
            for (int i = 0; i < n; i++)
            s += func(a + h * (i + 0.5));
            
            #pragma omp atomic
            sq[k] += s * h; // Ждем пока все потоки обновят sq[k]
            #pragma omp barrier
            
            if (n > n0) delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
        }
            #pragma omp master
            printf("Result Pi: %.12f; Runge rule: EPS %e, n %d\n", sq[k] * sq[k], eps, n / 2);
    }
    t = omp_get_wtime() - t;
    printf("Elapsed time (sec.): %.6f\n", t);
    
    return 0;
}