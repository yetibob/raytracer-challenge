#include <assert.h>
#include "../src/colors.h"
#include "../src/utils.h"

void test_color_tuple() {
    Tuple c = {-0.5, 0.4, 1.7};
    assert(equals(colors_red(c), -0.5));
    assert(equals(colors_green(c), 0.4));
    assert(equals(colors_blue(c), 1.7));
}

void test_tuple_add_colors() {
    Tuple c1 = {0.9, 0.6, 0.75};
    Tuple c2 = {0.7, 0.1, 0.25};
    Tuple e = {1.6, 0.7, 1};

    Tuple added;
    tuple_add(c1, c2, added);
    assert(tuple_compare(added, e));
}

void test_tuple_subtract_colors() {
    Tuple c1 = {0.9, 0.6, 0.75};
    Tuple c2 = {0.7, 0.1, 0.25};
    Tuple e = {0.2, 0.5, 0.5};
    Tuple sub;
    tuple_subtract(c1, c2, sub);
    assert(tuple_compare(sub, e));
}

void test_mutliply_color_by_scalar() {
    Tuple c1 = {0.2, 0.3, 0.4};
    Tuple e = {0.4, 0.6, 0.8};
    Tuple scaled;
    tuple_scale(c1, scaled, 2);
    assert(tuple_compare(scaled, e));
}

void test_multiple_two_colors() {
    Tuple c1 = {1, 0.2, 0.4};
    Tuple c2 = {0.9, 1, 0.1};
    Tuple e = {0.9, 0.2, 0.04};
    Tuple mult;
    colors_multiply(c1, c2, mult);
    assert(tuple_compare(mult, e));
}

int main() {
    test_color_tuple();
    test_tuple_add_colors();
    test_tuple_subtract_colors();
    test_mutliply_color_by_scalar();
    test_multiple_two_colors();
}
