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

// This was my first attempt at creating and writing a canvas
// It required manually allocating each row of the canvas
// and also did some dumb stuff when generating a ppm
//typedef struct {
//    int height;
//    int width;
//    Tuple **pixels;
//} InefficientCanvas;

// Returns a new canvas with the given width and height. All pixels initialize to black
Canvas* canvas(int width, int height);

// Writes a pixel to the canvas
void canvas_write(Canvas *c, int x, int y, Tuple color);
Tuple canvas_at(const Canvas *c, int x, int y);
char *canvas_gen_ppm(Canvas *c);

// InefficientCanvas* inefficient_canvas(int width, int height);
// void inefficient_write_pixel(InefficientCanvas *c, int x, int y, Tuple color);
// Tuple inefficient_pixel_at(const InefficientCanvas *c, int x, int y);
// char * inefficient_canvas_to_ppm(InefficientCanvas *c);

#endif
