/**************************************************//**
* 定义常用矩阵操作
* author: zhou shi fu
******************************************************/
#ifndef _LABMATRIX_H_
#define _LABMATRIX_H_
#endif

//matrix A*B
int Matrix_X(const double *A, const double *B, int m, int n, int k, double *C);
//matrix A+B
int Matrix_A(const double *A, const double *B, int m, int n, double *C);
//matrix A-B
int Matrix_M(const double *A, const double *B, int m, int n, double *C);
