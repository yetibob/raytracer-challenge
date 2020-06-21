#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../src/tuples.h"
#include "../src/utils.h"

void test_make_tuple_point() {
    Tuple t = {0, 0, 0, POINT};
    assert(tuple_is_point(t));
}

void test_make_tuple_vector() {
    Tuple t = {0, 0, 0, VEC};
    assert(tuple_is_vector(t));
}

void test_tuple_compare() {
    Tuple t1 = {3.0, -4.0, 5.0, POINT};
    Tuple t2 = {3.0, -4.0, 5.0, POINT};

    assert(tuple_compare(t1, t2));
    
    t1[0] = -3.1;
    assert(!tuple_compare(t1, t2));
    
    Tuple t3 = {3.0, -4.0, 5.0, VEC};
    assert(!tuple_compare(t2, t3));
}

void test_tuple_add() {
    Tuple t1 = {3, -2, 5, POINT};

    Tuple t2 = {-2, 3, 1, VEC};

    Tuple t3;
    tuple_add(t1, t2, t3);
    
    Tuple EXPECTED = {1, 1, 6, POINT};
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_subtract_two_tuple_points() {
    Tuple t1 = {3, 2, 1, POINT};

    Tuple t2 = {5, 6, 7, POINT};

    Tuple t3;
    tuple_subtract(t1, t2, t3);

    Tuple EXPECTED = {-2, -4, -6, VEC};
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_subtract_tuple_vector_from_tuple_point() {
    Tuple t1 = {3, 2, 1, POINT};

    Tuple t2 = {5, 6, 7, VEC};

    Tuple t3;
    tuple_subtract(t1, t2, t3);
    
    Tuple EXPECTED = {-2, -4, -6, POINT};
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_subtract_two_tuple_vectors() {
    Tuple t1 = {3, 2, 1, VEC};
    Tuple t2 = {5, 6, 7, VEC};
    
    Tuple t3;
    tuple_subtract(t1, t2, t3);
    
    Tuple EXPECTED = {-2, -4, -6, VEC};
    assert(tuple_compare(t3, EXPECTED));
}

void test_tuple_negate_tuple() {
    Tuple t1 = {1, -2, 3, VEC};

    Tuple t2;
    tuple_negate(t1, t2);

    Tuple EXPECTED = {-1, 2, -3, VEC};
    assert(tuple_compare(t2, EXPECTED));
}

void test_tuple_scale_tuple() {
    Tuple t1 = {1, 2, 3, POINT};
    
    Tuple scaled;
    tuple_scale(t1, scaled, 3.5);
    
    Tuple EXPECTED = {3.5, 7, 10.5, POINT};
    assert(tuple_compare(scaled, EXPECTED));

    tuple_scale(t1, scaled, 0.5);
    Tuple EXPECTED2 = {0.5, 1, 1.5, POINT};
    assert(tuple_compare(scaled, EXPECTED2));
}

void test_tuple_dscale_tuple() {
    Tuple t1 = {1, 2, 3, POINT};

    Tuple scaled;
    tuple_dscale(t1, scaled, 2);

    Tuple EXPECTED = {0.5, 1, 1.5, POINT};
    assert(tuple_compare(scaled, EXPECTED));
}

void test_compute_tuple_vector_tuple_magnitude() {
    double EXPECTED = 1;

    Tuple t1 = {1, 0, 0, VEC};
    assert(equals(tuple_magnitude(t1), EXPECTED));

    Tuple t2 = {0, 1, 0, VEC};
    assert(equals(tuple_magnitude(t2), EXPECTED));

    Tuple t3 = {0, 0, 1, VEC};
    assert(equals(tuple_magnitude(t3), EXPECTED));

    EXPECTED = sqrt(14);
    Tuple t4 = {1, 2, 3, VEC};
    assert(equals(tuple_magnitude(t4), EXPECTED));

    Tuple t5 = {-1, -2, -3, VEC};
    assert(equals(tuple_magnitude(t5), EXPECTED));
}

void test_tuple_normalize_tuple_vector() {
    Tuple v = {4, 0, 0, VEC};
    Tuple e = {1, 0, 0, VEC};

    Tuple norm1;
    tuple_normalize(v, norm1);
    assert(tuple_compare(norm1, e));
    
    Tuple v2 = {1, 2, 3, VEC};

    Tuple norm2;
    tuple_normalize(v2, norm2);

    Tuple e2 = {1/sqrt(14), 2/sqrt(14), 3/sqrt(14), VEC};
    assert(tuple_compare(norm2, e2));
}

void test_tuple_dot_product() {
    Tuple v1 = {1, 2, 3, VEC};
    Tuple v2 = {2, 3, 4, VEC};

    double tuple_dotp = tuple_dot(v1, v2);
    double e = 20;
    assert(equals(tuple_dotp, e));
}

void test_tuple_cross_product() {
    Tuple v1 = {1, 2, 3, VEC};
    Tuple v2 = {2, 3, 4, VEC};

    Tuple cp;
    cp[3] = VEC;
    tuple_cross(v1, v2, cp);

    Tuple e = {-1, 2, -1, VEC};
    assert(tuple_compare(cp, e));

    tuple_cross(v2, v1, cp);
    Tuple e2 = {1, -2, 1, VEC};
    assert(tuple_compare(cp, e2));
}

//void test_reflect_around_normal() {
//    Tuple v = {1, -1, 0, VEC};
//    Tuple n = {0, 1, 0, VEC};
//
//    Tuple r;
//    tuple_reflect(v, n, r);
//
//    Tuple e = {1, 1, 0, VEC};
//    assert(tuple_compare(r, e));
//}


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
//    test_reflect_around_normal();
}
