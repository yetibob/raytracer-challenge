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

void test_write_pixel() {
    Canvas *c = canvas(10, 20);
    Tuple red = color(1, 0, 0);
    write_pixel(c, 2, 3, red);
    assert(is_equal(pixel_at(*c, 2, 3), red) == 0);
}

void test_canvas_to_ppm_header() {
    Canvas *c = canvas(5, 3);
    char *ppm = canvas_to_ppm(*c);
    char expected[] = {'P', '3', '\n', '5', ' ', '3', '\n', '2', '5', '5', '\n', '\0'};
    for (int i = 0; expected[i] != '\0'; i++) {
        assert(ppm[i] == expected[i]);
    }
}

int main() {
    test_create_canvas();
    test_write_pixel();
    test_canvas_to_ppm_header();
}
