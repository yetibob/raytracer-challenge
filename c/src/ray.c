#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "ray.h"
#include "matrix.h"

Ray *ray_transform(const Ray *r, const Matrix *m) {
    Ray *tr = malloc(sizeof(Ray));
    matrix_multiply_tuple(m, r->origin, tr->origin);
    matrix_multiply_tuple(m, r->direction, tr->direction);
    return tr;
}

void ray_destroy(Ray *r) {
    free(r);
}

void ray_position(const Ray *r, double t, Tuple res) {
    Tuple tmp;
    tuple_scale(r->direction, tmp, t);
    tuple_add(r->origin, tmp, res);
}


void ray_intersection_destroy(Intersection *i) {
    free(i);
}

Intersection **ray_intersect(Sphere *s, const Ray *r, int *count) {
    Matrix *in = matrix_inverse(s->transform);
    Ray *t = ray_transform(r, in);
    Tuple sphere_to_ray;
    tuple_subtract(t->origin, s->origin, sphere_to_ray);

    double dot = tuple_dot(t->direction, t->direction);
    double dot2 = 2 * tuple_dot(t->direction, sphere_to_ray);
    double dot3 = tuple_dot(sphere_to_ray, sphere_to_ray) - 1;

    double discriminant = (dot2*dot2) - 4 * dot * dot3;

    ray_destroy(t);
    matrix_destroy(in);
    if (discriminant < 0) {
        *count = 0; 
        return NULL;
    }

    double t1 = (-dot2 - sqrt(discriminant)) / (2*dot);
    double t2 = (-dot2 + sqrt(discriminant)) / (2*dot);
    *count = 2;

    Intersection *i1 = malloc(sizeof(Intersection));
    Intersection *i2 = malloc(sizeof(Intersection));
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

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = 1; i < num; i++) {
            if (arr[i-1]->t > arr[i]->t) {
                swapped = 1;
                Intersection *tmp = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = tmp;
            }
        }
    }
    return arr;
}

Intersection *ray_hit(Intersection *xs[], int count) {
    for (int i = 0; i < count; i++) {
        if (xs[i]->t >= 0) {
            return xs[i];
        }
    }    
    return NULL;
}
