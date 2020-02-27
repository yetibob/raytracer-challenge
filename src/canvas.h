#ifndef CANVAS_H
#define CANVAS_H

#include "tuples.h"

typedef struct {
    int height;
    int width;
    double *pixels;
} Canvas;

typedef struct {
    int height;
    int width;
    Tuple **pixels;
} InefficientCanvas;

Canvas* canvas(int width, int height);
void write_pixel(Canvas *c, int x, int y, Tuple color);
Tuple pixel_at(const Canvas *c, int x, int y);
char * canvas_to_ppm(Canvas *c);

InefficientCanvas* inefficient_canvas(int width, int height);
void inefficient_write_pixel(InefficientCanvas *c, int x, int y, Tuple color);
Tuple inefficient_pixel_at(const InefficientCanvas *c, int x, int y);
// char * inefficient_canvas_to_ppm(InefficientCanvas *c);

#endif
