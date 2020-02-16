#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../src/tuples.h"
#include "../src/utils.h"

void test_tuple_is_point() {
    double t[4] = { 4.3, -3.0, 2.0, 1.0 };
    assert(t[3] == 1);
}

void test_tuple_is_vector() {
    double t[4] = { 4.3, -3.0, 0.6, 0.0 };
    assert(t[3] == 0);
}

void test_make_point() {
    Tuple t = point(3.0, -4.0, 5.0);
    assert(t[3] == 1);
}

void test_make_vector() {
    Tuple t = vector(3.0, -4.0, 5.0);
    assert(t[3] == 0);
}

void test_is_equal() {
    Tuple t1 = point(3.0, -4.0, 5.0);
    Tuple t2 = point(3.0, -4.0, 5.0);
    assert(is_equal(t1, t2) == 0);
    t1[0] = -3.1;
    assert(is_equal(t1, t2) == 1);
    Tuple t3 = vector(3.0, -4.0, 5.0);
    assert(is_equal(t2, t3) == 1);
}

void test_add() {
    Tuple t1 = point(3,-2, 5);
    Tuple t2 = vector(-2, 3, 1);
    Tuple t3 = add(t1, t2);
    Tuple EXPECTED = point(1, 1, 6);
    assert(is_equal(t3, EXPECTED) == 0);
}

void test_subtract_two_points() {
    Tuple t1 = point(3, 2, 1);
    Tuple t2 = point(5, 6, 7);
    Tuple t3 = subtract(t1, t2);
    Tuple EXPECTED = vector(-2, -4, -6);
    assert(is_equal(t3, EXPECTED) == 0);
}

void test_subtract_vector_from_point() {
    Tuple t1 = point(3, 2, 1);
    Tuple t2 = vector(5, 6, 7);
    Tuple t3 = subtract(t1, t2);
    Tuple EXPECTED = point(-2, -4, -6);
    assert(is_equal(t3, EXPECTED) == 0);
}

void test_subtract_two_vectors() {
    Tuple t1 = vector(3, 2, 1);
    Tuple t2 = vector(5, 6, 7);
    Tuple t3 = subtract(t1, t2);
    Tuple EXPECTED = vector(-2, -4, -6);
    assert(is_equal(t3, EXPECTED) == 0);
}

void test_negate_tuple() {
    Tuple t1 = vector(1, -2, 3);
    Tuple t2 = negate(t1);
    Tuple EXPECTED = vector(-1, 2, -3);
    assert(is_equal(t2, EXPECTED) == 0);
}

void test_mscale_tuple() {
    Tuple t1 = point(1, 2, 3);
    Tuple scaled = mscale(t1, 3.5);
    Tuple EXPECTED = point(3.5, 7, 10.5);
    assert(is_equal(scaled, EXPECTED) == 0);
    scaled = mscale(t1, 0.5);
    EXPECTED = point(0.5, 1, 1.5);
    assert(is_equal(scaled, EXPECTED) == 0);
}

void test_dscale_tuple() {
    Tuple t1 = point(1, 2, 3);
    Tuple scaled = dscale(t1, 2);
    Tuple EXPECTED = point(0.5, 1, 1.5);
    assert(is_equal(scaled, EXPECTED) == 0);
}

void test_compute_vector_magnitude() {
    double EXPECTED = 1;
    Tuple t1 = vector(1, 0, 0);
    assert(equals(magnitude(t1), EXPECTED) == 0);
    Tuple t2 = vector(0, 1, 0);
    assert(equals(magnitude(t2), EXPECTED) == 0);
    Tuple t3 = vector(0, 0, 1);
    assert(equals(magnitude(t3), EXPECTED) == 0);

    EXPECTED = sqrt(14);
    Tuple t4 = vector(1, 2, 3);
    assert(equals(magnitude(t4), EXPECTED) == 0);
    Tuple t5 = vector(-1, -2, -3);
    assert(equals(magnitude(t5), EXPECTED) == 0);
}

void test_normaliize_vector() {
    Tuple v = vector(4, 0, 0);
    Tuple e = vector(1, 0, 0);
    assert(is_equal(normalize(v), e) == 0);
    v = vector(1, 2, 3);
    e = vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
    assert(is_equal(normalize(v), e) == 0);
}

void test_dot_product() {
    Tuple v1 = vector(1, 2, 3);
    Tuple v2 = vector(2, 3, 4);
    double dotp = dot(v1, v2);
    double e = 20;
    assert(equals(dotp, e) == 0);
}

void test_cross_product() {
    Tuple v1 = vector(1, 2, 3);
    Tuple v2 = vector(2, 3, 4);
    Tuple cp = cross(v1, v2);
    Tuple e = vector(-1, 2, -1);
    assert(is_equal(cp, e) == 0);
    cp = cross(v2, v1);
    e = vector(1, -2, 1);
    assert(is_equal(cp, e) == 0);
}


int main() {
    test_tuple_is_point();
    test_tuple_is_vector();
    test_make_point();
    test_make_vector();
    test_is_equal();
    test_add();
    test_subtract_two_points();
    test_subtract_vector_from_point();
    test_subtract_two_vectors();
    test_negate_tuple();
    test_mscale_tuple();
    test_dscale_tuple();
    test_compute_vector_magnitude();
    test_normaliize_vector();
    test_dot_product();
    test_cross_product();
}
