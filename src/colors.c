#include "colors.h"

double colors_red(Tuple c) {
    return c[0];
}

double colors_green(Tuple c) {
    return c[1];
}

double colors_blue(Tuple c) {
    return c[2];
}

void colors_multiply(Tuple c1, Tuple c2, Tuple res) {
    res[0] = c1[0] * c2[0];
    res[1] = c1[1] * c2[1];
    res[2] = c1[2] * c2[2];
}
