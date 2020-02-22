#include <stdio.h>
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

void tick(struct Environment env, struct Projectile *proj) {
    proj->position = add(proj->position, proj->velocity);
    proj->velocity = add(proj->velocity, add(env.gravity, env.wind));
}

int main() {
    struct Projectile p = { point(0, 200 ,0), mscale(normalize(vector(1, 1, 0)), 11.5) };
    struct Environment e = { vector(0, -0.1, 0), vector(-0.01, 0, 0) };
    int ticks = 0;
	Canvas *c = canvas(1100, 900);
	char *ppm;
	Tuple pixel_color = color(0, 1, 0);
	
    while(y(p.position) > 0) {
        ticks++;
        tick(e, &p);
        write_pixel(c, x(p.position), c->height - y(p.position), pixel_color);
    }
	ppm = canvas_to_ppm(c);
	write_to_file("projectile.ppm", ppm);
}
