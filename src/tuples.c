#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include "tuples.h"
#include "utils.h"

// TODO: Consider making x/y/z/w functions return a double pointer
//       this would allow them to be used for easily setting tuple values as well
double x(Tuple t) {
    return t[0];
}

double y(Tuple t) {
    return t[1];
}

double z(Tuple t) {
    return t[2];
}

double w(Tuple t) {
    return t[3];
}

Tuple ztuple() {
    return calloc(4, sizeof(double));
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
    if (w(t) == 1) {
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
    if (w(t) == 1) {
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
    sum += x(v1) * x(v2);
    sum += y(v1) * y(v2);
    sum += z(v1) * z(v2);
    sum += w(v1) + w(v2);
    return sum;
}

Tuple cross(Tuple v1, Tuple v2) {
    Tuple rv = ztuple();
    rv[0] = (y(v1) * z(v2)) - (z(v1) * y(v2));
    rv[1] = (z(v1) * x(v2)) - (x(v1) * z(v2));
    rv[2] = (x(v1) * y(v2)) - (y(v1) * x(v2));
    return rv;
}
