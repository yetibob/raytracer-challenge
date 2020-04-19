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

void canvas_destroy(Canvas *c) {
    free(c->pixels);
    free(c);
}

void canvas_write(Canvas *c, int x, int y, Tuple color) {
	if (x >= c->width || x < 0 || y >= c->height || y < 0) { return; }
    int pos = (y * c->width + x) * 4;
	if (pos+2 >= c->height * c->width * 4) { return; }

    c->pixels[pos]   = color[0];
    c->pixels[pos+1] = color[1];
    c->pixels[pos+2] = color[2];
}

Tuple canvas_at(const Canvas *c, int x, int y) {
	if (x >= c->width || x < 0 || y >= c->height || y < 0) {
			return color(0, 0, 0);
	}

    int pos = (y * c->width + x) * 4;
	if (pos+2 >= c->height * c->width * 4) {
			return tuple_point(-1, -1, -1);
	}

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

static int write_body(Canvas *c, char *ppm, int line_length) {
    int convPix;
    int skipPix = 0;
    char buf[5];

    int pos = 0;
    int lpos = 0;

    // make line length 0 based
    line_length--;
    int cpos = 0;
    int csize = c->height * c->width * 4;

    double *pixel = c->pixels;


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
            lpos = 0;
            ppm[pos-1] = '\n';
        } else if (lpos + len == line_length) {
            buf[len-1] = '\n';
        }

        for (char *c = buf; *c != '\0'; c++) {
            ppm[pos++] = *c;
            lpos++;
        }

        pixel++;
        cpos++;
        skipPix++;
    }
    ppm[pos-1] = '\n';
    ppm[pos] = '\0';
    return pos-1;
}

// split file was used as an inefficient line split after creating
// an unsplit ppm
/*
static void split_file(char *ppm, int len) {
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (pos == 69) {
            if (ppm[i] != ' ') {
                for (; ppm[i] != ' '; i--)
                    ;
            }
            ppm[i] = '\n';
            pos = 0;
        }
        pos++;
    }
}
*/

char *canvas_gen_ppm(Canvas *c) {
    int size = c->height * c->width * 15;
    char *ppm = malloc(sizeof(char) * size);
    int header_pos = write_header(c, ppm);
    write_body(c, ppm+header_pos, 70);
    // int pos = write_body(c, ppm+header_pos, 70);
    // split_file(ppm+header_pos, pos);
    // ppm[header_pos+pos] = '\n';
    return ppm;
}

/*
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
*/
