#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    int dim;
    double **data;
} Matrix;

Matrix *matrix(int dim);
int mcompare(const Matrix *m1, const Matrix *m2);
Matrix *multiply_matrices(const Matrix *m1, const Matrix *m2);

#endif
