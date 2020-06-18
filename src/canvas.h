#ifndef CANVAS_H
#define CANVAS_H

#include "tuples.h"

// The canvas is where we write our pixel data to. It has a height, a width, and an array of pixels
// The pixel array is of length height * width and is the flat equivalent to pixels[x][y]
typedef struct {
    int height;
    int width;
    double *pixels;
} Canvas;

// Returns a new canvas with the given width and height. All pixels initialize to black
Canvas* canvas(int width, int height);
void canvas_destroy(Canvas *c);

void canvas_init(Canvas *c, int width, int height);
void canvas_free(Canvas *c);

// Writes a pixel to the canvas
void canvas_write(Canvas *c, int x, int y, const Tuple color);
double *canvas_at(const Canvas *c, int x, int y);
char *canvas_gen_ppm(Canvas *c);

#endif
