#include <assert.h>

#include "../src/tuples.h"

void test_tuple_is_point() {
    Tuple t = { .x = 4.3, .y = -3.0, .z = 0.6, .w = 1 };
    assert(t.w == 1);
}

void test_tuple_is_vector() {
    Tuple t = { .x = 4.3, .y = -3.0, .z = 0.6, .w = 0 };
    assert(t.w == 0);
}

void test_make_point() {
    Tuple *t = point(3.0, -4.0, 5.0);
    assert(t->w == 1);
}

void test_make_vector() {
    Tuple *t = vector(3.0, -4.0, 5.0);
    assert(t->w == 0);
}

int main() {
    test_tuple_is_point();
    test_tuple_is_vector();
    test_make_point();
    test_make_vector();
}
