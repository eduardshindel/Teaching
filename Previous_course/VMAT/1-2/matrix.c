#include "matrix.h"

void printMatrix(double **m, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= len; j++) {
            if (j == len) printf("|\t");
            printf("%.2f\t",m[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void initMatrix(double **m, int len, int p) {
    int i, j;
    switch (p) {
        case 1:
            for (i = 0; i < len; i++) {
                for (j = 0; j <= len; j++) {
                    m[i][j] = 0.0;
                }
            }
            break;
        case 2:
            for (i = 0; i < len; i++) {
                for (j = 0; j <= len; j++) {
                    m[i][j] = 1.0;
                }
            }
            break;
        case 3:
            for (i = 0, j = 0; i < len, j < len; i++, j++) {
                m[i][j] = 1.0;
            }
            for (i = 0; i < len; i++) {
                m[i][len] = (double)(rand() % 21 - 10);
            }
            break;
        case 4:
            for (i = 0; i < len; i++) {
                for (j = 0; j <= len; j++) {
                    m[i][j] = (double)(rand() % 21 - 10);
                }
            }
            break;
        case 5:
            for (i = 0; i < len; i++) {
                for (j = 0; j <= len; j++) {
                    scanf("%lf", &m[i][j]);
                }
            }
            break;
        case 6:
            m[0][0] = 9.0;
            m[0][1] = 3.0;
            m[0][2] = 1.0;
            m[0][3] = 14.0;
            m[1][0] = 2.0;
            m[1][1] = 10.0;
            m[1][2] = 1.0;
            m[1][3] = 13.0;
            m[2][0] = 5.0;
            m[2][1] = 1.0;
            m[2][2] = 8.0;
            m[2][3] = 16.0;
            break;
    }
    system("clear");
    printMatrix(m, len);
}

int maxElement(double **m, int len, int exp) {
    double max = 0.0;
    int max_len, i, j;
    for (i = exp, j = exp; i < len; i++) {
        if (fabs(m[i][j]) >= max) {
            max = fabs(m[i][j]);
            max_len = i;
        }
    }
    return max_len;
}
void printAnswer(double **m, int len) {
    for (int i = 0; i < len; i++) printf("x%d = %.2f\n", i + 1, m[i][len]);
}

int gaussMatrix(double **m, int len) {
    double dif;
    int turn = len - 1, exp = 0, i, j, NA = 0;

    while (turn) {
        int max_i = maxElement(m, len, exp);
        for (j = 0; j <= len; j++) {
            double temp = m[exp][j];
            m[exp][j] = m[max_i][j];
            m[max_i][j] = temp;
        }
        printMatrix(m, len);
        for (i = exp + 1; i < len; i++) {
            if (m[exp][exp] != 0.0) dif = m[i][exp] / m[exp][exp];
            else dif = 0.0, NA = 1;
            if (NA == 1) return 1;
            for (j = exp; j <= len; j++) {
                m[i][j] -= dif * m[exp][j];
            }
        }
        printMatrix(m, len);
        exp++;
        turn--;
    }
    for (i = exp; i >= 0; i--) {
        double sum = 0.0;
        for (j = exp + 1; j < len; j++) {
            sum += m[i][j];
        }
        m[i][j] -= sum;
        if (m[exp][exp] != 0.0) m[i][j] /= m[exp][exp];
        else m[i][j] = 0.0, NA = 1;
        if (NA == 1) return 1;
        for (int k = 0; k < len; k++) m[k][exp] *= m[i][j];
        exp--;
    }
    return 0;
}

double epsMatrix(int x) {
    double eps = 1.0;
    for (int i = 0; i < x; i++) eps /= 10;
    return eps;
}

int simple_it(double **m, int len, int eps) {
    printf("simple_it\n");
    double main = 0.0, dif = 0.0;
    int i, j, exp = 0, count = 0, n = 1;
    double *prev_m = malloc(len * sizeof(double));
    double *now_m = malloc(len * sizeof(double));

    for (i = 0; i < len; i++) {
        prev_m[i] = 0.0;
        now_m[i] = 0.0;
    }
    for (i = 0; i < len; i++) {
        main = m[exp][exp];
        for (j = 0; j <= len; j++) {
            m[i][j] /= main;
        }
        exp++;
    }
    dif = epsMatrix(eps);
    int k;
    for (i = 0, j = 0; i < len; i++, j++) m[i][j] = 0.0;
    while(n) {
        double time = 0.0;
        for (i = 0, j = len; i < len; i++) prev_m[i] = now_m[i];
        for (i = 0; i < len; i++) {
            for (j = 0; j < len; j++) {
                time += (m[i][j] * prev_m[j]);
            }
            now_m[i] = m[i][len] - time;
            time = 0.0;
        }
        k = 0;
        count++;
        for (i = 0, j = len; i < len; i++) {
            double pin = now_m[i] - prev_m[i];
            if (fabs(pin) < dif) k++;  
        }
        if (k == len) n = 0;
        if (count > 100) n = 0;
    }
    if (count > 100) printf("Невозможно решить!\n\n");
    else {
        printMatrix(m, len);
        for (i = 0; i < len; i++) printf("x%d = %.*f\n", i + 1, eps, now_m[i]);
        printf("\ncount = %d\n", count);
    }
    return 0;
}

int method_Z(double **m, int len, int eps) {
    printf("method_Z\n");
    double main = 0.0, dif = 0.0;
    int i, j, exp = 0, count = 0, n = 1;
    double *prev_m = malloc(len * sizeof(double));
    double *now_m = malloc(len * sizeof(double));

    for (i = 0; i < len; i++) {
        prev_m[i] = 0.0;
        now_m[i] = 0.0;
    }
    for (i = 0; i < len; i++) {
        main = m[exp][exp];
        for (j = 0; j <= len; j++) {
            m[i][j] /= main;
        }
        exp++;
    }
    dif = epsMatrix(eps);
    int k;
    for (i = 0, j = 0; i < len; i++, j++) m[i][j] = 0.0;
    while(n) {
        double time = 0.0;
        int exp = 0;
        for (i = 0, j = len; i < len; i++) prev_m[i] = now_m[i];
        for (i = 0; i < len; i++) {
            for (j = 0; j < len; j++) {
                if (j < exp) time += (m[i][j] * now_m[j]);
                else time += (m[i][j] * prev_m[j]);
            }
            exp++;
            now_m[i] = m[i][len] - time;
            time = 0.0;
        }
        k = 0;
        count++;
        for (i = 0, j = len; i < len; i++) {
            double pin = now_m[i] - prev_m[i];
            if (fabs(pin) < dif) k++;  
        }
        if (k == len) n = 0;
        if (count > 100) n = 0;
    }
    if (count > 100) printf("Невозможно решить!\n\n");
    else {
        printMatrix(m, len);
        for (i = 0; i < len; i++) printf("x%d = %.*f\n", i + 1, eps ,now_m[i]);
        printf("\ncount = %d\n", count);
    }
    return 0;
}