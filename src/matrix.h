#ifndef MATRIX_H
#define MATRIX_H

#include "tuples.h"

typedef struct Matrix {
    int dim;
    double **data;
} Matrix;

Matrix *matrix(int dim);
Matrix IdentityMatrix();
Matrix *gen_matrix_from_arr(double *a, int dim);
int mcompare(const Matrix *m1, const Matrix *m2);
Matrix *multiply_matrices(const Matrix *m1, const Matrix *m2);
Tuple multiply_matrix_with_tuple(const Matrix *m, const Tuple t);
Matrix *transpose(const Matrix *m);
double two_dim_determinant(const Matrix *m);
Matrix *submatrix(const Matrix *m, int row, int col);

#endif
