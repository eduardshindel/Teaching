#include <stdio.h>
#include <stdlib.h>

void print_matrix(float **m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.1f ", m[i][j]);
        }
        printf("\n");
    }
}

void transpose_matrix(float **m, int n) {
    int main_diagonal = 1;
    for (int i = 0; i < n; i++, main_diagonal++) {
        for (int j = main_diagonal; j < n; j++) {
            float buf = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = buf;
        }
    }
}

int main()
{
    float **m, count = 1.0;
    int n;

    printf("Enter n = ");
    scanf("%d", &n);

    m = (float **) malloc(sizeof(float *) * n);
    for (int i = 0; i < n; i++) m[i] = (float *) malloc(sizeof(float) * n);

    for (int i = 0; i < n; i++, count += 1.0) {
        for (int j = 0; j < n; j++) {
            m[i][j] = count;
        }
    }
    print_matrix(m, n);
    printf("\n///////////////result///////////////\n\n");
    transpose_matrix(m, n);
    print_matrix(m, n);

    return 0;
}