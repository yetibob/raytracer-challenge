#include <stdio.h>
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
    Tuple ray_origin = tuple_point(0, 0, -5);

    Sphere *s = ray_sphere();
    // Tuple center = tuple_point(25, 25, 0);
    Tuple hit_pixel = color(1, 0, 0);
    int count;

    for (int y=0; y < c->height; y++) {
        double world_y = half - pixel_size * y;
        for (int x=0; x < c->width; x++) {
            double world_x = -half + pixel_size * x;
            Tuple pos = tuple_point(world_x, world_y, wall_z);
            Ray *r = ray(ray_origin, tuple_normalize(tuple_subtract(pos, ray_origin)));
            Intersection **xs = ray_intersect(s, r, &count);
            if (ray_hit(xs, count) != NULL) {
                canvas_write(c, x, y, hit_pixel);
            } 
        }
    }

    char *ppm = canvas_gen_ppm(c);
    write_to_file("shadow.ppm", ppm);
    return 0;
}