#include "lab5.h"

int main()
{
    int X; 

    printf("Enter X = ");
    scanf("%d", &X);

    double *mx = malloc(X * sizeof(double));
    double *my = malloc(X * sizeof(double));

    for (int i = 0; i < X; i++) {
        mx[i] = i;
        my[i] = function(i);
    }

    printf("Langrange = %.2f\n", Lagrange(mx, my, X));
    printf("Aitken = %.2f\n", Aitken(mx, my, X));
    printf("Newton = %.2f\n", Newton(mx, my, X));

    return 0;
}