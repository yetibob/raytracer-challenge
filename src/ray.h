#include <stdlib.h>
#include "tuples.h"


typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;

// Create new array with given origin and direction
Ray *ray(Tuple origin, Tuple dir);

// Get ray position after given time `t`
Tuple ray_position(const Ray *r, double t);
