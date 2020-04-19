#include <stdlib.h>
#include "tuples.h"

typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;

typedef struct Sphere {
   int id; 
   Tuple origin;
} Sphere;

typedef struct Intersection {
    int count;
    double *data;
} Intersection;

// Create new array with given origin and direction
Ray *ray(Tuple origin, Tuple dir);
void destroy_ray(Ray *r);
// Get ray position after given time `t`
Tuple ray_position(const Ray *r, double t);

Sphere *ray_sphere();
void ray_sphere_destroy(Sphere *s);

Intersection *ray_intersect(Sphere *s, Ray *r); 
void ray_intersection_destroy(Intersection *i);
