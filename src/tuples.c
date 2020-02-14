#include <stdlib.h>
#include <stddef.h>
#include "tuples.h"
#include "utils.h"

Tuple tuple() {
    Tuple t = malloc(sizeof(double) * 4);
    t[0] = 0;
    t[1] = 0;
    t[2] = 0;
    t[3] = 0;
    return t;
}

Tuple point(double x, double y, double z) {
    Tuple t = malloc(sizeof(double) * 4);
    if (!t) {
        return NULL;
    }
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
    Tuple t = malloc(sizeof(double) * 4);
    t[0] = x;
    t[1] = y;
    t[2] = z;
    t[3] = 0;
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

Tuple add_tuples(Tuple t1, Tuple t2) {
    Tuple t = tuple();
    for(int i = 0; i < 4; i++) {
        t[i] = t1[i] + t2[i];
    }
    return t;
}

Tuple subtract_tuples(Tuple t1, Tuple t2) {
    Tuple t = tuple();
    for (int i = 0; i < 4; i++) {
        t[i] = t1[i] - t2[i];
    }
    return t;
}
