#include "tuples.h"

typedef struct {
    int height;
    int width;
    Tuple **pixels;
} Canvas;

Canvas* canvas(int width, int height);
void write_pixel(Canvas *c, int x, int y, Tuple color);
Tuple pixel_at(const Canvas c, int x, int y);
char * canvas_to_ppm(Canvas c);
