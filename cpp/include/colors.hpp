#ifndef COLORS_H
#define COLORS_H

#include "tuples.hpp"

// gets red value of color
double colors_red(Tuple c);

// gets green value of color
double colors_green(Tuple c);
//
// gets blue value of color
double colors_blue(Tuple c);

// multiplies 2 colors together
void colors_multiply(Tuple c1, Tuple c2, Tuple res);

#endif
