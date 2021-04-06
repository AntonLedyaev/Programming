#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct complex {
	double re;
	double im;
};

void summ(double a, double b, double c, double d ) {
	printf("z = (%.2f, %.2fi)", a + c, b + d);
};

void difference(double a, double b, double c, double d) {
	printf("z = (%.2f, %.2fi)", a - c, b - d);
};

void multiplication(double a, double b, double c, double d) {
	double real = a * c - b * d;
	double image = a * d + c * b;
	printf("z = (%.2f; %.2fi)", real, image);
}

void division(double a, double b, double c, double d) {
	double real = (a * c + b * d)/(c * c + d * d);
	double image = (b * c - a * d )/(c * c + d * d);
	printf("z = (%.2f; %.2fi)", real, image);
}

void main() {
	setlocale(LC_ALL, "RUS");
	struct complex comp1, comp2;
	printf("������� ������������ ����� ������� �����: ");
	scanf_s("%lf", &comp1.re);
	printf("������� ������ ����� ������� �����: ");
	scanf_s("%lf", &comp1.im);
	printf("������� ������������ ����� ������� �����: ");
	scanf_s("%lf", &comp2.re);
	printf("������� ������ ����� ������� �����: ");
	scanf_s("%lf", &comp2.im);

	printf("����� �������� �� ������ �������?\n1 - ��������\n2 - ���������\n3 - ���������\n4 - �������\n");
	int p;
	scanf_s("%d", &p);
	if (p == 1) {
		summ(comp1.re, comp1.im, comp2.re, comp2.im);
	}
	else if (p == 2) {
		difference(comp1.re, comp1.im, comp2.re, comp2.im);
	}
	else if (p == 3) {
		multiplication(comp1.re, comp1.im, comp2.re, comp2.im);
	}
	else if (p == 4) {
		division(comp1.re, comp1.im, comp2.re, comp2.im);
	}
	else {
		printf("������� �������� �����.");
	}

	system("pause");
}