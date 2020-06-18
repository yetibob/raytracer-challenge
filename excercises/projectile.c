#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/tuples.h"
#include "../src/canvas.h"
#include "../src/colors.h"
#include "../src/utils.h"

struct Projectile {
    Tuple position;
    Tuple velocity;
};

struct Environment {
    Tuple gravity;
    Tuple wind;
};

void tick(struct Environment env, struct Projectile *proj, Tuple add) {
    Tuple tmp;
    tuple_add(proj->position, proj->velocity, tmp);
    memcpy(proj->position, tmp, sizeof(double) * TUPLE_LEN);
    
    tuple_add(proj->velocity, add, tmp);
    memcpy(proj->velocity, tmp, sizeof(double) * TUPLE_LEN);
}

int main() {
    Tuple s = {1, 1.8, 0};
    tuple_vector(s);

    Tuple norm;
    tuple_normalize(s, norm);

    Tuple scaled;
    tuple_scale(norm, scaled, 11.25);

    struct Projectile p = { .position = {0, 1 ,0}};
    memcpy(p.velocity, scaled, sizeof(double) * TUPLE_LEN);
    tuple_point(p.position);
    tuple_vector(p.velocity);

    struct Environment e = { .gravity={0, -0.1, 0}, .wind={-0.01, 0, 0} };
    tuple_vector(e.gravity);
    tuple_vector(e.wind);
    Tuple add;
    tuple_add(e.gravity, e.wind, add);
    Canvas *c = canvas(900, 550);
    char *ppm;
    Tuple pixel_color = {0, 1, 0};
	
    while(tuple_y(p.position) > 0) {
        tick(e, &p, add);
        canvas_write(c, tuple_x(p.position), c->height - tuple_y(p.position), pixel_color);
    }
    ppm = canvas_gen_ppm(c);
    write_to_file("projectile.ppm", ppm);
}
