#include <stdio.h>
#include <stdlib.h>
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
    Tuple freePos = proj->position;
    Tuple freeVol = proj->velocity;
    
    proj->position = tuple_add(proj->position, proj->velocity);
    proj->velocity = tuple_add(proj->velocity, add);

    free(freePos);
    free(freeVol);
}

int main() {
    struct Projectile p = { tuple_point(0, 200 ,0), tuple_scale(tuple_normalize(tuple_vector(1, 1, 0)), 11.5) };
    struct Environment e = { tuple_vector(0, -0.1, 0), tuple_vector(-0.01, 0, 0) };
    Tuple add = tuple_add(e.gravity, e.wind);
    int ticks = 0;
    Canvas *c = canvas(700, 400);
    char *ppm;
    Tuple pixel_color = color(0, 1, 0);
	
    while(tuple_y(p.position) > 0) {
        ticks++;
        tick(e, &p, add);
        canvas_write(c, tuple_x(p.position), c->height - tuple_y(p.position), pixel_color);
    }
    ppm = canvas_gen_ppm(c);
    write_to_file("projectile.ppm", ppm);
}
