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
    assert(equals(0, data[0][0]));
    assert(equals(0, data[0][1]));
    assert(equals(0, data[1][0]));
    assert(equals(0, data[1][1]));
}

void test_matrix_compare() {
    Matrix *m1 = matrix(4);
    Matrix *m2 = matrix(4);

    int val = 1;
    for (int i = 0; i < m1->dim; i++) {
        for (int j = 0; j < m1->dim; j++) {
            m1->data[i][j] = val;
            m2->data[i][j] = val;
        }
    }

    assert(matrix_compare(m1, m2));
}

void test_matrix_multiply() {
   double a1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2 };
   double a2[16] = { -2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8 };

   Matrix *m1 = matrix_gen(a1, 4);
   Matrix *m2 = matrix_gen(a2, 4);

   double a3[16] = { 20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42 };
   Matrix *expected = matrix_gen(a3, 4);

   Matrix *p = matrix_multiply(m1, m2);
   assert(matrix_compare(expected, p));
}

void test_matrix_multiply_tuple() {
    double a[16] = { 1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1 };
    Matrix *m = matrix_gen(a, 4);
    Tuple t1 = {1, 2, 3, POINT};
    
    Tuple result;
    matrix_multiply_tuple(m, t1, result);

    Tuple e = {18, 24, 33, POINT};
    assert(tuple_compare(e, result));
}

void test_multiply_matrix_by_identity_matrix() {
    double a1[] = { 0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32 };
    Matrix *m = matrix_gen(a1, 4);

    Matrix *result = matrix_multiply(m, matrix_IdentityMatrix());
    assert(matrix_compare(m, result));
}

void test_multiply_tuple_by_identity_matrix() {
    Tuple t = {1, 2, 3, POINT};
    t[3] = 4;

    Tuple result;
    matrix_multiply_tuple(matrix_IdentityMatrix(), t, result);
    assert(tuple_compare(t, result));
}

void test_matrix_transpose_matrix() {
    double arr[] = { 0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8 };
    Matrix *m = matrix_gen(arr, 4);

    double earr[] = { 0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8 };
    Matrix *e = matrix_gen(earr, 4);

    Matrix *transpose = matrix_transpose(m);
    assert(matrix_compare(e, transpose));
}

void test_matrix_transpose_identity_matrix() {
    Matrix *id = matrix_IdentityMatrix();
    assert(matrix_compare(id, matrix_transpose(id)));
}

void test_find_matrix_determinant_2_dim_matrix() {
    double arr[] = { 1 , 5, -3, 2 };
    Matrix *m = matrix_gen(arr, 2);

    double e = 17;
    double res = matrix_determinant(m);
    assert(equals(e, res));
}

void test_get_matrix_sub() {
    double a1[] = { 1, 5, 0, -3, 2, 7, 0, 6, -3 };
    Matrix *m1 = matrix_gen(a1, 3);
    Matrix *sub1 = matrix_sub(m1, 0, 2);

    double e1a[] = { -3, 2, 0, 6};
    Matrix *e1 = matrix_gen(e1a, 2); 
    assert(matrix_compare(e1, sub1));

    double a2[] = { -6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    Matrix *m2 = matrix_gen(a2, 4);
    Matrix *sub2 = matrix_sub(m2, 2, 1);

    double e2a[] = { -6, 1, 6, -8, 8, 6, -7, -1, 1};
    Matrix *e2 = matrix_gen(e2a, 3);
    assert(matrix_compare(e2, sub2));
}

void test_get_matrix_minor() {
    double a1[] = { 3, 5, 0, 2, -1, -7, 6, -1, 5 };
    Matrix *m = matrix_gen(a1, 3);
    Matrix *b = matrix_sub(m, 1, 0);
    double d1 = matrix_determinant(b);
    assert(equals(d1, 25));
    double d2 = matrix_minor(m, 1, 0);
    assert(equals(d1, d2));
}

void test_get_matrix_cofactor() {
    double a[] = { 3, 5, 0, 2, -1, -7, 6, -1, 5 };
    Matrix *m = matrix_gen(a, 3);
    double matrix_minor1 = matrix_minor(m, 0, 0);
    assert(equals(-12, matrix_minor1));
    double matrix_cofactor1 = matrix_cofactor(m, 0, 0);
    assert(equals(-12, matrix_cofactor1));

    double matrix_minor2 = matrix_minor(m, 1, 0);
    assert(equals(25, matrix_minor2));
    double matrix_cofactor2 = matrix_cofactor(m, 1, 0);
    assert(equals(-25, matrix_cofactor2));
}

void test_find_matrix_determinant_3_4_dim_matrix() {
    double arr1[] = { 1, 2, 6, -5, 8, -4, 2, 6, 4 };
    Matrix *m3 = matrix_gen(arr1, 3);

    assert(equals(56,   matrix_cofactor(m3, 0, 0)));
    assert(equals(12,   matrix_cofactor(m3, 0, 1)));
    assert(equals(-46,  matrix_cofactor(m3, 0, 2)));
    assert(equals(-196, matrix_determinant(m3)));

    double arr2[] = { -2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9 };
    Matrix *m4 = matrix_gen(arr2, 4);

    assert(equals(690,   matrix_cofactor(m4, 0, 0)));
    assert(equals(447,   matrix_cofactor(m4, 0, 1)));
    assert(equals(210,   matrix_cofactor(m4, 0, 2)));
    assert(equals(51,    matrix_cofactor(m4, 0, 3)));
    assert(equals(-4071, matrix_determinant(m4)));
}

void test_invert_matrix() {
    double a1[] = { -5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4 };
    Matrix *m1 = matrix_gen(a1, 4);

    Matrix *m2 = matrix_inverse(m1);
    assert(equals(matrix_determinant(m1), 532));
    assert(equals(matrix_cofactor(m1, 2, 3), -160));
    assert(equals(m2->data[3][2], -160.0/532.0));
    assert(equals(matrix_cofactor(m1, 3, 2), 105));
    assert(equals(m2->data[2][3], 105.0/532.0));

    double a2[] = { 0.21805, 0.45113, 0.24060, -0.04511, -0.80827, -1.45677, -0.44361, 0.52068, -0.07895, -0.22368, -0.05263, 0.19737, -0.52256, -0.81391, -0.30075, 0.30639 };
    Matrix *e = matrix_gen(a2, 4);
    assert(matrix_compare(e, m2));
}

void test_more_matrix_inversions() {
    double a1[] = { 8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4 };
    double a2[] = { 9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2 };
    Matrix *m1 = matrix_gen(a1, 4);
    Matrix *m2 = matrix_gen(a2, 4);

    Matrix *i1 = matrix_inverse(m1);
    Matrix *i2 = matrix_inverse(m2);

    double ea1[] = { -0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308 };
    double ea2[] = { -0.04074, -0.07778, 0.14444, -0.22222, -0.07778, 0.03333, 0.36667, -0.33333, -0.02901, -0.14630, -0.10926, 0.12963, 0.17778, 0.06667, -0.26667, 0.33333 };
    Matrix *e1 = matrix_gen(ea1, 4);
    Matrix *e2 = matrix_gen(ea2, 4);

    assert(matrix_compare(e1, i1));
    assert(matrix_compare(e2, i2));
}

void test_multiply_product_by_its_matrix_inverse() {
    double a1[] = { 3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1 };
    double a2[] = { 8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5 };

    Matrix *m1 = matrix_gen(a1, 4);
    Matrix *m2 = matrix_gen(a2, 4);

    Matrix *m3 = matrix_multiply(m1, m2);
    assert(matrix_compare(matrix_multiply(m3, matrix_inverse(m2)), m1));
}

void test_multiply_tuple_point_by_matrix_translation_matrix() {
    Matrix *m = matrix_translation(5, -3, 2);
    Tuple p = {-3, 4, 5, POINT};

    Tuple transformed;
    matrix_multiply_tuple(m, p, transformed);

    Tuple expected = {2, 1, 7, POINT};
    assert(tuple_compare(transformed, expected)); 
}

void test_multiply_tuple_point_by_matrix_translation_matrix_inverse() {
    Matrix *m = matrix_inverse(matrix_translation(5, -3, 2));
    Tuple p = {-3, 4, 5, POINT};

    Tuple transformed;
    matrix_multiply_tuple(m, p, transformed);
    
    Tuple expected = {-8, 7, 3, POINT};
    assert(tuple_compare(transformed, expected));
}

void test_multiply_tuple_vector_by_matrix_translation_does_nothing() {
    Matrix *m = matrix_translation(5, -3, 2);
    Tuple v = {-3, 4, 5, VEC};
    
    Tuple transformed;
    matrix_multiply_tuple(m, v, transformed);
    assert(tuple_compare(transformed, v));
}

void test_scale_matrix_applied_to_tuple_point() {
    Matrix *m = matrix_scaling(2, 3, 4);
    Tuple p = {-4, 6, 8, POINT};

    Tuple scaled;
    matrix_multiply_tuple(m, p, scaled);

    Tuple expected = {-8, 18, 32, POINT};
    assert(tuple_compare(expected, scaled));
}

void test_scale_matrix_applied_to_tuple_vector() {
    Matrix *m = matrix_scaling(2, 3, 4);
    Tuple v = {-4, 6, 8, VEC};

    Tuple scaled;
    matrix_multiply_tuple(m, v, scaled);

    Tuple expected = {-8, 18, 32, VEC};
    assert(tuple_compare(expected, scaled));
}

void test_multiply_by_matrix_inverse_of_matrix_scaling_matrix() {
    Matrix *m = matrix_inverse(matrix_scaling(2, 3, 4));
    Tuple v = {-4, 6, 8, VEC};

    Tuple scaled;
    matrix_multiply_tuple(m, v, scaled);

    Tuple expected = {-2, 2, 2, VEC};
    assert(tuple_compare(expected, scaled));
}

void test_rotating_tuple_point_around_x_axis() {
    Tuple p = {0, 1, 0, POINT};

    Matrix *half = matrix_rotation_x(M_PI / 4);
    Matrix *full = matrix_rotation_x(M_PI / 2);

    Tuple rot1;
    matrix_multiply_tuple(half, p, rot1);
    Tuple rot2;
    matrix_multiply_tuple(full, p, rot2);

    Tuple e1 = {0, sqrt(2)/2, sqrt(2)/2, POINT};
    Tuple e2 = {0, 0, 1, POINT};
    assert(tuple_compare(e1, rot1));
    assert(tuple_compare(e2, rot2));
}

void test_rotate_x_axis_by_matrix_inverse() {
    Tuple p = {0, 1, 0, POINT};

    Matrix *half = matrix_inverse(matrix_rotation_x(M_PI / 4));
    Tuple rot1;
    matrix_multiply_tuple(half, p, rot1);

    Tuple e1 = {0, sqrt(2)/2, -sqrt(2)/2, POINT};
    assert(tuple_compare(e1, rot1));
}

void test_rotating_tuple_point_around_y_axis() {
    Tuple p = {0, 0, 1, POINT};

    Matrix *half = matrix_rotation_y(M_PI / 4);
    Matrix *full = matrix_rotation_y(M_PI / 2);

    Tuple rot1;
    matrix_multiply_tuple(half, p, rot1);
    Tuple rot2;
    matrix_multiply_tuple(full, p, rot2);

    Tuple e1 = {sqrt(2)/2, 0, sqrt(2)/2, POINT};
    Tuple e2 = {1, 0, 0, POINT};
    assert(tuple_compare(e1, rot1));
    assert(tuple_compare(e2, rot2));
}

void test_rotating_tuple_point_around_z_axis() {
    Tuple p = {0, 1, 0, POINT};
    
    Matrix *half = matrix_rotation_z(M_PI / 4);
    Matrix *full = matrix_rotation_z(M_PI / 2);
    
    Tuple rot1;
    matrix_multiply_tuple(half, p, rot1);
    Tuple rot2;
    matrix_multiply_tuple(full, p, rot2);

    Tuple e1 = {-sqrt(2)/2, sqrt(2)/2, 0, POINT};
    Tuple e2 = {-1, 0, 0, POINT};
    assert(tuple_compare(e1, rot1));
    assert(tuple_compare(e2, rot2));
}

void test_matrix_shearing_moves_x_prop_y() {
    Matrix *m = matrix_shearing(1, 0, 0, 0, 0, 0);
    Tuple p = {2, 3, 4, POINT};

    Tuple sheared;
    matrix_multiply_tuple(m, p, sheared);
    
    Tuple expected = {5, 3, 4, POINT};
    assert(tuple_compare(expected, sheared));
}

void test_matrix_shearing_moves_x_prop_z() {
    Matrix *m = matrix_shearing(0, 1, 0, 0, 0, 0);
    Tuple p = {2, 3, 4, POINT};

    Tuple sheared;
    matrix_multiply_tuple(m, p, sheared);

    Tuple expected = {6, 3, 4, POINT};
    assert(tuple_compare(expected, sheared));
}

void test_matrix_shearing_moves_y_prop_x() {
    Matrix *m = matrix_shearing(0, 0, 1, 0, 0, 0);
    Tuple p = {2, 3, 4, POINT};

    Tuple sheared;
    matrix_multiply_tuple(m, p, sheared);

    Tuple expected = {2, 5, 4, POINT};
    assert(tuple_compare(expected, sheared));
}

void test_matrix_shearing_moves_y_prop_z() {
    Matrix *m = matrix_shearing(0, 0, 0, 1, 0, 0);
    Tuple p = {2, 3, 4, POINT};

    Tuple sheared;
    matrix_multiply_tuple(m, p, sheared);

    Tuple expected = {2, 7, 4, POINT};
    assert(tuple_compare(expected, sheared));
}

void test_matrix_shearing_moves_z_prop_x() {
    Matrix *m = matrix_shearing(0, 0, 0, 0, 1, 0);
    Tuple p = {2, 3, 4, POINT};

    Tuple sheared;
    matrix_multiply_tuple(m, p, sheared);

    Tuple expected = {2, 3, 6, POINT};
    assert(tuple_compare(expected, sheared));
}

void test_matrix_shearing_moves_z_prop_y() {
    Matrix *m = matrix_shearing(0, 0, 0, 0, 0, 1);
    Tuple p = {2, 3, 4, POINT};

    Tuple sheared;
    matrix_multiply_tuple(m, p, sheared);

    Tuple expected = {2, 3, 7, POINT};
    assert(tuple_compare(expected, sheared));
}

void test_individual_transformations_are_applied_in_sequence() {
    Tuple p = {1, 0, 1, POINT};
    Matrix *rot = matrix_rotation_x(M_PI / 2);
    Matrix *scal = matrix_scaling(5, 5, 5);
    Matrix *trans = matrix_translation(10, 5, 7);
    
    Tuple p2;
    matrix_multiply_tuple(rot, p, p2);
    Tuple e = {1, -1, 0, POINT};
    assert(tuple_compare(p2, e));
    
    Tuple p3;
    matrix_multiply_tuple(scal, p2, p3);

    Tuple e2 = {5, -5, 0, POINT};
    assert(tuple_compare(p3, e2));

    Tuple p4;
    matrix_multiply_tuple(trans, p3, p4);

    Tuple e3 = {15, 0, 7, POINT};
    assert(tuple_compare(p4, e3));
}

void test_chained_transormations_must_be_applied_in_reverse() {
    Tuple p = {1, 0, 1, POINT};
    Matrix *rot = matrix_rotation_x(M_PI / 2);
    Matrix *scal = matrix_scaling(5, 5, 5);
    Matrix *trans = matrix_translation(10, 5, 7);

    Matrix *t = matrix_multiply(matrix_multiply(trans, scal), rot);
    Tuple transformed;
    matrix_multiply_tuple(t, p, transformed);

    Tuple e = {15, 0, 7, POINT};
    assert(tuple_compare(transformed, e));
}

int main() {
    test_create_matrix();
    test_matrix_compare();
    test_matrix_multiply();
    test_matrix_multiply_tuple();
    test_multiply_matrix_by_identity_matrix();
    test_multiply_tuple_by_identity_matrix();
    test_matrix_transpose_matrix();
    test_matrix_transpose_identity_matrix();
    test_find_matrix_determinant_2_dim_matrix();
    test_get_matrix_sub();
    test_get_matrix_minor();
    test_get_matrix_cofactor();
    test_find_matrix_determinant_3_4_dim_matrix();
    test_invert_matrix();
    test_more_matrix_inversions();
    test_multiply_product_by_its_matrix_inverse();
    test_multiply_tuple_point_by_matrix_translation_matrix();
    test_multiply_tuple_point_by_matrix_translation_matrix_inverse();
    test_scale_matrix_applied_to_tuple_point();
    test_scale_matrix_applied_to_tuple_vector();
    test_multiply_by_matrix_inverse_of_matrix_scaling_matrix();
    test_rotating_tuple_point_around_x_axis();
    test_rotate_x_axis_by_matrix_inverse();
    test_rotating_tuple_point_around_y_axis();
    test_rotating_tuple_point_around_z_axis();
    test_matrix_shearing_moves_x_prop_y();
    test_matrix_shearing_moves_x_prop_z();
    test_matrix_shearing_moves_y_prop_x();
    test_matrix_shearing_moves_y_prop_z();
    test_matrix_shearing_moves_z_prop_x();
    test_matrix_shearing_moves_z_prop_y();
    test_individual_transformations_are_applied_in_sequence();
    test_chained_transormations_must_be_applied_in_reverse();
}
