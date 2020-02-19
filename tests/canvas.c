#include <assert.h>
#include <stdio.h>
#include "../src/canvas.h"
#include "../src/utils.h"
#include "../src/colors.h"

void test_create_canvas() {
    Canvas *c = canvas(10, 20);
    assert(equals(c->width, 10) == 0);
    assert(equals(c->height, 20) == 0);
    Tuple black = color(0, 0, 0);
    // for(int y = 0; y < c->height; y++) {
    //     for(int x = 0; x < c->width; x++) {
    //         assert(is_equal(c->pixels[y][x], black) == 0);
    //     }
    // }

    for(int i = 0; i < c->width * c->height * 4; i += 4) {
        assert(is_equal(c->pixels+i, black) == 0);
    }
}

void test_write_pixel() {
    Canvas *c = canvas(10, 20);
    Tuple c1 = color(0, 0, 1);
    write_pixel(c, 2, 3, c1);
    assert(is_equal(pixel_at(*c, 2, 3), c1) == 0);
}

void test_canvas_to_ppm_header() {
    Canvas *c = canvas(5, 3);
    char *ppm = canvas_to_ppm(*c);
    char expected[] = "P3\n5 3\n255\n";
    for (int i = 0; expected[i] != '\0'; i++) {
        assert(ppm[i] == expected[i]);
    }
}

void test_canvas_to_ppm_pixel_data() {
    Canvas *c = canvas(5, 3);
    Tuple c1 = color(1.5, 0, 0);
    Tuple c2 = color(0, 0.5, 0);
    Tuple c3 = color(-0.5, 0, 1);
    char expected[] = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n \
                       0 0 0 0 0 0 128 0 0 0 0 0 0 0 0\n \
                       0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    write_pixel(c, 0, 0, c1);
    write_pixel(c, 2, 1, c2);
    write_pixel(c, 4, 2, c3);
    char *ppm = canvas_to_ppm(*c);
    int i = 0;
    int line = 0;

    // walk i up to correct start of line 4
    for (i; line < 4; i++) {
        if (ppm[i] == '\n') {
            line++;
        }
    }

    // start comparing strings at i
    for (i; expected[i] != '\0'; i++) {
        assert(ppm[i] == expected[i]);
    }

}

int main() {
    test_create_canvas();
    test_write_pixel();
    test_canvas_to_ppm_header();
    // test_canvas_to_ppm_pixel_data();
}
