#include <assert.h>
#include <math.h>

#include "../src/sphere.h"
#include "../src/tuples.h"

void test_sphere_normal_on_x_axis() {
    Sphere s;
    sphere_init(&s);

    Tuple point = {1, 0, 0};
    tuple_point(point);

    Tuple normal;
    sphere_normal_at(&s, point, normal);

    Tuple e = {1, 0, 0};
    tuple_vector(e);

    assert(tuple_compare(e, normal));
}

void test_sphere_normal_on_y_axis() {
    Sphere s;
    sphere_init(&s);

    Tuple point = {0, 1, 0};
    tuple_point(point);

    Tuple normal;
    sphere_normal_at(&s, point, normal);

    Tuple e = {0, 1, 0};
    tuple_vector(e);

    assert(tuple_compare(e, normal));
}

void test_sphere_normal_on_z_axis() {
    Sphere s;
    sphere_init(&s);

    Tuple point = {0, 0, 1};
    tuple_point(point);

    Tuple normal;
    sphere_normal_at(&s, point, normal);

    Tuple e = {0, 0, 1};
    tuple_vector(e);

    assert(tuple_compare(e, normal));
}

void test_sphere_normal_on_nonaxial() {
    Sphere s;
    sphere_init(&s);

    Tuple point = {sqrt(3)/3, sqrt(3)/3, sqrt(3)/3};
    tuple_point(point);

    Tuple normal;
    sphere_normal_at(&s, point, normal);

    Tuple e = {sqrt(3)/3, sqrt(3)/3 , sqrt(3)/3};
    tuple_vector(e);

    assert(tuple_compare(e, normal));
}

void test_normal_is_always_normalized() {
    Sphere s;
    sphere_init(&s);

    Tuple point = {sqrt(3)/3, sqrt(3)/3, sqrt(3)/3};
    tuple_point(point);

    Tuple normal;
    sphere_normal_at(&s, point, normal);

    Tuple e;
    tuple_normalize(normal, e);

    assert(tuple_compare(normal, e));
}

int main() {
    test_sphere_normal_on_x_axis();
    test_sphere_normal_on_y_axis();
    test_sphere_normal_on_z_axis();
    test_sphere_normal_on_nonaxial();
    test_normal_is_always_normalized();
    return 0;
}
