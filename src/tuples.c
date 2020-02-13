#include <stdlib.h>
#include <stddef.h>
#include "tuples.h"

Tuple point(double x, double y, double z) {
    Tuple t = malloc(sizeof(double) * 4);
    if (!t) {
        return NULL;
    }
    t[0] = x;
    t[1] = y;
    t[2] = z;
    t[3] = 1.0;
    return t;
}

int is_point(Tuple t) {
    if (t[3] == 1) {
        return 0;
    }
    return 1;
}

Tuple vector(double x, double y, double z) {
    Tuple t = malloc(sizeof(double) * 4);
    t[0] = x;
    t[1] = y;
    t[2] = z;
    t[3] = 0.0;
    return t;
}

int is_vector(Tuple t) {
    if (t[3] == 1.0) {
        return 0;
    }
    return 1;
}
