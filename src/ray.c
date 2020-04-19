#include "ray.h"

Ray *ray(Tuple origin, Tuple dir) {
    Ray *r = malloc(sizeof(Ray));
    r->origin = origin;
    r->direction = dir;
    return r;
}

Tuple ray_position(const Ray *r, double t) {
    return tuple_add(r->origin, tuple_scale(r->direction, t));
}
