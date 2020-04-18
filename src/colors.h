#ifndef COLORS_H
#define COLORS_H

#include "tuples.h"

// Creates a new color with given rbg values
Tuple color(double red, double green, double blue);

// gets red value of color
double colors_red(Tuple c);

// gets green value of color
double colors_green(Tuple c);
//
// gets blue value of color
double colors_blue(Tuple c);

// multiplies 2 colors together
Tuple colors_multiply(Tuple c1, Tuple c2);

#endif
