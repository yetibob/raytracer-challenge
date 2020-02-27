#ifndef COLORS_H
#define COLORS_H

#include "tuples.h"

Tuple color(double red, double green, double blue);
double red(Tuple c);
double green(Tuple c);
double blue(Tuple c);
Tuple multiply_colors(Tuple c1, Tuple c2);

#endif
