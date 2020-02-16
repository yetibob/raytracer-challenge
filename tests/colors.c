#include <assert.h>
#include "../src/colors.h"
#include "../src/utils.h"

void test_color_tuple() {
    Tuple c = color(-0.5, 0.4, 1.7);
    assert(equals(red(c), -0.5) == 0);
    assert(equals(green(c), 0.4) == 0);
    assert(equals(blue(c), 1.7) == 0);
}

int main() {
    test_color_tuple();
}
