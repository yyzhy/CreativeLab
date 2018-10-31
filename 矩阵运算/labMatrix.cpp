#include "stdafx.h"
#include "labMatrix.h"

int Matrix_X(const double *A, const double *B, int m, int n, int k, double *C)
{
	int i, j, l, u;
	for (j = 0; j < m; j++)
	{
		for (i = 0; i < k; i++)
		{
			u = j*k + i;
			C[u] = 0;
			for (l = 0; l < n; l++)
			{
				C[u] = C[u] + A[j*n+l] * B[l*k+i];
			}
		}
	}
	return 0;
}

int Matrix_A(const double *A, const double *B, int m, int n, double *C)
{
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			C[j*n + i] = A[j*n + i] + B[j*n + i];
		}
	}
	return 0;
}

int Matrix_M(const double *A, const double *B, int m, int n, double *C)
{
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			C[j*n + i] = A[j*n + i] - B[j*n + i];
		}
	}
	return 0;
}
