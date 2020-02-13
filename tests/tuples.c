#include <assert.h>
#include <stdio.h>
#include "../src/tuples.h"

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

int main() {
    test_tuple_is_point();
    test_tuple_is_vector();
    test_make_point();
    test_make_vector();
}
