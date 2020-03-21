#include <assert.h>
#include "../src/utils.h"

void test_compare_doubles() {
    int is_equal = equals(5.0, 5.1);
    assert(is_equal == 1);
    is_equal = equals(5.0, 5.000001);
    assert(is_equal == 0);
}

int main() {
    test_compare_doubles();
}
