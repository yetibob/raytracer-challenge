#include <stdlib.h>

#include "sphere.h"
#include "matrix.h"

void sphere_init(Sphere *s) {
    static int id = 0;
    s->id = id++;
    s->origin[0] = 0;
    s->origin[1] = 0;
    s->origin[2] = 0;
    tuple_point(s->origin);
    s->transform = matrix_IdentityMatrix();
}

void sphere_set_transform(Sphere *s, const Matrix *m) {
    s->transform = m;
}

void sphere_normal_at(const Sphere *s, const Tuple p, Tuple res) {
    Matrix *inv = matrix_inverse(s->transform);
    Tuple op;
    matrix_multiply_tuple(inv, p, op);

    Tuple orig = {0, 0, 0};
    tuple_point(orig);
    
    Tuple object_normal;
    tuple_subtract(op, orig, object_normal);

    Matrix *tp = matrix_transpose(inv);

    Tuple world_normal;
    matrix_multiply_tuple(tp, object_normal, world_normal);

    world_normal[3] = 0;
    tuple_normalize(world_normal, res);
    matrix_destroy(inv);
    matrix_destroy(tp);
}

// void sphere_destroy(Sphere *s) {
//     free(s);
// }
