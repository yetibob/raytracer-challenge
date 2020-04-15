#include <assert.h>
#include <math.h>
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
    assert(tcompare(e, result) == 0);
}

void test_multiply_matrix_by_identity_matrix() {
    double a1[] = { 0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32 };
    Matrix *m = gen_matrix_from_arr(a1, 4);

    Matrix *result = multiply_matrices(m, IdentityMatrix());
    assert(mcompare(m, result) == 0);
}

void test_multiply_tuple_by_identity_matrix() {
    Tuple t = point(1, 2, 3);
    t[3] = 4;
    Tuple result = multiply_matrix_with_tuple(IdentityMatrix(), t);
    assert(tcompare(t, result) == 0);
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
    Matrix *id = IdentityMatrix();
    assert(mcompare(id, transpose(id)) == 0);
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

void test_find_determinant_3_4_dim_matrix() {
    double arr1[] = { 1, 2, 6, -5, 8, -4, 2, 6, 4 };
    Matrix *m3 = gen_matrix_from_arr(arr1, 3);

    assert(equals(56,   cofactor(m3, 0, 0)) == 0);
    assert(equals(12,   cofactor(m3, 0, 1)) == 0);
    assert(equals(-46,  cofactor(m3, 0, 2)) == 0);
    assert(equals(-196, determinant(m3))    == 0);

    double arr2[] = { -2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9 };
    Matrix *m4 = gen_matrix_from_arr(arr2, 4);

    assert(equals(690,   cofactor(m4, 0, 0)) == 0);
    assert(equals(447,   cofactor(m4, 0, 1)) == 0);
    assert(equals(210,   cofactor(m4, 0, 2)) == 0);
    assert(equals(51,    cofactor(m4, 0, 3)) == 0);
    assert(equals(-4071, determinant(m4))    == 0);
}

void test_invert_matrix() {
    double a1[] = { -5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4 };
    Matrix *m1 = gen_matrix_from_arr(a1, 4);

    Matrix *m2 = inverse(m1);
    assert(equals(determinant(m1), 532) == 0);
    assert(equals(cofactor(m1, 2, 3), -160) == 0);
    assert(equals(m2->data[3][2], -160.0/532.0) == 0);
    assert(equals(cofactor(m1, 3, 2), 105) == 0);
    assert(equals(m2->data[2][3], 105.0/532.0) == 0);

    double a2[] = { 0.21805, 0.45113, 0.24060, -0.04511, -0.80827, -1.45677, -0.44361, 0.52068, -0.07895, -0.22368, -0.05263, 0.19737, -0.52256, -0.81391, -0.30075, 0.30639 };
    Matrix *e = gen_matrix_from_arr(a2, 4);
    assert(mcompare(e, m2) == 0);
}

void test_more_matrix_inversions() {
    double a1[] = { 8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4 };
    double a2[] = { 9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2 };
    Matrix *m1 = gen_matrix_from_arr(a1, 4);
    Matrix *m2 = gen_matrix_from_arr(a2, 4);

    Matrix *i1 = inverse(m1);
    Matrix *i2 = inverse(m2);

    double ea1[] = { -0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308 };
    double ea2[] = { -0.04074, -0.07778, 0.14444, -0.22222, -0.07778, 0.03333, 0.36667, -0.33333, -0.02901, -0.14630, -0.10926, 0.12963, 0.17778, 0.06667, -0.26667, 0.33333 };
    Matrix *e1 = gen_matrix_from_arr(ea1, 4);
    Matrix *e2 = gen_matrix_from_arr(ea2, 4);

    assert(mcompare(e1, i1) == 0);
    assert(mcompare(e2, i2) == 0);
}

void test_multiply_product_by_its_inverse() {
    double a1[] = { 3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1 };
    double a2[] = { 8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5 };

    Matrix *m1 = gen_matrix_from_arr(a1, 4);
    Matrix *m2 = gen_matrix_from_arr(a2, 4);

    Matrix *m3 = multiply_matrices(m1, m2);
    assert(mcompare(multiply_matrices(m3, inverse(m2)), m1) == 0);
}

void test_multiply_point_by_translation_matrix() {
    Matrix *m = translation(5, -3, 2);
    Tuple p = point(-3, 4, 5);
    Tuple transformed = multiply_matrix_with_tuple(m, p);

    Tuple expected = point(2, 1, 7);
    assert(tcompare(transformed, expected) == 0); 
}

void test_multiply_point_by_translation_inverse() {
    Matrix *m = inverse(translation(5, -3, 2));
    Tuple p = point(-3, 4, 5);
    Tuple transformed = multiply_matrix_with_tuple(m, p);
    
    Tuple expected = point(-8, 7, 3);
    assert(tcompare(transformed, expected) == 0);
}

void test_multiply_vector_by_translation_does_nothing() {
    Matrix *m = translation(5, -3, 2);
    Tuple v = vector(-3, 4, 5);
    
    Tuple transformed = multiply_matrix_with_tuple(m, v);
    assert(tcompare(transformed, v) == 0);
}

void test_scale_matrix_applied_to_point() {
    Matrix *m = scaling(2, 3, 4);
    Tuple p = point(-4, 6, 8);
    Tuple scaled = multiply_matrix_with_tuple(m, p);
    Tuple expected = point(-8, 18, 32);
    assert(tcompare(expected, scaled) == 0);
}

void test_scale_matrix_applied_to_vector() {
    Matrix *m = scaling(2, 3, 4);
    Tuple v = vector(-4, 6, 8);
    Tuple scaled = multiply_matrix_with_tuple(m, v);
    Tuple expected = vector(-8, 18, 32);
    assert(tcompare(expected, scaled) == 0);
}

void test_multiply_by_inverse_of_scaling_matrix() {
    Matrix *m = inverse(scaling(2, 3, 4));
    Tuple v = vector(-4, 6, 8);
    Tuple scaled = multiply_matrix_with_tuple(m, v);
    Tuple expected = vector(-2, 2, 2);
    assert(tcompare(expected, scaled) == 0);
}

void test_rotating_point_around_x_axis() {
    Tuple p = point(0, 1 , 0);
    Matrix *half = rotation_x(M_PI / 4);
    Matrix *full = rotation_x(M_PI / 2);
    Tuple rot1 = multiply_matrix_with_tuple(half, p);
    Tuple rot2 = multiply_matrix_with_tuple(full, p);

    Tuple e1 = point(0, sqrt(2)/2, sqrt(2)/2);
    Tuple e2 = point(0, 0, 1);
    assert(tcompare(e1, rot1) == 0);
    assert(tcompare(e2, rot2) == 0);
}

void test_rotate_x_axis_by_inverse() {
    Tuple p = point(0, 1 , 0);
    Matrix *half = inverse(rotation_x(M_PI / 4));
    Tuple rot1 = multiply_matrix_with_tuple(half, p);

    Tuple e1 = point(0, sqrt(2)/2, -sqrt(2)/2);
    assert(tcompare(e1, rot1) == 0);
}

void test_rotating_point_around_y_axis() {
    Tuple p = point(0, 0, 1);
    Matrix *half = rotation_y(M_PI / 4);
    Matrix *full = rotation_y(M_PI / 2);
    Tuple rot1 = multiply_matrix_with_tuple(half, p);
    Tuple rot2 = multiply_matrix_with_tuple(full, p);

    Tuple e1 = point(sqrt(2)/2, 0, sqrt(2)/2);
    Tuple e2 = point(1, 0, 0);
    assert(tcompare(e1, rot1) == 0);
    assert(tcompare(e2, rot2) == 0);
}

void test_rotating_point_around_z_axis() {
    Tuple p = point(0, 1 , 0);
    Matrix *half = rotation_z(M_PI / 4);
    Matrix *full = rotation_z(M_PI / 2);
    Tuple rot1 = multiply_matrix_with_tuple(half, p);
    Tuple rot2 = multiply_matrix_with_tuple(full, p);

    Tuple e1 = point(-sqrt(2)/2, sqrt(2)/2, 0);
    Tuple e2 = point(-1, 0, 0);
    assert(tcompare(e1, rot1) == 0);
    assert(tcompare(e2, rot2) == 0);
}

void test_shearing_moves_x_prop_y() {
    Matrix *m = shearing(1, 0, 0, 0, 0, 0);
    Tuple p = point(2, 3, 4);
    Tuple sheared = multiply_matrix_with_tuple(m, p);
    Tuple expected = point(5, 3, 4);
    assert(tcompare(expected, sheared) == 0);
}

void test_shearing_moves_x_prop_z() {
    Matrix *m = shearing(0, 1, 0, 0, 0, 0);
    Tuple p = point(2, 3, 4);
    Tuple sheared = multiply_matrix_with_tuple(m, p);
    Tuple expected = point(6, 3, 4);
    assert(tcompare(expected, sheared) == 0);
}

void test_shearing_moves_y_prop_x() {
    Matrix *m = shearing(0, 0, 1, 0, 0, 0);
    Tuple p = point(2, 3, 4);
    Tuple sheared = multiply_matrix_with_tuple(m, p);
    Tuple expected = point(2, 5, 4);
    assert(tcompare(expected, sheared) == 0);
}

void test_shearing_moves_y_prop_z() {
    Matrix *m = shearing(0, 0, 0, 1, 0, 0);
    Tuple p = point(2, 3, 4);
    Tuple sheared = multiply_matrix_with_tuple(m, p);
    Tuple expected = point(2, 7, 4);
    assert(tcompare(expected, sheared) == 0);
}

void test_shearing_moves_z_prop_x() {
    Matrix *m = shearing(0, 0, 0, 0, 1, 0);
    Tuple p = point(2, 3, 4);
    Tuple sheared = multiply_matrix_with_tuple(m, p);
    Tuple expected = point(2, 3, 6);
    assert(tcompare(expected, sheared) == 0);
}

void test_shearing_moves_z_prop_y() {
    Matrix *m = shearing(0, 0, 0, 0, 0, 1);
    Tuple p = point(2, 3, 4);
    Tuple sheared = multiply_matrix_with_tuple(m, p);
    Tuple expected = point(2, 3, 7);
    assert(tcompare(expected, sheared) == 0);
}

void test_individual_transformations_are_applied_in_sequence() {
    Tuple p = point(1, 0, 1);
    Matrix *rot = rotation_x(M_PI / 2);
    Matrix *scal = scaling(5, 5, 5);
    Matrix *trans = translation(10, 5, 7);
    
    Tuple p2 = multiply_matrix_with_tuple(rot, p);
    assert(tcompare(p2, point(1, -1, 0)) == 0);
    
    Tuple p3 = multiply_matrix_with_tuple(scal, p2);
    assert(tcompare(p3, point(5, -5, 0)) == 0);

    Tuple p4 = multiply_matrix_with_tuple(trans, p3);
    assert(tcompare(p4, point(15, 0, 7)) == 0);
}

void test_chained_transormations_must_be_applied_in_reverse() {
    Tuple p = point(1, 0, 1);
    Matrix *rot = rotation_x(M_PI / 2);
    Matrix *scal = scaling(5, 5, 5);
    Matrix *trans = translation(10, 5, 7);

    Matrix *t = multiply_matrices(multiply_matrices(trans, scal), rot);
    Tuple transformed = multiply_matrix_with_tuple(t, p);
    assert(tcompare(transformed, point(15, 0, 7)) == 0);
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
    test_find_determinant_3_4_dim_matrix();
    test_invert_matrix();
    test_more_matrix_inversions();
    test_multiply_product_by_its_inverse();
    test_multiply_point_by_translation_matrix();
    test_multiply_point_by_translation_inverse();
    test_scale_matrix_applied_to_point();
    test_scale_matrix_applied_to_vector();
    test_multiply_by_inverse_of_scaling_matrix();
    test_rotating_point_around_x_axis();
    test_rotate_x_axis_by_inverse();
    test_rotating_point_around_y_axis();
    test_rotating_point_around_z_axis();
    test_shearing_moves_x_prop_y();
    test_shearing_moves_x_prop_z();
    test_shearing_moves_y_prop_x();
    test_shearing_moves_y_prop_z();
    test_shearing_moves_z_prop_x();
    test_shearing_moves_z_prop_y();
    test_individual_transformations_are_applied_in_sequence();
    test_chained_transormations_must_be_applied_in_reverse();
}
