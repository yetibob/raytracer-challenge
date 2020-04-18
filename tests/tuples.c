#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../src/tuples.h"
#include "../src/utils.h"

void test_make_tuple_point() {
    Tuple t = tuple_point(3.0, -4.0, 5.0);
    assert(tuple_is_point(t) == 0);
}

void test_make_tuple_vector() {
    Tuple t = tuple_vector(3.0, -4.0, 5.0);
    assert(tuple_is_vector(t) == 0);
}

void test_tuple_compare() {
    Tuple t1 = tuple_point(3.0, -4.0, 5.0);
    Tuple t2 = tuple_point(3.0, -4.0, 5.0);
    assert(tuple_compare(t1, t2) == 0);
    t1[0] = -3.1;
    assert(tuple_compare(t1, t2) == 1);
    Tuple t3 = tuple_vector(3.0, -4.0, 5.0);
    assert(tuple_compare(t2, t3) == 1);
}

void test_tuple_add() {
    Tuple t1 = tuple_point(3,-2, 5);
    Tuple t2 = tuple_vector(-2, 3, 1);
    Tuple t3 = tuple_add(t1, t2);
    Tuple EXPECTED = tuple_point(1, 1, 6);
    assert(tuple_compare(t3, EXPECTED) == 0);
}

void test_tuple_subtract_two_tuple_points() {
    Tuple t1 = tuple_point(3, 2, 1);
    Tuple t2 = tuple_point(5, 6, 7);
    Tuple t3 = tuple_subtract(t1, t2);
    Tuple EXPECTED = tuple_vector(-2, -4, -6);
    assert(tuple_compare(t3, EXPECTED) == 0);
}

void test_tuple_subtract_tuple_vector_from_tuple_point() {
    Tuple t1 = tuple_point(3, 2, 1);
    Tuple t2 = tuple_vector(5, 6, 7);
    Tuple t3 = tuple_subtract(t1, t2);
    Tuple EXPECTED = tuple_point(-2, -4, -6);
    assert(tuple_compare(t3, EXPECTED) == 0);
}

void test_tuple_subtract_two_tuple_vectors() {
    Tuple t1 = tuple_vector(3, 2, 1);
    Tuple t2 = tuple_vector(5, 6, 7);
    Tuple t3 = tuple_subtract(t1, t2);
    Tuple EXPECTED = tuple_vector(-2, -4, -6);
    assert(tuple_compare(t3, EXPECTED) == 0);
}

void test_tuple_negate_tuple() {
    Tuple t1 = tuple_vector(1, -2, 3);
    Tuple t2 = tuple_negate(t1);
    Tuple EXPECTED = tuple_vector(-1, 2, -3);
    assert(tuple_compare(t2, EXPECTED) == 0);
}

void test_tuple_scale_tuple() {
    Tuple t1 = tuple_point(1, 2, 3);
    Tuple scaled = tuple_scale(t1, 3.5);
    Tuple EXPECTED = tuple_point(3.5, 7, 10.5);
    assert(tuple_compare(scaled, EXPECTED) == 0);
    scaled = tuple_scale(t1, 0.5);
    EXPECTED = tuple_point(0.5, 1, 1.5);
    assert(tuple_compare(scaled, EXPECTED) == 0);
}

void test_tuple_dscale_tuple() {
    Tuple t1 = tuple_point(1, 2, 3);
    Tuple scaled = tuple_dscale(t1, 2);
    Tuple EXPECTED = tuple_point(0.5, 1, 1.5);
    assert(tuple_compare(scaled, EXPECTED) == 0);
}

void test_compute_tuple_vector_tuple_magnitude() {
    double EXPECTED = 1;
    Tuple t1 = tuple_vector(1, 0, 0);
    assert(equals(tuple_magnitude(t1), EXPECTED) == 0);
    Tuple t2 = tuple_vector(0, 1, 0);
    assert(equals(tuple_magnitude(t2), EXPECTED) == 0);
    Tuple t3 = tuple_vector(0, 0, 1);
    assert(equals(tuple_magnitude(t3), EXPECTED) == 0);

    EXPECTED = sqrt(14);
    Tuple t4 = tuple_vector(1, 2, 3);
    assert(equals(tuple_magnitude(t4), EXPECTED) == 0);
    Tuple t5 = tuple_vector(-1, -2, -3);
    assert(equals(tuple_magnitude(t5), EXPECTED) == 0);
}

void test_tuple_normalize_tuple_vector() {
    Tuple v = tuple_vector(4, 0, 0);
    Tuple e = tuple_vector(1, 0, 0);
    assert(tuple_compare(tuple_normalize(v), e) == 0);
    v = tuple_vector(1, 2, 3);
    e = tuple_vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
    assert(tuple_compare(tuple_normalize(v), e) == 0);
}

void test_tuple_dot_product() {
    Tuple v1 = tuple_vector(1, 2, 3);
    Tuple v2 = tuple_vector(2, 3, 4);
    double tuple_dotp = tuple_dot(v1, v2);
    double e = 20;
    assert(equals(tuple_dotp, e) == 0);
}

void test_tuple_cross_product() {
    Tuple v1 = tuple_vector(1, 2, 3);
    Tuple v2 = tuple_vector(2, 3, 4);
    Tuple cp = tuple_cross(v1, v2);
    Tuple e = tuple_vector(-1, 2, -1);
    assert(tuple_compare(cp, e) == 0);
    cp = tuple_cross(v2, v1);
    e = tuple_vector(1, -2, 1);
    assert(tuple_compare(cp, e) == 0);
}


int main() {
    test_make_tuple_point();
    test_make_tuple_vector();
    test_tuple_compare();
    test_tuple_add();
    test_tuple_subtract_two_tuple_points();
    test_tuple_subtract_tuple_vector_from_tuple_point();
    test_tuple_subtract_two_tuple_vectors();
    test_tuple_negate_tuple();
    test_tuple_scale_tuple();
    test_tuple_dscale_tuple();
    test_compute_tuple_vector_tuple_magnitude();
    test_tuple_normalize_tuple_vector();
    test_tuple_dot_product();
    test_tuple_cross_product();
}
