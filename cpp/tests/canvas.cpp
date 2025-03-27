#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "canvas.hpp"
#include "utils.hpp"
#include "colors.hpp"

void test_create_canvas() {
    Canvas *c = canvas(10, 20);
    assert(equals(c->width, 10));
    assert(equals(c->height, 20));

    Tuple black = {0, 0, 0};
    for(int i = 0; i < c->width * c->height * 4; i += 4) {
        assert(tuple_compare(c->pixels+i, black));
    }
}

void test_canvas_write() {
    Canvas *c = canvas(10, 20);
    Tuple c1 = {0, 0, 1};
    canvas_write(c, 2, 3, c1);
    assert(tuple_compare(canvas_at(c, 2, 3), c1));
}

void test_canvas_gen_ppm_header() {
    Canvas *c = canvas(5, 3);
    char *ppm = canvas_gen_ppm(c);
    char expected[] = "P3\n5 3\n255\n";
    for (int i = 0; expected[i] != '\0'; i++) {
        assert(ppm[i] == expected[i]);
    }
}

void test_canvas_gen_ppm_pixel_data() {
    Canvas *c = canvas(10, 2);
    Tuple c1 = {1, 0.8, 0.6};
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 2; y++) {
            canvas_write(c, x, y, c1);
        }
    }
    char expected[] = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255\n204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153\n";

    char *ppm = canvas_gen_ppm(c);
    int i = 0;
    int line = 0;

    for (; line < 3; i++) {
        if (ppm[i] == '\n') {
            line++;
        }
    }
    assert(strcmp(ppm+i, expected) == 0);
}

/*
void test_write_to_file() {
    const int width = 5, height = 3;
    Canvas *c = canvas(width, height);
    Tuple c1 = color(1, 0.8, 0.6);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            canvas_write(c, x, y, c1);
        }
    }
    char *ppm = canvas_gen_ppm(c);
    int len = strlen(ppm);
    FILE *fp = fopen("img.ppm", "w");
    fwrite(ppm, sizeof(char), len, fp);
    fclose(fp);
}
*/

int main() {
    test_create_canvas();
    test_canvas_write();
    test_canvas_gen_ppm_header();
    test_canvas_gen_ppm_pixel_data();
    // test_write_to_file();
}
