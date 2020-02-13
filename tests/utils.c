#include <assert.h>
#include "../src/utils.h"

void test_compare_doubles() {
    int is_equal = equal(5.0, 5.1);
    assert(is_equal == 1);
    is_equal = equal(5.0, 5.000001);
    assert(is_equal == 0);
}

void main() {
    test_compare_doubles();
}
