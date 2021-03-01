#include "matrix.h"

int main()
{
    srand(time(NULL));

    int p = 1, i, len = 3;

    while (1) {

        system("clear");
        /*printf("1. Matrix{0}\n");
        printf("2. Matrix{1}\n");
        printf("3. Matrix{main = 1}\n");
        printf("4. Matrix{rand}\n");
        printf("5. Matrix{my}\n");
        printf("0. Quit\n :");
        scanf("%d", &p);

        switch(p) {
            case 1:
                len = rand() % 3 + 3;
                break;
            case 2:
                len = rand() % 3 + 3;
                break;
            case 3:
                len = rand() % 3 + 3;
                break;
            case 4:
                len = rand() % 3 + 3;
                break;
            case 5:
                len = 3;
                break;
            case 0:
                return 0;
            }*/

        double **matrix;
        matrix = (double**)malloc(len * sizeof(double*));
        for (i = 0; i < len; i++) matrix[i] = (double*)malloc((len + 1) * sizeof(double));

        double **matrix2;
        matrix2 = (double**)malloc(len * sizeof(double*));
        for (i = 0; i < len; i++) matrix2[i] = (double*)malloc((len + 1) * sizeof(double));

        initMatrix(matrix, len, 6); 
        /*int check = gaussMatrix(matrix, len);
        if (check == 0) printAnswer(matrix, len);
        else printf("Неопределённость!\n");*/

        for (i = 0; i < len; i++) {
            for (int j = 0; j <= len; j++) {
                matrix2[i][j] = matrix[i][j];
            }
        }
        int eps;
        printf("Enter eps = ");
        scanf("%d", &eps);

        simple_it(matrix, len, eps);
        printf("-------------------------\n");
        method_Z(matrix2, len, eps);

        char ch;
        printf("Enter '0' to continue...");
        while ((ch = getchar()) != '0');
        free(matrix);
        free(matrix2);
    }
}