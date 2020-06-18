#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../src/tuples.h"
#include "../src/utils.h"

void test_make_tuple_point() {
    Tuple t = {0};
    tuple_point(t);
    assert(tuple_is_point(t));
}

void test_make_tuple_vector() {
    Tuple t = {0};
    tuple_vector(t);
    assert(tuple_is_vector(t));
}

void test_tuple_compare() {
    Tuple t1 = {3.0, -4.0, 5.0};
    tuple_point(t1);

    Tuple t2 = {3.0, -4.0, 5.0};
    tuple_point(t2);

    assert(tuple_compare(t1, t2));
    
    t1[0] = -3.1;
    assert(tuple_compare(t1, t2));
    
    Tuple t3 = {3.0, -4.0, 5.0};
    tuple_vector(t3);
    assert(tuple_compare(t2, t3));
}

void test_tuple_add() {
    Tuple t1 = {3, -2, 5};
    tuple_point(t1);

    Tuple t2 = {-2, 3, 1};
    tuple_vector(t2);

    Tuple t3;
    tuple_add(t1, t2, t3);
    
    Tuple EXPECTED = {1, 1, 6};
    tuple_point(EXPECTED);
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_subtract_two_tuple_points() {
    Tuple t1 = {3, 2, 1};
    tuple_point(t1);

    Tuple t2 = {5, 6, 7};
    tuple_point(t2);

    Tuple t3;
    tuple_subtract(t1, t2, t3);
    Tuple EXPECTED = {-2, -4, -6};
    tuple_vector(EXPECTED);
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_subtract_tuple_vector_from_tuple_point() {
    Tuple t1 = {3, 2, 1};
    tuple_point(t1);

    Tuple t2 = {5, 6, 7};
    tuple_vector(t2);

    Tuple t3;
    tuple_subtract(t1, t2, t3);
    Tuple EXPECTED = {-2, -4, -6};
    tuple_point(EXPECTED);
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_subtract_two_tuple_vectors() {
    Tuple t1 = {3, 2, 1};
    tuple_vector(t1);
    Tuple t2 = {5, 6, 7};
    tuple_vector(t2);
    Tuple t3;
    tuple_subtract(t1, t2, t3);
    Tuple EXPECTED = {-2, -4, -6};
    tuple_vector(EXPECTED);
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_negate_tuple() {
    Tuple t1 = {1, -2, 3};
    tuple_vector(t1);
    Tuple t2;
    tuple_negate(t1, t2);
    Tuple EXPECTED = {-1, 2, -3};
    tuple_vector(EXPECTED);
    assert(tuple_compare(t2, EXPECTED));
}

void test_tuple_scale_tuple() {
    Tuple t1 = {1, 2, 3};
    tuple_point(t1);
    Tuple scaled;
    tuple_scale(t1, scaled, 3.5);
    Tuple EXPECTED = {3.5, 7, 10.5};
    tuple_point(EXPECTED);
    assert(tuple_compare(scaled, EXPECTED));
    tuple_scale(t1, scaled, 0.5);
    Tuple EXPECTED2 = {0.5, 1, 1.5};
    tuple_point(EXPECTED2);
    assert(tuple_compare(scaled, EXPECTED2));
}

void test_tuple_dscale_tuple() {
    Tuple t1 = {1, 2, 3};
    tuple_point(t1);
    Tuple scaled;
    tuple_dscale(t1, scaled, 2);
    Tuple EXPECTED = {0.5, 1, 1.5};
    tuple_point(EXPECTED);
    assert(tuple_compare(scaled, EXPECTED));
}

void test_compute_tuple_vector_tuple_magnitude() {
    double EXPECTED = 1;
    Tuple t1 = {1, 0, 0};
    tuple_vector(t1);
    assert(equals(tuple_magnitude(t1), EXPECTED));
    Tuple t2 = {0, 1, 0};
    tuple_vector(t2);
    assert(equals(tuple_magnitude(t2), EXPECTED));
    Tuple t3 = {0, 0, 1};
    tuple_vector(t3);
    assert(equals(tuple_magnitude(t3), EXPECTED));

    EXPECTED = sqrt(14);
    Tuple t4 = {1, 2, 3};
    tuple_vector(t4);
    assert(equals(tuple_magnitude(t4), EXPECTED));
    Tuple t5 = {-1, -2, -3};
    tuple_vector(t5);
    assert(equals(tuple_magnitude(t5), EXPECTED));
}

void test_tuple_normalize_tuple_vector() {
    Tuple v = {4, 0, 0};
    tuple_vector(v);
    Tuple e = {1, 0, 0};
    tuple_vector(e);
    Tuple norm1;
    tuple_normalize(v, norm1);
    assert(tuple_compare(norm1, e));
    Tuple v2 = {1, 2, 3};
    tuple_vector(v2);
    Tuple e2 = {1/sqrt(14), 2/sqrt(14), 3/sqrt(14)};
    tuple_vector(e2);
    Tuple norm2;
    tuple_normalize(v2, norm2);
    assert(tuple_compare(norm2, e2));
}

void test_tuple_dot_product() {
    Tuple v1 = {1, 2, 3};
    tuple_vector(v1);
    Tuple v2 = {2, 3, 4};
    tuple_vector(v2);
    double tuple_dotp = tuple_dot(v1, v2);
    double e = 20;
    assert(equals(tuple_dotp, e));
}

void test_tuple_cross_product() {
    Tuple v1 = {1, 2, 3};
    tuple_vector(v1);
    Tuple v2 = {2, 3, 4};
    tuple_vector(v2);
    Tuple cp;
    tuple_cross(v1, v2, cp);
    Tuple e = {-1, 2, -1};
    tuple_vector(e);
    assert(tuple_compare(cp, e));
    tuple_cross(v2, v1, cp);
    Tuple e2 = {1, -2, 1};
    tuple_vector(e2);
    assert(tuple_compare(cp, e2));
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
