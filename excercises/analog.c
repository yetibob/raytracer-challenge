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
        .origin = point(25, 0, 25),
        .hour = point(0, 0, 1)
    };

    Canvas *c = canvas(50, 50);
    Tuple pixel_color = color(1, 1, 1);

    Matrix *m = rotation_y(M_PI/6);
    double radius = c->width * (3.0/8.0);

    for (int i = 0; i < 12; i++) {
        Tuple loc = mscale(clock.hour, radius);
        loc = add(loc, clock.origin);
        write_pixel(c, x(loc), z(loc), pixel_color);
        clock.hour = multiply_matrix_with_tuple(m, clock.hour);
    }

    char *ppm = canvas_to_ppm(c);
    write_to_file("analog.ppm", ppm);
}
