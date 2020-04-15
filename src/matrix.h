#ifndef MATRIX_H
#define MATRIX_H

#include "tuples.h"

typedef struct Matrix {
    int dim;
    double **data;
} Matrix;

Matrix *matrix(int dim);
Matrix *IdentityMatrix();
Matrix *gen_matrix_from_arr(double *a, int dim);
int mcompare(const Matrix *m1, const Matrix *m2);
Matrix *multiply_matrices(const Matrix *m1, const Matrix *m2);
Tuple multiply_matrix_with_tuple(const Matrix *m, const Tuple t);
Matrix *transpose(const Matrix *m);
double determinant(const Matrix *m);
Matrix *submatrix(const Matrix *m, int row, int col);
double minor(const Matrix *m, int row, int col);
double cofactor(const Matrix *m, int row, int col);
Matrix *inverse(const Matrix *m);
Matrix *translation(double x, double y, double z);
Matrix *scaling(double x, double y, double z);
Matrix *rotation_x(double radians);
Matrix *rotation_y(double radians);
Matrix *rotation_z(double radians);
Matrix *shearing(double xy, double xz, double yx, double yz, double zx, double zy);
#endif
