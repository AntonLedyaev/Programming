#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

double det(int A[3][3]);
double detA(int A[3][3], int B[3]);
double detB(int A[3][3], int B[3]);
double detC(int A[3][3], int B[3]);
void setMatr(int A[3][3]);
void PrintMatr(int A[3][3]);

int main() {
	setlocale(LC_ALL, "RUS");

	int A[3][3];
	int B[3];
	printf("Введите коэффициенты при x:");
	setMatr(A);
	printf("Введите результаты");
	for (int i = 0; i < 3; i++)
	{
		scanf_s("%d", &B[i]);
	}
	printf("\nСоставленная матрица:\n");
	PrintMatr(A);
	printf("\nОпределитель матрицы x = %.2lf\n", det(A));
	if (det(A) != 0) {
		printf("\nОпределитель матрицы x1 = %.2lf\n", detA(A, B));
		printf("\nОпределитель матрицы x2 = %.2lf\n", detB(A, B));
		printf("\nОпределитель матрицы x3 = %.2lf\n", detC(A, B));

		printf("x1 = %.2lf\n", (detA(A, B) / det(A)));
		printf("x2 = %.2lf\n", (detB(A, B) / det(A)));
		printf("x3 = %.2lf\n", (detC(A, B) / det(A)));
	}
	else {
		printf("Определитель равен нулю => Система имеет бесконечное количество решений либо несовместна.");
	}


	system("pause");
	return 0;
}

double det(int A[3][3])
{
	return (A[0][0] * A[1][1] * A[2][2] +
		A[0][1] * A[1][2] * A[2][0] +
		A[1][0] * A[2][1] * A[0][2] -
		A[2][0] * A[1][1] * A[0][2] -
		A[1][0] * A[0][1] * A[2][2] -
		A[2][1] * A[1][2] * A[0][0]);
}

double detA(int A[3][3], int B[3]) {
	return (B[0] * A[1][1] * A[2][2] +
		A[0][1] * A[1][2] * B[2] +
		B[1] * A[2][1] * A[0][2] -
		B[2] * A[1][1] * A[0][2] -
		B[1] * A[0][1] * A[2][2] -
		A[2][1] * A[1][2] * B[0]);
}

double detB(int A[3][3], int B[3]) {


	return (A[0][0] * B[1] * A[2][2] +
		B[0] * A[1][2] * A[2][0] +
		A[1][0] * B[2] * A[0][2] -
		A[2][0] * B[1] * A[0][2] -
		A[1][0] * B[0] * A[2][2] -
		B[2] * A[1][2] * A[0][0]);
}

double detC(int A[3][3], int B[3]) {
	return (A[0][0] * A[1][1] * B[2] +
		A[0][1] * B[1] * A[2][0] +
		A[1][0] * A[2][1] * B[0] -
		A[2][0] * A[1][1] * B[0] -
		A[1][0] * A[0][1] * B[2] -
		A[2][1] * B[1] * A[0][0]);
}

void setMatr(int A[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf_s("%d", &A[i][j]);
		}
	}
}

void PrintMatr(int A[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}