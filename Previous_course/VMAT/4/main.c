#include "lab4.h"

int main()
{
    double x, y;
    int e;

    printf("Enter x: ");
    scanf("%lf", &x);
    printf("Enter y: ");
    scanf("%lf", &y);
    printf("Enter e: ");
    scanf("%d", &e);
    Newton(e, x, y);

    return 0;
}