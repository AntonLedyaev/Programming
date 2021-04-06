#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

float Mx(float* x, float n);
float Mx2(float* x, float n);
float Mxy(float* x, float*y, float n);

void result(float* x, float* y, float n,FILE* out);

void main() {
	setlocale(LC_ALL, "RUS");
	int n;
	FILE* in = fopen("dat.txt ", "r+");
	FILE* out = fopen("dat1.txt ", "w+");

	if (in != NULL)
	{
		printf("in != null");
		fscanf(in, "%d", &n);
		float* x, * y;
		x = (float*)malloc(n * sizeof(float));
		for (int i = 0; i < n; i++)
		{
			fscanf(in, "%f", &x[i]);
		}

		y = (float*)malloc(n * sizeof(float));
		for (int i = 0; i < n; i++)
		{
			fscanf(in, "%f", &y[i]);
		}
		fprintf(out, "%.2f", Mx(x, n));

		fprintf(out, "\n");

		fprintf(out, "%.2f", Mx(y, n));
		fprintf(out, "\n");
		fprintf(out, "%.2f", Mx2(x, n));
		fprintf(out, "\n");
		fprintf(out, "%.2f", Mxy(x,y, n));
		fprintf(out, "\n");
		result(x, y, n, out);
		

	}
	else {
		printf("in == null");
	}
	system("pause");
}

float Mx(float* x, float n) {
	float s = 0;
	for (int i = 0; i < n; i++)
	{
		s += x[i];
	}
	return(1 / n * s);
}

float Mx2(float* x, float n) {
	float s = 0;
	for (int i = 0; i < n; i++)
	{
		s += x[i]*x[i];
	}
	return(1 / n * s);
}


float Mxy(float* x, float* y, float n) {
	float s = 0;
	for (int i = 0; i < n; i++)
	{
		s += x[i]+y[i];
	}
	return(1 / n * s);
}

void result(float* x, float* y, float n, FILE* out) {
	float A[2][2];
	A[0][0] = 1;
	A[0][1] = Mx(x, n);
	A[1][0] = Mx(x, n);
	A[1][1] = Mx2(x, n);

	float b[2];
	b[0] = Mx(y, n);
	b[1] = Mxy(x, y, n);

	float detA = A[0][0] * A[1][1] - A[0][1] * A[1][0];
	float inverseA[2][2];
	inverseA[0][0] = A[1][1] * (1 / detA);
	inverseA[0][1] = A[0][1] * (-1 / detA);
	inverseA[1][0] = A[1][0] * (-1 / detA);
	inverseA[1][1] = A[0][0] * (1 / detA);

	float a[2];
	 
	a[0] = inverseA[0][0] * b[0] + inverseA[0][1] * b[1];
	a[1] = inverseA[1][0] * b[0] + inverseA[1][1] * b[1];

	for (int i = 0; i < 2; i++)
	{
		fprintf(out, "\n");
		fprintf(out, "%.2f", a[i]);
	}
}


