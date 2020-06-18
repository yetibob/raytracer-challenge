#include <stdio.h>
#include <string.h>
#include "../src/ray.h"
#include "../src/canvas.h"
#include "../src/matrix.h"
#include "../src/tuples.h"
#include "../src/colors.h"
#include "../src/utils.h"

int main() {
    double wall_z = 10;
    double wall_size = 7;
    double canvas_pixels = 100;
    double pixel_size = wall_size / canvas_pixels;
    double half = wall_size / 2;

    Canvas *c = canvas(canvas_pixels, canvas_pixels);
    Tuple ray_origin = {0, 0, -5};
    tuple_point(ray_origin);

    Sphere s;
    ray_sphere_init(&s);
    Tuple hit_pixel = {1, 0, 0};
    int count;

    for (int y = 0; y < c->height; y++) {
        double world_y = half - pixel_size * y;
        for (int x = 0; x < c->width; x++) {
            double world_x = -half + pixel_size * x;
            Tuple pos = {world_x, world_y, wall_z};
            tuple_point(pos);
            Tuple tmp = {0};
            memcpy(tmp, ray_origin, sizeof(double)*TUPLE_LEN);

            Tuple dir;
            tuple_subtract(pos, tmp, dir);

            Tuple norm_dir;
            tuple_normalize(dir, norm_dir);

            Ray r;
            memcpy(r.origin, tmp, sizeof(double)*TUPLE_LEN);
            memcpy(r.direction, norm_dir, sizeof(double)*TUPLE_LEN);

            Intersection **xs = ray_intersect(&s, &r, &count);
            if (ray_hit(xs, count) != NULL) {
                canvas_write(c, x, y, hit_pixel);
            } 
            for (int i = 0; i < count; i++) {
                ray_intersection_destroy(xs[i]);
            }
            free(xs);
        }
    }

    char *ppm = canvas_gen_ppm(c);
    write_to_file("shadow.ppm", ppm);
    return 0;
}
