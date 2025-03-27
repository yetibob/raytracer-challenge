#include <assert.h>
#include "utils.hpp"

void test_compare_doubles() {
    int is_equal = equals(5.0, 5.1);
    assert(is_equal== 0);
    is_equal = equals(5.0, 5.000001);
    assert(is_equal);
}

int main() {
    test_compare_doubles();
}
