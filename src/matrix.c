#include <stdlib.h>
#include "matrix.h"
#include "utils.h"

Matrix *matrix(int dim) {
    Matrix *m = malloc(sizeof(Matrix));
    m->dim = dim;
    m->data = malloc(sizeof(double *) * dim);
    for (int i = 0; i < dim; i++) {
        m->data[i] = calloc(dim, sizeof(double));
    }
    return m;
}

int mcompare(const Matrix *m1, const Matrix *m2) {
    if (m1->dim != m2->dim) {
        return 1;
    }

    for (int i = 0; i < m1->dim; i++) {
        for (int j = 0; j < m1->dim; j++) {
            if (equals(m1->data[i][j], m2->data[i][j]) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

Matrix *multiply_matrices(const Matrix *m1, const Matrix *m2) {
    Matrix *p = matrix(4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double result = 0;
            for (int c = 0; c < 4; c++) {
                result += m1->data[i][c] * m2->data[c][j];
            }
            p->data[i][j] = result;
        }
    }
    return p;
}
