#ifndef RAY_H
#define RAY_H

#include "tuples.h"
#include "matrix.h"
#include "sphere.h"

typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;


typedef struct Intersection {
    double t;
    void *object;
} Intersection;

// Create new array with given origin and direction
Ray *ray_transform(const Ray *r, const Matrix *m);
void ray_destroy(Ray *r);
// Get ray position after given time `t`
void ray_position(const Ray *r, double t, Tuple res);

void ray_intersection_destroy(Intersection *i);

// Returns an array of length 2 that contains intersection pointers
// The sphere pointer is not const because it must be assigned to
// Intersection.object, which is not const
Intersection **ray_intersect(Sphere *s, const Ray *r, int *count); 

// Generates an array of intersection pointers of num length
Intersection **ray_intersections(int num, ...);
Intersection *ray_hit(Intersection *xs[], int count);

#endif
