#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/canvas.h"
#include "../src/utils.h"
#include "../src/colors.h"

void test_create_canvas() {
    Canvas *c = canvas(10, 20);
    assert(equals(c->width, 10) == 0);
    assert(equals(c->height, 20) == 0);

    Tuple black = color(0, 0, 0);
    for(int i = 0; i < c->width * c->height * 4; i += 4) {
        assert(is_equal(c->pixels+i, black) == 0);
    }
}

void test_write_pixel() {
    Canvas *c = canvas(10, 20);
    Tuple c1 = color(0, 0, 1);
    write_pixel(c, 2, 3, c1);
    assert(is_equal(pixel_at(c, 2, 3), c1) == 0);
}

void test_canvas_to_ppm_header() {
    Canvas *c = canvas(5, 3);
    char *ppm = canvas_to_ppm(c);
    char expected[] = "P3\n5 3\n255\n";
    for (int i = 0; expected[i] != '\0'; i++) {
        assert(ppm[i] == expected[i]);
    }
}

void test_canvas_to_ppm_pixel_data() {
    Canvas *c = canvas(10, 2);
    Tuple c1 = color(1, 0.8, 0.6);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 2; y++) {
            write_pixel(c, x, y, c1);
        }
    }
    char expected[] = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255\n204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153\n";

    char *ppm = canvas_to_ppm(c);
    int i = 0;
    int line = 0;
    for (i; line < 3; i++) {
        if (ppm[i] == '\n') {
            line++;
        }
    }
    assert(strcmp(ppm+i, expected) == 0);

}

void test_inefficient_create_canvas() {
    InefficientCanvas *c = inefficient_canvas(10, 20);
    assert(equals(c->width, 10) == 0);
    assert(equals(c->height, 20) == 0);

    Tuple black = color(0, 0, 0);
    for(int x = 0; x < c->width; x++) {
        for(int y = 0; y < c->height; y++) {
            assert(is_equal(c->pixels[x][y], black) == 0);
        }
    }
}

void test_inefficient_write_pixel() {
    InefficientCanvas *c = inefficient_canvas(10, 20);
    Tuple c1 = color(0, 0, 1);
    inefficient_write_pixel(c, 2, 3, c1);
    assert(is_equal(inefficient_pixel_at(c, 2, 3), c1) == 0);
}

void test_write_to_file() {
    Canvas *c = canvas(6, 5);
    Tuple c1 = color(1, 0.8, 0.6);
    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 5; y++) {
            write_pixel(c, x, y, c1);
        }
    }
    char *ppm = canvas_to_ppm(c);
    int len = strlen(ppm);
    FILE *fp = fopen("img.ppm", "w");
    fwrite(ppm, sizeof(char), len, fp);
    fclose(fp);
}

int main() {
    test_create_canvas();
    test_write_pixel();
    test_canvas_to_ppm_header();
    test_canvas_to_ppm_pixel_data();
    test_write_to_file();
}
