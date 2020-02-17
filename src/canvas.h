#include "tuples.h"

typedef struct {
    int height;
    int width;
    Tuple *pixels;
} Canvas;

Canvas* canvas(int width, int height);
