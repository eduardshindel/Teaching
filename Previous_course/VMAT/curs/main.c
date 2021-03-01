#include <stdio.h>
#include <math.h>

double const e = 2.71828;

double f(double x, double y) {
    return ((exp(x) + 2 * y + 3 * x) / 6);
}

double RK(double x, double y, double h) {
    double _y = y + h * f(x, y) / 2;
    double yy = y + h * f(x + h / 2, _y);
    return yy;
}

double integral(double b, double t){
    double hh = 0.002;
	double x = 0.0, y = 0.0, sum_1 = 0.0, sum_2 = 0.0;
	int k = 0;
	
	while(x <= (t - hh)) {
		k++;
		x = b + hh * k;
		y = RK(x, y, hh);
		if(k % 2 == 0) sum_2 += y;
		else sum_1 += y;
	}
	return ((RK(b, y, hh) + RK(t, y, hh) + 4 * sum_1 + 2 * sum_2) * hh / 3);
}

int main()
{
    double const h = 0.14319;
    double x = 1.0, y = 1.0;
    int count = 1;

    printf("\tКурсовая работа по дисциплине \"Вычислительная математика\"\n");
    printf("\tпо теме: \"Решение дифференциального уравнения методом\n");
    printf("\tРунге-Кутта 2-ого порядка с усреднением по времени\"\n");
    printf("Выполнил:\nст. гр. ИВ-823\nШиндель Э.Д.\n\n");
    printf("Проверил:\nассистент\nкафедры ПМиК\nПетухова Я.В.\n");
    printf("\t\t\tНовосибирск, 2020\n");
    
    printf("\t1 часть:\n");
    while (x < e) {
        y = RK(x, y, h);
        x += h;
        printf("%d. y(%.5f) = %.5f\n", count, x, y);
        count++;
    }
    
    x = y = 0.0;
    printf("\n\t2 часть:\n");
    for (x = 0.0; x <= 1.0; x += 0.2) {
        y = RK(x, y, 0.2);
        printf("y(%.2f) = %.2f\n", x, y);
    }

    printf("\n\t3 часть:\n");
    printf("Integral = %.5f\n", integral(0, 1));
    return 0;
}