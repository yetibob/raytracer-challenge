#include <assert.h>
#include <stddef.h>

#include "../src/ray.h"
#include "../src/matrix.h"
#include "../src/tuples.h"
#include "../src/utils.h"
#include "../src/sphere.h"

void test_create_and_query_ray() {
    Ray r = {.origin = {1, 2, 3}, .direction = {4, 5, 6}};
    tuple_point(r.origin);
    tuple_vector(r.direction);

    Tuple origin_e = {1, 2, 3};
    tuple_point(origin_e);

    Tuple dir_e = {4, 5, 6};
    tuple_vector(dir_e);

    assert(tuple_compare(r.origin, origin_e));
    assert(tuple_compare(r.direction, dir_e));
}

void test_compute_a_point_from_a_distance() {
    Ray r = {
        .origin = {2, 3, 4},
        .direction = {1, 0, 0}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);
    
    Tuple p1;
    ray_position(&r, 0, p1);
    Tuple p2;
    ray_position(&r, 1, p2);
    Tuple p3;
    ray_position(&r, -1, p3);
    Tuple p4;
    ray_position(&r, 2.5, p4);

    Tuple e1 = {2, 3, 4};
    tuple_point(e1);
    Tuple e2 = {3, 3, 4};
    tuple_point(e2);
    Tuple e3 = {1, 3, 4};
    tuple_point(e3);
    Tuple e4 = {4.5, 3, 4};
    tuple_point(e4);

    assert(tuple_compare(e1, p1));
    assert(tuple_compare(e2, p2));
    assert(tuple_compare(e3, p3));
    assert(tuple_compare(e4, p4));
}

void test_ray_intersects_a_sphere_at_two_points() {
    Ray r = {
        .origin = {0, 0, -5},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);

    Sphere s;
    sphere_init(&s);

    int count;
    Intersection **xs = ray_intersect(&s, &r, &count);

    assert(equals(count, 2));
    assert(equals(xs[0]->t, 4.0));
    assert(equals(xs[1]->t, 6.0));
}

void test_ray_intersects_sphere_at_tangent() {
    Ray r = {
        .origin = {0, 1, -5},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);
    
    Sphere s;
    sphere_init(&s);

    int count;
    Intersection **xs = ray_intersect(&s, &r, &count);
    assert(equals(count, 2));
    assert(equals(xs[0]->t, 5.0));
    assert(equals(xs[1]->t, 5.0));
}

void test_ray_misses_a_sphere() {
    Ray r = {
        .origin = {0, 2, -5},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);
    
    Sphere s;
    sphere_init(&s);
    int count;
    Intersection **xs = ray_intersect(&s, &r, &count);
    assert(count == 0);
    assert(xs == NULL);
}

void test_ray_originates_in_a_sphere() {
    Ray r = {
        .origin = {0, 0, 0},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);
    
    Sphere s;
    sphere_init(&s);
    int count;
    Intersection **xs = ray_intersect(&s, &r, &count);
    assert(equals(count, 2));
    assert(equals(xs[0]->t, -1.0));
    assert(equals(xs[1]->t, 1.0));
}

void test_sphere_is_behind_ray() {
    Ray r = {
        .origin = {0, 0, 5},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);

    Sphere s;
    sphere_init(&s);

    int count;
    Intersection **xs = ray_intersect(&s, &r, &count);
    assert(equals(count, 2));
    assert(equals(xs[0]->t, -6.0));
    assert(equals(xs[1]->t, -4.0));
}

void test_intersection_encapsulates_t_and_object() {
    Sphere s;
    sphere_init(&s);

    Intersection i = { .t=3.5, .object=&s };
    assert(equals(i.t, 3.5));
    assert(i.object == &s);
}

void test_aggregating_intersections() {
    Sphere s;
    sphere_init(&s);

    Intersection i1 = { .t=1, .object=&s };
    Intersection i2 = { .t=2, .object=&s };
    Intersection **xs = ray_intersections(2, &i1, &i2);
    assert(equals(xs[0]->t, 1));
    assert(equals(xs[1]->t, 2));
}

void test_intersect_sets_the_object_on_the_intersection() {
    Ray r = {
        .origin = {0, 0, -5},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);
    
    Sphere s;
    sphere_init(&s);
    int count;
    Intersection **xs = ray_intersect(&s,& r, &count);
    assert(xs[0]->object == &s);
    assert(xs[1]->object == &s);
}

void test_ray_hit_when_all_intersections_are_positive() {
    Sphere s;
    sphere_init(&s);

    Intersection i1 = { 1, &s };
    Intersection i2 = { 2, &s };
    Intersection **xs = ray_intersections(2, &i2, &i1);
    assert(ray_hit(xs, 2) == &i1);
}

void test_ray_hit_when_some_intersections_are_negative() {
    Sphere s;
    sphere_init(&s);
    
    Intersection i1 = { -1, &s };
    Intersection i2 = { 1, &s };
    Intersection **xs = ray_intersections(2, &i2, &i1);
    assert(ray_hit(xs, 2) == &i2);
}

void test_ray_hit_when_all_intersections_are_negative() {
    Sphere s;
    sphere_init(&s);

    Intersection i1 = { -2, &s };
    Intersection i2 = { -1, &s };
    Intersection **xs = ray_intersections(2, &i1, &i2);
    assert(ray_hit(xs, 2) == NULL);
}

void test_ray_hit_is_always_the_lowest_non_negative_intersection() {
    Sphere s;
    sphere_init(&s);

    Intersection i1 = { 5, &s };
    Intersection i2 = { 7, &s };
    Intersection i3 = { -3, &s };
    Intersection i4 = { 2, &s };
    Intersection **xs = ray_intersections(4, &i1, &i2, &i3, &i4);
    assert(ray_hit(xs, 4) == &i4);
}

void test_translating_a_ray() {
    Ray r = {
        .origin = {1, 2, 3},
        .direction = {0, 1, 0}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);

    Matrix *m = matrix_translation(3, 4, 5);
    Ray *r2 = ray_transform(&r, m);

    Tuple e1 = {4, 6, 8};
    tuple_point(e1);

    Tuple e2 = {0, 1, 0};
    tuple_vector(e2);

    assert(tuple_compare(r2->origin, e1));
    assert(tuple_compare(r2->direction, e2));
}

void test_scaling_a_ray() {
    Ray r = {
        .origin = {1, 2, 3},
        .direction = {0, 1, 0}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);
    
    Matrix *m = matrix_scaling(2, 3, 4);
    Ray *r2 = ray_transform(&r, m);

    Tuple e1 = {2, 6, 12};
    tuple_point(e1);

    Tuple e2 = {0, 3, 0};
    tuple_vector(e2);
    
    assert(tuple_compare(r2->origin, e1));
    assert(tuple_compare(r2->direction, e2));
}

void test_sphere_default_transformation() {
    Sphere s;
    sphere_init(&s);

    assert(matrix_compare(s.transform, matrix_IdentityMatrix()));
}

void test_changing_a_spheres_transformation() {
    Sphere s;
    sphere_init(&s);

    Matrix *t = matrix_translation(2, 3, 4);
    sphere_set_transform(&s, t);
    assert(matrix_compare(s.transform, t));
}

void test_intersecting_a_scaled_sphere_with_a_ray() {
    Ray r = {
        .origin = {0, 0, -5},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);

    Sphere s;
    sphere_init(&s);

    sphere_set_transform(&s, matrix_scaling(2, 2, 2));
    int count;
    Intersection **xs = ray_intersect(&s, &r, &count);
    assert(count == 2);
    assert(equals(xs[0]->t, 3));
    assert(equals(xs[1]->t, 7));
}

void test_intersecting_a_translated_sphere_with_a_ray() {
    Ray r = {
        .origin = {0, 0, -5},
        .direction = {0, 0, 1}
    };

    tuple_point(r.origin);
    tuple_vector(r.direction);

    Sphere s;
    sphere_init(&s);

    sphere_set_transform(&s, matrix_translation(5, 0, 0));
    int count;
    ray_intersect(&s, &r, &count);
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
