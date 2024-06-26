#include <math.h>
#include <stdlib.h>

#include "matrix.hpp"
#include "tuples.hpp"
#include "utils.hpp"

Matrix* matrix(int dim) {
    Matrix* m = malloc(sizeof(Matrix));
    m->dim    = dim;
    m->data   = malloc(sizeof(double*) * dim);
    for (int i = 0; i < dim; i++) {
        m->data[i] = calloc(dim, sizeof(double));
    }
    return m;
}

void matrix_destroy(Matrix* m) {
    for (int i = 0; i < m->dim; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void matrix_init(Matrix* m, int dim) {
    m->dim  = dim;
    m->data = malloc(sizeof(double*) * dim);
    for (int i = 0; i < dim; i++) {
        m->data[i] = calloc(dim, sizeof(double));
    }
}

void matrix_free(Matrix* m) {
    for (int i = 0; i < m->dim; i++) {
        free(m->data[i]);
    }
    free(m->data);
}

Matrix* matrix_IdentityMatrix() {
    Matrix* idm = matrix(4);

    idm->data[0][0] = 1;
    idm->data[1][1] = 1;
    idm->data[2][2] = 1;
    idm->data[3][3] = 1;

    return idm;
}

Matrix* matrix_gen(double* a, int dim) {
    Matrix* m = matrix(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            m->data[i][j] = *a++;
        }
    }
    return m;
}

int matrix_compare(const Matrix* m1, const Matrix* m2) {
    if (m1->dim != m2->dim) {
        return 0;
    }

    for (int i = 0; i < m1->dim; i++) {
        for (int j = 0; j < m1->dim; j++) {
            if (!equals(m1->data[i][j], m2->data[i][j])) {
                return 0;
            }
        }
    }
    return 1;
}

Matrix* matrix_multiply(const Matrix* m1, const Matrix* m2) {
    Matrix* p = matrix(4);
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

void matrix_multiply_tuple(const Matrix* m, const Tuple t, Tuple res) {
    for (int i = 0; i < 4; i++) {
        double result = 0;
        for (int j = 0; j < 4; j++) {
            result += m->data[i][j] * t[j];
        }
        res[i] = result;
    }
}

Matrix* matrix_transpose(const Matrix* m) {
    Matrix* t = matrix(4);
    for (int i = 0; i < t->dim; i++) {
        for (int j = 0; j < t->dim; j++) {
            t->data[j][i] = m->data[i][j];
        }
    }
    return t;
}

double matrix_determinant(const Matrix* m) {
    double det = 0;

    if (m->dim == 2) {
        det = m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    } else {
        for (int col = 0; col < m->dim; col++) {
            det = det + m->data[0][col] * matrix_cofactor(m, 0, col);
        }
    }
    return det;
}

Matrix* matrix_sub(const Matrix* m, int row, int col) {
    Matrix* res    = matrix(m->dim - 1);
    int     curRow = 0;
    int     curCol = 0;
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

double matrix_minor(const Matrix* m, int row, int col) {
    Matrix* sub = matrix_sub(m, row, col);
    double  det = matrix_determinant(sub);
    matrix_destroy(sub);
    return det;
}

double matrix_cofactor(const Matrix* m, int row, int col) {
    double d = matrix_minor(m, row, col);
    if ((row + col) % 2 == 1) {
        d = -d;
    }
    return d;
}

Matrix* matrix_inverse(const Matrix* m) {
    if (equals(matrix_determinant(m), 0)) {
        return NULL;
    }

    Matrix* i = matrix(m->dim);
    for (int row = 0; row < m->dim; row++) {
        for (int col = 0; col < m->dim; col++) {
            double c = matrix_cofactor(m, row, col);
            // this is worth calling out as a performance optimization
            // instead of doing something like i = transpose(i)
            // then looping through here and doing the division
            // we combine the operations as below
            i->data[col][row] = c / matrix_determinant(m);
        }
    }

    return i;
}

Matrix* matrix_translation(double x, double y, double z) {
    Matrix* m     = matrix_IdentityMatrix();
    m->data[0][3] = x;
    m->data[1][3] = y;
    m->data[2][3] = z;
    return m;
}

Matrix* matrix_scaling(double x, double y, double z) {
    Matrix* m     = matrix_IdentityMatrix();
    m->data[0][0] = x;
    m->data[1][1] = y;
    m->data[2][2] = z;
    return m;
}

Matrix* matrix_rotation_x(double radians) {
    Matrix* m     = matrix_IdentityMatrix();
    m->data[1][1] = cos(radians);
    m->data[1][2] = -sin(radians);
    m->data[2][1] = sin(radians);
    m->data[2][2] = cos(radians);
    return m;
}

Matrix* matrix_rotation_y(double radians) {
    Matrix* m     = matrix_IdentityMatrix();
    m->data[0][0] = cos(radians);
    m->data[0][2] = sin(radians);
    m->data[2][0] = -sin(radians);
    m->data[2][2] = cos(radians);
    return m;
}

Matrix* matrix_rotation_z(double radians) {
    Matrix* m     = matrix_IdentityMatrix();
    m->data[0][0] = cos(radians);
    m->data[0][1] = -sin(radians);
    m->data[1][0] = sin(radians);
    m->data[1][1] = cos(radians);
    return m;
}

Matrix* matrix_shearing(double xy, double xz, double yx, double yz, double zx, double zy) {
    Matrix* m     = matrix_IdentityMatrix();
    m->data[0][1] = xy;
    m->data[0][2] = xz;
    m->data[1][0] = yx;
    m->data[1][2] = yz;
    m->data[2][0] = zx;
    m->data[2][1] = zy;
    return m;
}
