#include <assert.h>
#include <stdio.h>
#include "../src/matrix.h"
#include "../src/utils.h"
#include "../src/tuples.h"

void display_matrix(Matrix m) {
    for (int i = 0; i < m.dim; i++) {
        for (int j = 0; j < m.dim; j++) {
            printf("%f ", m.data[i][j]);
        }
        printf("\n");
    }
}

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
   assert(mcompare(expected, p) == 0);
}

void test_multiply_matrix_by_tuple() {
    double a[16] = { 1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1 };
    Matrix *m = gen_matrix_from_arr(a, 4);
    Tuple t1 = point(1, 2, 3);
    Tuple result = multiply_matrix_with_tuple(m ,t1);
    Tuple e = point(18, 24, 33);
    assert(is_equal(e, result) == 0);
}

void test_multiply_matrix_by_identity_matrix() {
    double a1[] = { 0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32 };
    Matrix *m = gen_matrix_from_arr(a1, 4);
    Matrix id = IdentityMatrix();

    Matrix *result = multiply_matrices(m, &id);
    assert(mcompare(m, result) == 0);
}

void test_multiply_tuple_by_identity_matrix() {
    Matrix id = IdentityMatrix();
    Tuple t = point(1, 2, 3);
    t[3] = 4;
    Tuple result = multiply_matrix_with_tuple(&id, t);
    assert(is_equal(t, result) == 0);
}

void test_transpose_matrix() {
    double arr[] = { 0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8 };
    Matrix *m = gen_matrix_from_arr(arr, 4);

    double earr[] = { 0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8 };
    Matrix *e = gen_matrix_from_arr(earr, 4);

    Matrix *transposed = transpose(m);
    assert(mcompare(e, transposed) == 0);
}

void test_transpose_identity_matrix() {
    Matrix m = IdentityMatrix();
    assert(mcompare(&m, transpose(&m)) == 0);
}

void test_find_determinant_2_dim_matrix() {
    double arr[] = { 1 , 5, -3, 2 };
    Matrix *m = gen_matrix_from_arr(arr, 2);

    double e = 17;
    double res = determinant(m);
    assert(equals(e, res) == 0);
}

void test_get_submatrix() {
    double a1[] = { 1, 5, 0, -3, 2, 7, 0, 6, -3 };
    Matrix *m1 = gen_matrix_from_arr(a1, 3);
    Matrix *sub1 = submatrix(m1, 0, 2);

    double e1a[] = { -3, 2, 0, 6};
    Matrix *e1 = gen_matrix_from_arr(e1a, 2); 
    assert(mcompare(e1, sub1) == 0);

    double a2[] = { -6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    Matrix *m2 = gen_matrix_from_arr(a2, 4);
    Matrix *sub2 = submatrix(m2, 2, 1);

    double e2a[] = { -6, 1, 6, -8, 8, 6, -7, -1, 1};
    Matrix *e2 = gen_matrix_from_arr(e2a, 3);
    assert(mcompare(e2, sub2) == 0);
}

void test_get_minor() {
    double a1[] = { 3, 5, 0, 2, -1, -7, 6, -1, 5 };
    Matrix *m = gen_matrix_from_arr(a1, 3);
    Matrix *b = submatrix(m, 1, 0);
    double d1 = determinant(b);
    assert(equals(d1, 25) == 0);
    double d2 = minor(m, 1, 0);
    assert(equals(d1, d2) == 0);
}

void test_get_cofactor() {
    double a[] = { 3, 5, 0, 2, -1, -7, 6, -1, 5 };
    Matrix *m = gen_matrix_from_arr(a, 3);
    double minor1 = minor(m, 0, 0);
    assert(equals(-12, minor1) == 0);
    double cofactor1 = cofactor(m, 0, 0);
    assert(equals(-12, cofactor1) == 0);

    double minor2 = minor(m, 1, 0);
    assert(equals(25, minor2) == 0);
    double cofactor2 = cofactor(m, 1, 0);
    assert(equals(-25, cofactor2) == 0);
}

int main() {
    test_create_matrix();
    test_compare_matrices();
    test_multiply_matrices();
    test_multiply_matrix_by_tuple();
    test_multiply_matrix_by_identity_matrix();
    test_multiply_tuple_by_identity_matrix();
    test_transpose_matrix();
    test_transpose_identity_matrix();
    test_find_determinant_2_dim_matrix();
    test_get_submatrix();
    test_get_minor();
    test_get_cofactor();
}
