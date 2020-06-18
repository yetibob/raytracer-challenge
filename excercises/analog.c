#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/canvas.h"
#include "../src/matrix.h"
#include "../src/tuples.h"
#include "../src/colors.h"
#include "../src/utils.h"

struct Clock {
    Tuple origin;
    Tuple hour;
};

int main() {
    struct Clock clock = {
        .origin = {25, 25, 0},
        .hour = {0, 1, 0}
    };

    tuple_point(clock.origin);
    tuple_point(clock.hour);

    Canvas *c = canvas(50, 50);
    Tuple pixel_color = {1, 1, 1};

    Matrix *m = matrix_rotation_z(M_PI/6);
    double radius = c->width * (3.0/8.0);

    for (int i = 0; i < 12; i++) {
        Tuple scaled;
        tuple_scale(clock.hour, scaled, radius);

        Tuple loc;
        tuple_add(scaled, clock.origin, loc);
        canvas_write(c, tuple_x(loc), tuple_y(loc), pixel_color);

        Tuple new_hour;
        matrix_multiply_tuple(m, clock.hour, new_hour);
        memcpy(clock.hour, new_hour, sizeof(double) * TUPLE_LEN);
    }

    char *ppm = canvas_gen_ppm(c);
    write_to_file("analog.ppm", ppm);
}
