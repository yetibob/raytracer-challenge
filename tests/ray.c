#include <assert.h>
#include "../src/ray.h"
#include "../src/matrix.h"
#include "../src/tuples.h"
#include "../src/utils.h"

void test_create_and_query_ray() {
    Tuple origin = tuple_point(1, 2, 3);
    Tuple dir = tuple_vector(4, 5, 6);
    Ray *r = ray(origin, dir);
    assert(tuple_compare(r->origin, origin) == 0);
    assert(tuple_compare(r->direction, dir) == 0);
}

void test_compute_a_point_from_a_distance() {
    Ray *r = ray(tuple_point(2, 3, 4), tuple_vector(1, 0, 0));
    
    Tuple p1 = ray_position(r, 0);
    Tuple p2 = ray_position(r, 1);
    Tuple p3 = ray_position(r, -1);
    Tuple p4 = ray_position(r, 2.5);

    Tuple e1 = tuple_point(2, 3, 4);
    Tuple e2 = tuple_point(3, 3, 4);
    Tuple e3 = tuple_point(1, 3, 4);
    Tuple e4 = tuple_point(4.5, 3, 4);

    assert(tuple_compare(e1, p1) == 0);
    assert(tuple_compare(e2, p2) == 0);
    assert(tuple_compare(e3, p3) == 0);
    assert(tuple_compare(e4, p4) == 0);
}

void test_ray_intersects_a_sphere_at_two_points() {
    Ray *r = ray(tuple_point(0, 0, -5), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    int count;
    Intersection **xs = ray_intersect(s, r, &count);
    assert(equals(count, 2) == 0);
    assert(equals(xs[0]->t, 4.0) == 0);
    assert(equals(xs[1]->t, 6.0) == 0);
}

void test_ray_intersects_sphere_at_tangent() {
    Ray *r = ray(tuple_point(0, 1, -5), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    int count;
    Intersection **xs = ray_intersect(s, r, &count);
    assert(equals(count, 2) == 0);
    assert(equals(xs[0]->t, 5.0) == 0);
    assert(equals(xs[1]->t, 5.0) == 0);
}

void test_ray_misses_a_sphere() {
    Ray *r = ray(tuple_point(0, 2, -5), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    int count;
    Intersection **xs = ray_intersect(s, r, &count);
    assert(count == 0);
    assert(xs == NULL);
}

void test_ray_originates_in_a_sphere() {
    Ray *r = ray(tuple_point(0, 0, 0), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    int count;
    Intersection **xs = ray_intersect(s, r, &count);
    assert(equals(count, 2) == 0);
    assert(equals(xs[0]->t, -1.0) == 0);
    assert(equals(xs[1]->t, 1.0) == 0);
}

void test_sphere_is_behind_ray() {
    Ray *r = ray(tuple_point(0, 0, 5), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    int count;
    Intersection **xs = ray_intersect(s, r, &count);
    assert(equals(count, 2) == 0);
    assert(equals(xs[0]->t, -6.0) == 0);
    assert(equals(xs[1]->t, -4.0) == 0);
}

void test_intersection_encapsulates_t_and_object() {
    Sphere *s = ray_sphere();
    Intersection i = { .t=3.5, .object=s };
    assert(equals(i.t, 3.5) == 0);
    assert(i.object == s);
}

void test_aggregating_intersections() {
    Sphere *s = ray_sphere();
    Intersection i1 = { .t=1, .object=s };
    Intersection i2 = { .t=2, .object=s };
    Intersection **xs = ray_intersections(2, &i1, &i2);
    assert(equals(xs[0]->t, 1) == 0);
    assert(equals(xs[1]->t, 2) == 0);
}

void test_intersect_sets_the_object_on_the_intersection() {
    Ray *r = ray(tuple_point(0, 0, -5), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    int count;
    Intersection **xs = ray_intersect(s, r, &count);
    assert(xs[0]->object == s);
    assert(xs[1]->object == s);
}

void test_ray_hit_when_all_intersections_are_positive() {
    Sphere *s = ray_sphere();
    Intersection i1 = { 1, s };
    Intersection i2 = { 2, s };
    Intersection **xs = ray_intersections(2, &i2, &i1);
    assert(ray_hit(xs, 2) == &i1);
}

void test_ray_hit_when_some_intersections_are_negative() {
    Sphere *s = ray_sphere();
    Intersection i1 = { -1, s };
    Intersection i2 = { 1, s };
    Intersection **xs = ray_intersections(2, &i2, &i1);
    assert(ray_hit(xs, 2) == &i2);
}

void test_ray_hit_when_all_intersections_are_negative() {
    Sphere *s = ray_sphere();
    Intersection i1 = { -2, s };
    Intersection i2 = { -1, s };
    Intersection **xs = ray_intersections(2, &i1, &i2);
    assert(ray_hit(xs, 2) == NULL);
}

void test_ray_hit_is_always_the_lowest_non_negative_intersection() {
    Sphere *s = ray_sphere();
    Intersection i1 = { 5, s };
    Intersection i2 = { 7, s };
    Intersection i3 = { -3, s };
    Intersection i4 = { 2, s };
    Intersection **xs = ray_intersections(4, &i1, &i2, &i3, &i4);
    assert(ray_hit(xs, 4) == &i4);
}

void test_translating_a_ray() {
    Ray *r = ray(tuple_point(1, 2, 3), tuple_vector(0, 1, 0));
    Matrix *m = matrix_translation(3, 4, 5);
    Ray *r2 = ray_transform(r, m);
    assert(tuple_compare(r2->origin, tuple_point(4, 6, 8)) == 0);
    assert(tuple_compare(r2->direction, tuple_vector(0, 1, 0)) == 0);
}

void test_scaling_a_ray() {
    Ray *r = ray(tuple_point(1, 2, 3), tuple_vector(0, 1, 0));
    Matrix *m = matrix_scaling(2, 3, 4);
    Ray *r2 = ray_transform(r, m);
    assert(tuple_compare(r2->origin, tuple_point(2, 6, 12)) == 0);
    assert(tuple_compare(r2->direction, tuple_vector(0, 3, 0)) == 0);
}

void test_sphere_default_transformation() {
    Sphere *s = ray_sphere();
    assert(matrix_compare(s->transform, matrix_IdentityMatrix()) == 0);
}

void test_changing_a_spheres_transformation() {
    Sphere *s = ray_sphere();
    Matrix *t = matrix_translation(2, 3, 4);
    ray_sphere_set_transform(s, t);
    assert(matrix_compare(s->transform, t) == 0);
}

void test_intersecting_a_scaled_sphere_with_a_ray() {
    Ray *r = ray(tuple_point(0, 0, -5), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    ray_sphere_set_transform(s, matrix_scaling(2, 2, 2));
    int count;
    Intersection **xs = ray_intersect(s, r, &count);
    assert(count == 2);
    assert(equals(xs[0]->t, 3) == 0 );
    assert(equals(xs[1]->t, 7) == 0 );
}

void test_intersecting_a_translated_sphere_with_a_ray() {
    Ray *r = ray(tuple_point(0, 0, -5), tuple_vector(0, 0, 1));
    Sphere *s = ray_sphere();
    ray_sphere_set_transform(s, matrix_translation(5, 0, 0));
    int count;
    ray_intersect(s, r, &count);
    assert(count == 0);
}

int main() {
    test_create_and_query_ray();
    test_compute_a_point_from_a_distance();
    test_ray_intersects_a_sphere_at_two_points();
    test_ray_intersects_sphere_at_tangent();
    test_ray_misses_a_sphere();
    test_ray_originates_in_a_sphere();
    test_sphere_is_behind_ray();
    test_intersection_encapsulates_t_and_object();
    test_aggregating_intersections();
    test_intersect_sets_the_object_on_the_intersection();
    test_ray_hit_when_all_intersections_are_positive();
    test_ray_hit_when_some_intersections_are_negative();
    test_ray_hit_when_all_intersections_are_negative();
    test_ray_hit_is_always_the_lowest_non_negative_intersection();
    test_translating_a_ray();
    test_scaling_a_ray();
    test_sphere_default_transformation();
    test_changing_a_spheres_transformation();
    test_intersecting_a_scaled_sphere_with_a_ray();
    test_intersecting_a_translated_sphere_with_a_ray();
}
