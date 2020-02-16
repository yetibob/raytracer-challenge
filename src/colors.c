#include "colors.h"

double red(Tuple c) {
    return c[0];
}

double green(Tuple c) {
    return c[1];
}

double blue(Tuple c) {
    return c[2];
}

Tuple color(double red, double green, double blue) {
    Tuple c = ztuple();
    c[0] = red;
    c[1] = green;
    c[2] = blue;
    c[3] = 0;
    return c;
}

Tuple multiply_colors(Tuple c1, Tuple c2) {
    Tuple nc = ztuple();
    nc[0] = c1[0] * c2[0];
    nc[1] = c1[1] * c2[1];
    nc[2] = c1[2] * c2[2];
    return nc;
}
