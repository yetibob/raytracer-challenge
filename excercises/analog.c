#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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
        .origin = tuple_point(25, 25, 0),
        .hour = tuple_point(0, 1, 0)
    };

    Canvas *c = canvas(50, 50);
    Tuple pixel_color = color(1, 1, 1);

    Matrix *m = matrix_rotation_z(M_PI/6);
    double radius = c->width * (3.0/8.0);

    for (int i = 0; i < 12; i++) {
        Tuple loc = tuple_scale(clock.hour, radius);
        Tuple freeScaled = loc;

        loc = tuple_add(loc, clock.origin);
        canvas_write(c, tuple_x(loc), tuple_y(loc), pixel_color);

        Tuple freeHour = clock.hour;
        clock.hour = matrix_multiply_tuple(m, clock.hour);

        free(loc);
        free(freeScaled);
        free(freeHour);
    }

    char *ppm = canvas_gen_ppm(c);
    write_to_file("analog.ppm", ppm);
}
