#include <assert.h>
#include <iostream>
#include <math.h>

#include "tuples.hpp"
#include "utils.hpp"

void test_make_tuple_point() {
    Tuple t = { 0, 0, 0, POINT };
    assert(t.is_point());
}

void test_make_tuple_vector() {
    Tuple t = { 0, 0, 0, VEC };
    assert(t.is_vector());
}

void test_tuple_compare() {
    Tuple t1 = { 3.0, -4.0, 5.0, POINT };
    Tuple t2 = { 3.0, -4.0, 5.0, POINT };

    assert(t1.compare(t2));

    t1[0] = -3.1;
    assert(!t1.compare(t2));

    Tuple t3 = { 3.0, -4.0, 5.0, VEC };
    assert(!t2.compare(t3));
}

void test_tuple_add() {
    Tuple t1 = { 3, -2, 5, POINT };

    Tuple t2 = { -2, 3, 1, VEC };

    Tuple t3 = t1.add(t2);

    Tuple EXPECTED = { 1, 1, 6, POINT };
    assert(t3.compare(EXPECTED));
}

void test_tuple_subtract_two_tuple_points() {
    Tuple t1 = { 3, 2, 1, POINT };

    Tuple t2 = { 5, 6, 7, POINT };

    Tuple t3 = t1.subtract(t2);

    Tuple EXPECTED = { -2, -4, -6, VEC };
    assert(t3.compare(EXPECTED));
}

void test_tuple_subtract_tuple_vector_from_tuple_point() {
    Tuple t1 = { 3, 2, 1, POINT };

    Tuple t2 = { 5, 6, 7, VEC };

    Tuple t3 = t1.subtract(t2);

    Tuple EXPECTED = { -2, -4, -6, POINT };
    assert(t3.compare(EXPECTED));
}

void test_tuple_subtract_two_tuple_vectors() {
    Tuple t1 = { 3, 2, 1, VEC };
    Tuple t2 = { 5, 6, 7, VEC };

    Tuple t3 = t1.subtract(t2);

    Tuple EXPECTED = { -2, -4, -6, VEC };
    assert(t3.compare(EXPECTED));
}

void test_tuple_negate_tuple() {
    Tuple t1 = { 1, -2, 3, VEC };

    Tuple t2 = t1.negate();

    Tuple EXPECTED = { -1, 2, -3, VEC };
    assert(t2.compare(EXPECTED));
}

void test_tuple_scale_tuple() {
    Tuple t1 = { 1, 2, 3, POINT };

    Tuple scaled = t1.scale(3.5);

    Tuple EXPECTED = { 3.5, 7, 10.5, POINT };
    assert(scaled.compare(EXPECTED));

    scaled          = t1.scale(0.5);
    Tuple EXPECTED2 = { 0.5, 1, 1.5, POINT };
    assert(scaled.compare(EXPECTED2));
}

void test_tuple_dscale_tuple() {
    Tuple t1 = { 1, 2, 3, POINT };

    Tuple scaled = t1.dscale(2);

    Tuple EXPECTED = { 0.5, 1, 1.5, POINT };
    assert(scaled.compare(EXPECTED));
}

void test_compute_tuple_vector_tuple_magnitude() {
    double EXPECTED = 1;

    Tuple t1 = { 1, 0, 0, VEC };
    assert(equals(t1.magnitude(), EXPECTED));

    Tuple t2 = { 0, 1, 0, VEC };
    assert(equals(t2.magnitude(), EXPECTED));

    Tuple t3 = { 0, 0, 1, VEC };
    assert(equals(t3.magnitude(), EXPECTED));

    EXPECTED = sqrt(14);
    Tuple t4 = { 1, 2, 3, VEC };
    assert(equals(t4.magnitude(), EXPECTED));

    Tuple t5 = { -1, -2, -3, VEC };
    assert(equals(t5.magnitude(), EXPECTED));
}

void test_tuple_normalize_tuple_vector() {
    Tuple v = { 4, 0, 0, VEC };
    Tuple e = { 1, 0, 0, VEC };

    Tuple norm1 = v.normalize();
    assert(norm1.compare(e));

    Tuple v2 = { 1, 2, 3, VEC };

    Tuple norm2 = v2.normalize();

    Tuple e2 = { 1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14), VEC };
    assert(norm2.compare(e2));
}

void test_tuple_dot_product() {
    Tuple v1 = { 1, 2, 3, VEC };
    Tuple v2 = { 2, 3, 4, VEC };

    double tuple_dotp = v1.dot(v2);
    double e          = 20;
    assert(equals(tuple_dotp, e));
}

void test_tuple_cross_product() {
    Tuple v1 = { 1, 2, 3, VEC };
    Tuple v2 = { 2, 3, 4, VEC };

    Tuple cp = v1.cross(v2);

    Tuple e = { -1, 2, -1, VEC };
    assert(cp.compare(e));

    cp       = v2.cross(v1);
    Tuple e2 = { 1, -2, 1, VEC };
    assert(cp.compare(e2));
}

void test_reflect_at_angle() {
    Tuple v = { 1, -1, 0, VEC };
    Tuple n = { 0, 1, 0, VEC };

    Tuple r = v.reflect(n);

    Tuple e = { 1, 1, 0, VEC };
    assert(r.compare(e));
}

void test_reflect_off_slant() {
    Tuple v = { 0, -1, 0, VEC };
    Tuple n = { sqrt(2) / 2, sqrt(2) / 2, 0, VEC };

    Tuple r = v.reflect(n);
    Tuple e = { 1, 0, 0, VEC };

    assert(r.compare(e));
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
    test_reflect_at_angle();
    test_reflect_off_slant();
}
