#include <math.h>
#include <stdarg.h>
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

void ray_sphere_destroy(Sphere *s) {
    free(s->origin);
    free(s);
}

//Intersection *ray_intersection() {
//    Intersection *i = malloc(sizeof(Intersection));
//    i->t = 0;
//    i->object = NULL;
//    return i;
//}

void ray_intersection_destroy(Intersection *i) {
    free(i->object);
    free(i);
}

Intersection **ray_intersect(Sphere *s, const Ray *r, int *count) {
    Tuple sphere_to_ray = tuple_subtract(r->origin, s->origin);

    double dot = tuple_dot(r->direction, r->direction);
    double dot2 = 2 * tuple_dot(r->direction, sphere_to_ray);
    double dot3 = tuple_dot(sphere_to_ray, sphere_to_ray) - 1;

    double discriminant = (dot2*dot2) - 4 * dot * dot3;

    if (discriminant < 0) {
       *count = -1; 
       return NULL;
    }


    
    double t1 = (-dot2 - sqrt(discriminant)) / (2*dot);
    double t2 = (-dot2 + sqrt(discriminant)) / (2*dot);
    *count = 2;

    Intersection *i1 = malloc(sizeof(Intersection));
    Intersection *i2= malloc(sizeof(Intersection));
    i1->object = s;
    i2->object = s;

    if (t1 <= t2) {
        i1->t = t1;
        i2->t = t2;
    } else {
        i1->t = t2;
        i2->t = t1;
    }
    
    Intersection **arr = ray_intersections(2, i1, i2);

    return arr;
}

Intersection **ray_intersections(int num, ...) {
    va_list valist;
    Intersection **arr = malloc(sizeof(Intersection *) * num);
    va_start(valist, num);

    for (int i = 0; i < num; i++) {
        arr[i] = va_arg(valist, Intersection *);
    }

    va_end(valist);
    return arr;
}
