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
