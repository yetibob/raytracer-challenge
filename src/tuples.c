#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "tuples.h"
#include "utils.h"

double tuple_x(const Tuple t) {
    return t[0];
}

double tuple_y(const Tuple t) {
    return t[1];
}

double tuple_z(const Tuple t) {
    return t[2];
}

double tuple_w(const Tuple t) {
    return t[3];
}

void tuple_point(Tuple t){
    t[3] = 1;
}

int tuple_is_point(const Tuple t) {
    if (equals(tuple_w(t), 1)) {
        return 1;
    }
    return 0;
}

void tuple_vector(Tuple t) {
    t[3] = 0;
}

int tuple_is_vector(const Tuple t) {
    if (equals(tuple_w(t), 0)) {
        return 1;
    }
    return 0;
}

int tuple_compare(const Tuple t1, const Tuple t2) {
    for (int i = 0; i < TUPLE_LEN; i++) {
        if (!equals(t1[i], t2[i])) {
            return 0;
        }
    }
    return 1;
}

void tuple_add(const Tuple t1, const Tuple t2, Tuple res) {
    for(int i = 0; i < TUPLE_LEN; i++) {
        res[i] = t1[i] + t2[i];
    }
}

void tuple_subtract(const Tuple t1, const Tuple t2, Tuple res) {
    for (int i = 0; i < TUPLE_LEN; i++) {
        res[i] = t1[i] - t2[i];
    }
}

void tuple_negate(const Tuple t, Tuple res) {
    Tuple zt = {0};
    tuple_subtract(zt, t, res);
}

void tuple_scale(const Tuple t, Tuple res, double scalar) {
    res[0] = t[0] * scalar;
    res[1] = t[1] * scalar;
    res[2] = t[2] * scalar;
    res[3] = t[3];
}

void tuple_dscale(const Tuple t, Tuple res, double scalar) {
    res[0] = t[0] / scalar;
    res[1] = t[1] / scalar;
    res[2] = t[2] / scalar;
    res[3] = t[3];
}

double tuple_magnitude(const Tuple t) {
    double m = pow(t[0], 2) + pow(t[1], 2) + pow(t[2], 2) + pow(t[3], 2);
    return sqrt(m);
}

void tuple_normalize(const Tuple t, Tuple res) {
    double m = tuple_magnitude(t);
    res[0] = t[0] / m;
    res[1] = t[1] / m;
    res[2] = t[2] / m;
    res[3] = t[3];
}

double tuple_dot(const Tuple v1, const Tuple v2) {
    double sum = 0;
    sum += tuple_x(v1) * tuple_x(v2);
    sum += tuple_y(v1) * tuple_y(v2);
    sum += tuple_z(v1) * tuple_z(v2);
    sum += tuple_w(v1) + tuple_w(v2);
    return sum;
}

void tuple_cross(const Tuple v1, const Tuple v2, Tuple res) {
    res[0] = (tuple_y(v1) * tuple_z(v2)) - (tuple_z(v1) * tuple_y(v2));
    res[1] = (tuple_z(v1) * tuple_x(v2)) - (tuple_x(v1) * tuple_z(v2));
    res[2] = (tuple_x(v1) * tuple_y(v2)) - (tuple_y(v1) * tuple_x(v2));
}
