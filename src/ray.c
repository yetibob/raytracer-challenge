#include <math.h>
#include "ray.h"

Ray *ray(Tuple origin, Tuple dir) {
    Ray *r = malloc(sizeof(Ray));
    r->origin = origin;
    r->direction = dir;
    return r;
}

void destroy_ray(Ray *r) {
    free(r->origin);
    free(r->direction);
    free(r);
}

Tuple ray_position(const Ray *r, double t) {
    return tuple_add(r->origin, tuple_scale(r->direction, t));
}

Sphere *ray_sphere() {
    static int id = 0;
    Sphere *s = malloc(sizeof(Sphere));
    s->id = id++;
    s->origin = tuple_point(0, 0, 0);
    return s;
}

void ray_spher_destroy(Sphere *s) {
    free(s->origin);
    free(s);
}

Intersection *ray_intersection() {
    Intersection *i = malloc(sizeof(Intersection));
    i->count = 2;
    i->data = malloc(sizeof(double) * 2);
    return i;
}

void ray_intersection_destroy(Intersection *i) {
    free(i->data);
    free(i);
}

Intersection *ray_intersect(Sphere *s, Ray *r) {
    Tuple sphere_to_ray = tuple_subtract(r->origin, s->origin);

    double dot = tuple_dot(r->direction, r->direction);
    double dot2 = 2 * tuple_dot(r->direction, sphere_to_ray);
    double dot3 = tuple_dot(sphere_to_ray, sphere_to_ray) - 1;

    double discriminant = (dot2*dot2) - 4 * dot * dot3;

    Intersection *xs = ray_intersection();
    if (discriminant < 0) {
       xs->count = -1; 
       return xs;
    }
    
    double t1 = (-dot2 - sqrt(discriminant)) / (2*dot);
    double t2 = (-dot2 + sqrt(discriminant)) / (2*dot);
    xs->count = 2;
    if (t1 <= t2) {
        xs->data[0] = t1;
        xs->data[1] = t2;
    } else {
        xs->data[0] = t2;
        xs->data[1] = t1;
    }
    return xs;
}
