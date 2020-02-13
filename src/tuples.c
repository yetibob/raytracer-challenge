#include <stdlib.h>
#include "tuples.h"

Tuple *point(double x, double y, double z) {
    Tuple *t = malloc(sizeof(Tuple));
    t->x = x;
    t->y = y;
    t->z = z;
    t->w = 1;
    return t;
}

Tuple *vector(double x, double y, double z) {
    Tuple *t = malloc(sizeof(Tuple));
    t->x = x;
    t->y = y;
    t->z = z;
    t->w = 0;
    return t;
}
