#include <assert.h>
#include "../src/colors.h"
#include "../src/utils.h"

void test_color_tuple() {
    Tuple c = color(-0.5, 0.4, 1.7);
    assert(equals(red(c), -0.5) == 0);
    assert(equals(green(c), 0.4) == 0);
    assert(equals(blue(c), 1.7) == 0);
}

void test_add_colors() {
    Tuple c1 = color(0.9, 0.6, 0.75);
    Tuple c2 = color(0.7, 0.1, 0.25);
    Tuple e = color(1.6, 0.7, 1);
    assert(is_equal(add(c1, c2), e) == 0);
}

void test_subtract_colors() {
    Tuple c1 = color(0.9, 0.6, 0.75);
    Tuple c2 = color(0.7, 0.1, 0.25);
    Tuple e = color(0.2, 0.5, 0.5);
    assert(is_equal(subtract(c1, c2), e) == 0);
}

void test_mutliply_color_by_scalar() {
    Tuple c1 = color(0.2, 0.3, 0.4);
    Tuple e = color(0.4, 0.6, 0.8);
    assert(is_equal(mscale(c1, 2), e) == 0);
}

void test_multiple_two_colors() {
    Tuple c1 = color(1, 0.2, 0.4);
    Tuple c2 = color(0.9, 1, 0.1);
    Tuple e = color(0.9, 0.2, 0.04);
    assert(is_equal(multiply_colors(c1, c2), e) == 0);
}

int main() {
    test_color_tuple();
    test_add_colors();
    test_subtract_colors();
    test_mutliply_color_by_scalar();
    test_multiple_two_colors();
}
