#include <assert.h>
#include "../src/canvas.h"
#include "../src/utils.h"
#include "../src/colors.h"

void test_create_canvas() {
    Canvas *c = canvas(10, 20);
    assert(equals(c->width, 10) == 0);
    assert(equals(c->height, 20) == 0);
    Tuple black = color(0, 0, 0);
    for(int i = 0; i < c->width*c->height; i++) {
        assert(is_equal(c->pixels[i], black) == 0);
    }
}

int main() {
    test_create_canvas();
}
