#include <stdio.h>
#include "../src/tuples.h"

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
    struct Projectile p = { point(0, 1 ,0), normalize(vector(1, 1, 0)) };
    struct Environment e = { vector(0, -0.1, 0), vector(-0.01, 0, 0) };
    int ticks = 0;

    while(p.position[1] > 0) {
        ticks++;
        tick(e, &p);
        printf("X: %f\tY: %f\tZ: %f\n", p.position[0], p.position[1], p.position[2]);
    }
    printf("Ticks to hit ground: %d\n", ticks);
}
