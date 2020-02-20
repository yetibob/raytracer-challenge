#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canvas.h"
#include "colors.h"
#include "tuples.h"

Canvas* canvas(int width, int height) {
    Canvas *c = malloc(sizeof(Canvas));
    c->width = width;
    c->height = height;

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
    int pos = (x * c->height + y) * 4;
    c->pixels[pos]   = color[0];
    c->pixels[pos+1] = color[1];
    c->pixels[pos+2] = color[2];
}

Tuple pixel_at(const Canvas *c, int x, int y) {
    int pos = (x * c->height + y) * 4;
    return &c->pixels[pos];
}

static int write_header(Canvas *c, char *ppm) {
    char buf[10];
    int i = 0;

    //set ppm flavor to P3
    ppm[i++] = 'P';
    ppm[i++] = '3';
    ppm[i++] = '\n';

    sprintf(buf, "%d", c->width);
    for (char *c = buf; *c != '\0'; c++) {
        ppm[i++] = *c;
    }

    ppm[i++] = ' ';

    sprintf(buf, "%d", c->height);
    for (char *c = buf; *c != '\0'; c++) {
        ppm[i++] = *c;
    }

    ppm[i++] = '\n';

    // set color range to 255
    ppm[i++] = '2';
    ppm[i++] = '5';
    ppm[i++] = '5';
    ppm[i++] = '\n';
    return i;
}

static int write_color(char *ppm, int pos, int color) {
    char buf[5];
    if (color > 255) {
        color = 255;
    } else if (color < 0) {
        color = 0;
    }
    sprintf(buf, "%d ", color);

    // int line = pos / 69;
    int offset = pos % 69;
    int end_pos = offset + strlen(buf);
    printf("%s\t:\t%d\t:\t%d\n", buf, offset, pos);
    if (end_pos >= 69) {
        ppm[pos-1] = '\n';
    }

    for(char *c = buf; *c != '\0'; c++) {
        ppm[pos++] = *c;
    }
    return pos;
}

static int write_body(Canvas *c, char *ppm) {
    int pos = 0;

    int canvas_size = c->width * c->height  * 4;
    for (int i = 0; i < canvas_size; i+=4) {
        int c1 = c->pixels[i] * 255;
        int c2 = c->pixels[i+1] * 255;
        int c3 = c->pixels[i+2] * 255;

        pos = write_color(ppm, pos, c1);
        pos = write_color(ppm, pos, c2);
        pos = write_color(ppm, pos, c3);
    }
    ppm[pos-1] = '\n';
    ppm[pos] = '\0';
    return pos;
}

char *canvas_to_ppm(Canvas *c) {
    int size = c->height * c->width * 15;
    char *ppm = malloc(sizeof(char) * size);
    int pos = write_header(c, ppm);
    pos += write_body(c, ppm+pos);
    return ppm;
}

InefficientCanvas* inefficient_canvas(int width, int height) {
    InefficientCanvas *c = malloc(sizeof(InefficientCanvas));
    c->width = width;
    c->height = height;

    c->pixels = malloc(sizeof(Tuple) * height);
    for (int x = 0; x < width; x++) {
        c->pixels[x] = malloc(sizeof(Tuple) * height);
        for (int y = 0; y < width; y++) {
            c->pixels[x][y] = color(0, 0, 0);
        }
    }

    return c;
}

void inefficient_write_pixel(InefficientCanvas *c, int x, int y, Tuple color) {
    c->pixels[x][y][0] = color[0];
    c->pixels[x][y][1] = color[1];
    c->pixels[x][y][2] = color[2];
}

Tuple inefficient_pixel_at(const InefficientCanvas *c, int x, int y) {
    return c->pixels[x][y];
}
