#include <assert.h>
#include "../src/matrix.h"
#include "../src/utils.h"
#include "tutils.h"

void test_create_matrix() {
    Matrix *m = matrix(2);
    double **data = m->data;
    assert(equals(0, data[0][0]) == 0);
    assert(equals(0, data[0][1]) == 0);
    assert(equals(0, data[1][0]) == 0);
    assert(equals(0, data[1][1]) == 0);
}

void test_compare_matrices() {
    Matrix *m1 = matrix(4);
    Matrix *m2 = matrix(4);

    int val = 1;
    for (int i = 0; i < m1->dim; i++) {
        for (int j = 0; j < m1->dim; j++) {
            m1->data[i][j] = val;
            m2->data[i][j] = val;
        }
    }

    assert(mcompare(m1, m2) == 0);
}

void test_multiply_matrices() {
   double a1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2 };
   double a2[16] = { -2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8 };

   Matrix *m1 = gen_matrix_from_arr(a1, 4);
   Matrix *m2 = gen_matrix_from_arr(a2, 4);

   double a3[16] = { 20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42 };
   Matrix *expected = gen_matrix_from_arr(a3, 4);

   Matrix *p = multiply_matrices(m1, m2);
   assert(mcompare(p, expected) == 0);
}

int main() {
    test_create_matrix();
    test_compare_matrices();
    test_multiply_matrices();
}
