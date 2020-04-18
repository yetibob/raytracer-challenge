#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "tuples.h"
#include "utils.h"

double tuple_x(Tuple t) {
    return t[0];
}

double tuple_y(Tuple t) {
    return t[1];
}

double tuple_z(Tuple t) {
    return t[2];
}

double tuple_w(Tuple t) {
    return t[3];
}

Tuple tuple() {
    return calloc(4, sizeof(double));
}

Tuple tuple_point(double x, double y, double z) {
    Tuple t = tuple();
    t[0] = x;
    t[1] = y;
    t[2] = z;
    t[3] = 1;
    return t;
}

int tuple_is_point(Tuple t) {
    if (tuple_w(t) == 1) {
        return 0;
    }
    return 1;
}

Tuple tuple_vector(double x, double y, double z) {
    Tuple t = tuple();
    t[0] = x;
    t[1] = y;
    t[2] = z;
    return t;
}

int tuple_is_vector(Tuple t) {
    if (tuple_w(t) == 0) {
        return 0;
    }
    return 1;
}

int tuple_compare(Tuple t1, Tuple t2) {
    for (int i = 0; i < 4; i++) {
        if (equals(t1[i], t2[i]) == 1) {
            return 1;
        }
    }
    return 0;
}

Tuple tuple_add(Tuple t1, Tuple t2) {
    Tuple t = tuple();
    for(int i = 0; i < 4; i++) {
        t[i] = t1[i] + t2[i];
    }
    return t;
}

Tuple tuple_subtract(Tuple t1, Tuple t2) {
    Tuple t = tuple();
    for (int i = 0; i < 4; i++) {
        t[i] = t1[i] - t2[i];
    }
    return t;
}

Tuple tuple_negate(Tuple t) {
    return tuple_subtract(tuple(), t);
}

Tuple tuple_scale(Tuple t, double scalar) {
    Tuple zt = tuple();
    zt[0] = t[0] * scalar;
    zt[1] = t[1] * scalar;
    zt[2] = t[2] * scalar;
    zt[3] = t[3];
    return zt;
}

Tuple tuple_dscale(Tuple t, double scalar) {
    Tuple zt = tuple();
    zt[0] = t[0] / scalar;
    zt[1] = t[1] / scalar;
    zt[2] = t[2] / scalar;
    zt[3] = t[3];
    return zt;
}

double tuple_magnitude(Tuple t) {
    double m = pow(t[0], 2) + pow(t[1], 2) + pow(t[2], 2) + pow(t[3], 2);
    return sqrt(m);
}

Tuple tuple_normalize(Tuple t) {
    double m = tuple_magnitude(t);
    Tuple normalized = tuple();
    normalized[0] = t[0] / m;
    normalized[1] = t[1] / m;
    normalized[2] = t[2] / m;
    normalized[3] = t[3];
    return normalized;
}

double tuple_dot(Tuple v1, Tuple v2) {
    double sum = 0;
    sum += tuple_x(v1) * tuple_x(v2);
    sum += tuple_y(v1) * tuple_y(v2);
    sum += tuple_z(v1) * tuple_z(v2);
    sum += tuple_w(v1) + tuple_w(v2);
    return sum;
}

Tuple tuple_cross(Tuple v1, Tuple v2) {
    Tuple rv = tuple();
    rv[0] = (tuple_y(v1) * tuple_z(v2)) - (tuple_z(v1) * tuple_y(v2));
    rv[1] = (tuple_z(v1) * tuple_x(v2)) - (tuple_x(v1) * tuple_z(v2));
    rv[2] = (tuple_x(v1) * tuple_y(v2)) - (tuple_y(v1) * tuple_x(v2));
    return rv;
}
