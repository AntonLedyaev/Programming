#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


void trans(float[][40], float[][40], int); 
void cofac(float[][40], int); 
float determin(float[][40], int); 

int main() {
	setlocale(LC_ALL, "RUS");

	float matrix[40][40], deter;
	int a, b, n;
	printf("Введите порядок матрицы : ");
	scanf_s("%d", &n);
	
	printf("Введите элементы матрицы : \n");
	for (a = 0; a < n; ++a) {
		for (b = 0; b < n; ++b) {
			scanf_s("%f", &matrix[a][b]);
		}
	}
	deter = determin(matrix, n);
	printf("\n Определитель матрицы равен  : %f", deter);
	if (deter == 0) {
		printf("\n Определитель равен 0 -> невозможно найти обратную матрицу\n");
	} else { 
		cofac(matrix, n); 
	}
		
	return(0);
}

float determin(float matrix[40][40], int k) {
	float deter = 0.0, z = 1.0, mt[40][40];
	int a, b, c, x, y;
	if (k == 1)
	{
		return(matrix[0][0]);
	}
	else
	{
		deter = 0;
		for (a = 0; a < k; ++a) {
			x = 0;
			y = 0;
			for (b = 0; b < k; ++b) {
				for (c = 0; c < k; ++c) {
					mt[b][c] = 0;
					if ((b != 0) && (c != a))
					{
						mt[x][y] = matrix[b][c];
						if (y < (k - 2))
							y++;
						else
						{
							y = 0;
							x++;
						}
					}
				}
			}
			deter = deter + z * (matrix[0][a] * determin(mt, k - 1));
			z = -1 * z;
		}
	}
	return(deter);
}

void cofac(float comatr[40][40], int f) {
	float matr[40][40], cofact[40][40];
	int a, b, c, d, x, y;
	for (c = 0; c < f; ++c) {
		for (d = 0; d < f; ++d) {
			x = 0;
			y = 0;
			for (a = 0; a < f; ++a) {
				for (b = 0; b < f; ++b) {
					if (a != c && b != d)
					{
						matr[x][y] = comatr[a][b];
						if (y < (f - 2))
							y++;
						else
						{
							y = 0;
							x++;
						}
					}
				}
			}
			cofact[c][d] = pow(-1, c + d) * determin(matr, f - 1);
		}
	}
	trans(comatr, cofact, f);
}

void trans(float matr[40][40], float m1[40][40], int r) {
	float inv_matrix[40][40], tran[40][40], d;
	int a, b;
	for (a = 0; a < r; ++a) {
		for (b = 0; b < r; ++b) {
			tran[a][b] = m1[b][a];
		}
	}
	d = determin(matr, r);
	for (a = 0; a < r; ++a) {
		for (b = 0; b < r; ++b) {
			inv_matrix[a][b] = tran[a][b] / d;
		}
	}
	printf("\n\n\n Обратная матрица равна \n\n");
	for (a = 0; a < r; ++a) {
		for (b = 0; b < r; ++b)
			printf("\t%f", inv_matrix[a][b]);
		printf("\n\n");
	}
}