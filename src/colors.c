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
    c[3] = 2;
    return c;
}
