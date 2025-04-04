#ifndef SPHERE_H
#define SPHERE_H

#include "tuples.hpp"
#include "matrix.hpp"

// Never create a sphere without calling `ray_sphere_init` unless you
// can guarantee a unique id for the sphere
typedef struct Sphere {
   int id; 
   Tuple origin;
   const Matrix *transform;
} Sphere;

void sphere_init(Sphere *s);

// int ray_sphere_compare(const Sphere *s1, const Sphere *s2);
void sphere_destroy(Sphere *s);
void sphere_set_transform(Sphere *s, const Matrix *m);

void sphere_normal_at(const Sphere *s, const Tuple p, Tuple res);

#endif
