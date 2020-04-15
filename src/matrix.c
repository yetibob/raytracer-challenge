#include <math.h>
#include <stdlib.h>
#include "matrix.h"
#include "tuples.h"
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

Matrix *IdentityMatrix() {
    Matrix *idm = matrix(4);

    idm->data[0][0] = 1;
    idm->data[1][1] = 1;
    idm->data[2][2] = 1;
    idm->data[3][3] = 1;

    return idm; 
}

Matrix *gen_matrix_from_arr(double *a, int dim) {
    Matrix *m = matrix(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            m->data[i][j] = *a++;
        }
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

Tuple multiply_matrix_with_tuple(const Matrix *m, const Tuple t) {
    Tuple res = ztuple();
    for (int i = 0; i < 4; i++) {
        double result = 0;
        for (int j = 0; j < 4; j++) {
           result += m->data[i][j] * t[j];
        }
        res[i] = result;
    }
    return res;
}

Matrix *transpose(const Matrix *m) {
    Matrix *t = matrix(4);
    for (int i = 0; i < t->dim; i++) {
        for (int j = 0; j < t->dim; j++) {
            t->data[j][i] = m->data[i][j];
        }
    }
    return t;
}

double determinant(const Matrix *m) {
    double det = 0;
    if (m->dim == 2) {
        det = m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    }
    else {
        for (int col = 0; col < m->dim; col++) {
            det = det + m->data[0][col] * cofactor(m, 0, col); 
        }
    }
    return det;
}

Matrix *submatrix(const Matrix *m, int row, int col) {
    Matrix *res = matrix(m->dim - 1);
    int curRow = 0;
    int curCol = 0;
    for (int i = 0; i < res->dim; i++) {
        if (i == row) {
            curRow++;
        }
        for (int j = 0; j < res->dim; j++) { 
            if (j == col) {
                curCol++;
            }
            res->data[i][j] = m->data[curRow][curCol];
            curCol++;
        }
        curCol = 0;
        curRow++;
    }
    return res;
}

double minor(const Matrix *m, int row, int col) {
    Matrix *sub = submatrix(m, row, col);
    return determinant(sub);
} double cofactor(const Matrix *m, int row, int col) {
    double d = minor(m, row, col);
    if ((row + col) % 2 == 1) {
        d = -d;
    }
    return d;
}

Matrix *inverse(const Matrix *m) {
    if (equals(determinant(m), 0) == 0) {
        return NULL;
    }

    Matrix *i = matrix(m->dim);
    for (int row = 0; row < m->dim; row++) {
        for (int col = 0; col < m->dim; col++) {
            double c = cofactor(m, row, col);
            // this is worth calling out as a performance optimization
            // instead of doing something like i = transpose(i)
            // then looping through here and doing the division
            // we combine the operations as below
            i->data[col][row] = c / determinant(m);
        }
    }

    return i;
}

Matrix *translation(double x, double y, double z) {
    Matrix *m = IdentityMatrix();
    m->data[0][3] = x;
    m->data[1][3] = y;
    m->data[2][3] = z;
    return m;
}

Matrix *scaling(double x, double y, double z) {
    Matrix *m = IdentityMatrix();
    m->data[0][0] = x;
    m->data[1][1] = y;
    m->data[2][2] = z;
    return m;
}

Matrix *rotation_x(double radians) {
    Matrix *m = IdentityMatrix();
    m->data[1][1] = cos(radians);
    m->data[1][2] = -sin(radians);
    m->data[2][1] = sin(radians);
    m->data[2][2] = cos(radians);
    return m;
}

Matrix *rotation_y(double radians) {
    Matrix *m = IdentityMatrix();
    m->data[0][0] = cos(radians);
    m->data[0][2] = sin(radians);
    m->data[2][0] = -sin(radians);
    m->data[2][2] = cos(radians);
    return m;
}

Matrix *rotation_z(double radians) {
    Matrix *m = IdentityMatrix();
    m->data[0][0] = cos(radians);
    m->data[0][1] = -sin(radians);
    m->data[1][0] = sin(radians);
    m->data[1][1] = cos(radians);
    return m;
}

Matrix *shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
    Matrix *m = IdentityMatrix();
    m->data[0][1] = xy;
    m->data[0][2] = xz;
    m->data[1][0] = yx;
    m->data[1][2] = yz;
    m->data[2][0] = zx;
    m->data[2][1] = zy;
    return m;
}
