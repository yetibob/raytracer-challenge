#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
#include "colors.h"
#include "tuples.h"

Canvas* canvas(int width, int height) {
    Canvas *c = malloc(sizeof(Canvas));
    c->width = width;
    c->height = height;
    int numPixels = width * height;
    c->pixels = malloc(sizeof(Tuple *) * numPixels);
    Tuple black = color(0, 0, 0);
    for (int i = 0; i < numPixels; i++) {
        c->pixels[i] = malloc(sizeof(double) * 4);
        *c->pixels[i] = *black;
    }
    return c;
}

void write_pixel(Canvas *c, int x, int y, Tuple color) {
    int pos = x * y;
    c->pixels[pos][0] = color[0];
    c->pixels[pos][1] = color[1];
    c->pixels[pos][2] = color[2];
}

Tuple pixel_at(Canvas c, int x, int y) {
    int pos = x*y;
    return c.pixels[pos];
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

char *canvas_to_ppm(Canvas c) {
    char *ppm = malloc(sizeof(char) * (c.height * c.width + 20));
    int pos = write_header(c, ppm);
    return ppm;
}
