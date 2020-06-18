#ifndef RAY_H
#define RAY_H

#include <stdlib.h>
#include "tuples.h"
#include "matrix.h"

typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;

// Never create a sphere without calling `ray_sphere` unless you
// can guarantee a unique id for the sphere
typedef struct Sphere {
   int id; 
   Tuple origin;
   Matrix *transform;
} Sphere;

typedef struct Intersection {
    double t;
    void *object;
} Intersection;

// Create new array with given origin and direction
Ray *ray_transform(const Ray *r, const Matrix *m);
void ray_destroy(Ray *r);
// Get ray position after given time `t`
void ray_position(const Ray *r, double t, TuplePtr res);

void *ray_sphere_init(Sphere *s);
// int ray_sphere_compare(const Sphere *s1, const Sphere *s2);
void ray_sphere_destroy(Sphere *s);
void ray_sphere_set_transform(Sphere *s, Matrix *m);

void ray_intersection_destroy(Intersection *i);

// Returns an array of length 2 that contains intersection pointers
// The sphere pointer is not const because it must be assigned to
// Intersection.object, which is not const
Intersection **ray_intersect(Sphere *s, const Ray *r, int *count); 

// Generates an array of intersection pointers of num length
Intersection **ray_intersections(int num, ...);
Intersection *ray_hit(Intersection *xs[], int count);

#endif
