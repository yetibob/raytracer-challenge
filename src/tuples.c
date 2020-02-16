#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "tuples.h"
#include "utils.h"

Tuple ztuple() {
    Tuple t = malloc(sizeof(double) * 4);
    t[0] = 0;
    t[1] = 0;
    t[2] = 0;
    t[3] = 0;
    return t;
}

Tuple point(double x, double y, double z) {
    Tuple t = ztuple();
    t[0] = x;
    t[1] = y;
    t[2] = z;
    t[3] = 1;
    return t;
}

int is_point(Tuple t) {
    if (t[3] == 1) {
        return 0;
    }
    return 1;
}

Tuple vector(double x, double y, double z) {
    Tuple t = ztuple();
    t[0] = x;
    t[1] = y;
    t[2] = z;
    return t;
}

int is_vector(Tuple t) {
    if (t[3] == 1.0) {
        return 0;
    }
    return 1;
}

int is_equal(Tuple t1, Tuple t2) {
    for (int i = 0; i < 4; i++) {
        if (equals(t1[i], t2[i]) == 1) {
            return 1;
        }
    }
    return 0;
}

Tuple add(Tuple t1, Tuple t2) {
    Tuple t = ztuple();
    for(int i = 0; i < 4; i++) {
        t[i] = t1[i] + t2[i];
    }
    return t;
}

Tuple subtract(Tuple t1, Tuple t2) {
    Tuple t = ztuple();
    for (int i = 0; i < 4; i++) {
        t[i] = t1[i] - t2[i];
    }
    return t;
}

Tuple negate(Tuple t) {
    return subtract(ztuple(), t);
}

Tuple mscale(Tuple t, double scalar) {
    Tuple zt = ztuple();
    zt[0] = t[0] * scalar;
    zt[1] = t[1] * scalar;
    zt[2] = t[2] * scalar;
    zt[3] = t[3];
    return zt;
}

Tuple dscale(Tuple t, double scalar) {
    Tuple zt = ztuple();
    zt[0] = t[0] / scalar;
    zt[1] = t[1] / scalar;
    zt[2] = t[2] / scalar;
    zt[3] = t[3];
    return zt;
}

double magnitude(Tuple t) {
    double m = pow(t[0], 2) + pow(t[1], 2) + pow(t[2], 2) + pow(t[3], 2);
    return sqrt(m);
}

Tuple normalize(Tuple t) {
    double m = magnitude(t);
    Tuple normalized = ztuple();
    normalized[0] = t[0] / m;
    normalized[1] = t[1] / m;
    normalized[2] = t[2] / m;
    normalized[3] = t[3];
    return normalized;
}

double dot(Tuple v1, Tuple v2) {
    double sum = 0;
    sum += v1[0] * v2[0];
    sum += v1[1] * v2[1];
    sum += v1[2] * v2[2];
    sum += v1[3] + v2[3];
    return sum;
}

Tuple cross(Tuple v1, Tuple v2) {
    Tuple rv = ztuple();
    rv[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    rv[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    rv[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    return rv;
}
