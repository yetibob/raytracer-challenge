#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.hpp"
#include "colors.hpp"
#include "tuples.hpp"
#include "utils.hpp"

struct Projectile {
    Tuple position;
    Tuple velocity;
};

struct Environment {
    Tuple gravity;
    Tuple wind;
};

void tick(struct Environment env, struct Projectile* proj, Tuple add) {
    Tuple tmp;
    tuple_add(proj->position, proj->velocity, tmp);
    memcpy(proj->position, tmp, sizeof(double) * TUPLE_LEN);

    tuple_add(proj->velocity, add, tmp);
    memcpy(proj->velocity, tmp, sizeof(double) * TUPLE_LEN);
}

int main() {
    Tuple s = { 1, 1.8, 0, VEC };

    Tuple norm;
    tuple_normalize(s, norm);

    Tuple scaled;
    tuple_scale(norm, scaled, 11.25);

    struct Projectile p = { .position = { 0, 1, 0, POINT } };
    memcpy(p.velocity, scaled, sizeof(double) * TUPLE_LEN);
    tuple_vector(p.velocity);

    struct Environment e = { .gravity = { 0, -0.1, 0, VEC }, .wind = { -0.01, 0, 0, VEC } };

    Tuple add;
    tuple_add(e.gravity, e.wind, add);
    Canvas* c = canvas(900, 550);
    char*   ppm;
    Tuple   pixel_color = { 0, 1, 0 };

    while (tuple_y(p.position) > 0) {
        tick(e, &p, add);
        canvas_write(c, tuple_x(p.position), c->height - tuple_y(p.position), pixel_color);
    }
    ppm = canvas_gen_ppm(c);
    write_to_file("projectile.ppm", ppm);
}
