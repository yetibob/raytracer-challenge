#include <stdlib.h>

#include "sphere.h"

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

// void sphere_destroy(Sphere *s) {
//     free(s);
// }
