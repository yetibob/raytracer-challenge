#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
#include "colors.h"
#include "tuples.h"

Canvas* canvas(int width, int height) {
    Canvas *c = malloc(sizeof(Canvas));
    c->width = width;
    c->height = height;

    // c->pixels = malloc(sizeof(Tuple) * height);
    // for (int y = 0; y < height; y++) {
    //     c->pixels[y] = malloc(sizeof(Tuple) * width);
    //     for (int x = 0; x < width; x++) {
    //         c->pixels[y][x] = color(0, 0, 0);
    //     }
    // }

    int numPixels = c->width * c->height;
    c->pixels = malloc(sizeof(double) * numPixels * 4);
    for (int i = 0; i < numPixels * 4; i += 4) {
        c->pixels[i]   = 0;
        c->pixels[i+1] = 0;
        c->pixels[i+2] = 0;
        c->pixels[i+3] = 0;
    }
    return c;
}

void write_pixel(Canvas *c, int x, int y, Tuple color) {
    // c->pixels[y][x][0] = color[0];
    // c->pixels[y][x][1] = color[1];
    // c->pixels[y][x][2] = color[2];

    int pos = y * c->width + x;
    c->pixels[pos]   = color[0];
    c->pixels[pos+1] = color[1];
    c->pixels[pos+2] = color[2];
}

Tuple pixel_at(Canvas c, int x, int y) {
    // return c.pixels[y][x];

    int pos = y * c.width + x;
    return &c.pixels[pos];
}

static int write_header(Canvas c, char *s) {
    char buf[10];
    int i = 0;

    //set ppm flavor to P3
    s[i++] = 'P';
    s[i++] = '3';
    s[i++] = '\n';

    sprintf(buf, "%d", c.width);
    for (char *c = buf; *c != '\0'; c++) {
        s[i] = *c;
        i++;
    }

    s[i++] = ' ';

    sprintf(buf, "%d", c.height);
    for (char *c = buf; *c != '\0'; c++) {
        s[i] = *c;
        i++;
    }

    s[i++] = '\n';

    // set color range to 255
    s[i++] = '2';
    s[i++] = '5';
    s[i++] = '5';
    s[i++] = '\n';
    return i;
}

static int write_body(Canvas c, char *s) {
    // get color

    // convert color values from 0-1 floating to 0-255 int

    // convert to string of format "val val val"

    // write tuple to file
}

char *canvas_to_ppm(Canvas c) {
    int size = c.height * c.width * 5;
    char *ppm = malloc(sizeof(char) * size);
    int pos = write_header(c, ppm);
    write_body(c, ppm+pos);
    return ppm;
}
