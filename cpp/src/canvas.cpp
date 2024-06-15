#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.hpp"
#include "colors.hpp"
#include "tuples.hpp"

Canvas* canvas(int width, int height) {
    Canvas* c = malloc(sizeof(Canvas));
    c->width  = width;
    c->height = height;

    int numPixels = c->width * c->height;
    c->pixels     = malloc(sizeof(double) * numPixels * 4);
    for (int i = 0; i < numPixels * 4; i += 4) {
        c->pixels[i]     = 0;
        c->pixels[i + 1] = 0;
        c->pixels[i + 2] = 0;
        c->pixels[i + 3] = 0;
    }
    return c;
}

void canvas_destroy(Canvas* c) {
    free(c->pixels);
    free(c);
}

void canvas_init(Canvas* c, int width, int height) {
    c->width  = width;
    c->height = height;

    int numPixels = c->width * c->height;
    c->pixels     = malloc(sizeof(double) * numPixels * 4);
    for (int i = 0; i < numPixels * 4; i += 4) {
        c->pixels[i]     = 0;
        c->pixels[i + 1] = 0;
        c->pixels[i + 2] = 0;
        c->pixels[i + 3] = 0;
    }
}

void canvas_free(Canvas* c) {
    free(c->pixels);
}

void canvas_write(Canvas* c, int x, int y, const Tuple color) {
    if (x >= c->width || x < 0 || y >= c->height || y < 0) {
        return;
    }
    int pos = (y * c->width + x) * 4;
    if (pos + 2 >= c->height * c->width * 4) {
        return;
    }

    c->pixels[pos]     = color[0];
    c->pixels[pos + 1] = color[1];
    c->pixels[pos + 2] = color[2];
}

double* canvas_at(const Canvas* c, int x, int y) {
    if (x >= c->width || x < 0 || y >= c->height || y < 0) {
        return NULL;
    }

    double* r = malloc(sizeof(double) * TUPLE_LEN);

    int pos = (y * c->width + x) * 4;
    if (pos + 2 >= c->height * c->width * 4) {
        r[0] = -1;
        r[1] = -1;
        r[2] = -1;
        r[3] = -1;
        return r;
    }
    for (int i = 0; i < TUPLE_LEN; i++) {
        r[i] = c->pixels[pos + i];
    }
    return r;
}

static int write_header(Canvas* c, char* ppm) {
    char buf[10];
    int  i = 0;

    // set ppm flavor to P3
    ppm[i++] = 'P';
    ppm[i++] = '3';
    ppm[i++] = '\n';

    sprintf(buf, "%d", c->width);
    for (char* c = buf; *c != '\0'; c++) {
        ppm[i++] = *c;
    }

    ppm[i++] = ' ';

    sprintf(buf, "%d", c->height);
    for (char* c = buf; *c != '\0'; c++) {
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

static int write_body(Canvas* c, char* ppm, int line_length) {
    int  convPix;
    int  skipPix = 0;
    char buf[5];

    int pos  = 0;
    int lpos = 0;

    // make line length 0 based
    line_length--;
    int cpos  = 0;
    int csize = c->height * c->width * 4;

    double* pixel = c->pixels;

    while (cpos < csize) {
        if (skipPix == 3) {
            cpos++;
            pixel++;

            skipPix = 0;
            continue;
        }

        convPix = *pixel * 255;
        sprintf(buf, "%d ", convPix);
        int len = strlen(buf);

        if (lpos + len > line_length) {
            lpos         = 0;
            ppm[pos - 1] = '\n';
        } else if (lpos + len == line_length) {
            buf[len - 1] = '\n';
        }

        for (char* c = buf; *c != '\0'; c++) {
            ppm[pos++] = *c;
            lpos++;
        }

        pixel++;
        cpos++;
        skipPix++;
    }
    ppm[pos - 1] = '\n';
    ppm[pos]     = '\0';
    return pos - 1;
}

char* canvas_gen_ppm(Canvas* c) {
    int   size       = c->height * c->width * 15;
    char* ppm        = malloc(sizeof(char) * size);
    int   header_pos = write_header(c, ppm);
    write_body(c, ppm + header_pos, 70);
    return ppm;
}

