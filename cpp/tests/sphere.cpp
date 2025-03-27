#include <assert.h>
#include <math.h>

#include "sphere.hpp"
#include "tuples.hpp"
#include "matrix.hpp"

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

void test_normal_on_translated_sphere() {
    Sphere s;
    sphere_init(&s);

    Matrix *t = matrix_translation(0, 1, 0);
    sphere_set_transform(&s, t);

    Tuple p = {0, 1.70711, -0.70711};
    tuple_point(p);

    Tuple norm;
    sphere_normal_at(&s, p, norm);

    Tuple e = {0, 0.70711, -0.70711};
    tuple_vector(e);
    
    assert(tuple_compare(e, norm));
}

void test_normal_on_transformed_sphere() {
    Sphere s;
    sphere_init(&s);

    Matrix *scal = matrix_scaling(1, 0.5, 1);
    Matrix *rot = matrix_rotation_z(M_PI/5);
    Matrix *t = matrix_multiply(scal, rot);
    sphere_set_transform(&s, t);

    Tuple p = {0, sqrt(2)/2, -(sqrt(2)/2)};
    tuple_point(p);

    Tuple norm;
    sphere_normal_at(&s, p, norm);

    Tuple e = {0, 0.97014, -0.24254};
    tuple_vector(e);
    
    assert(tuple_compare(e, norm));
}


int main() {
    test_sphere_normal_on_x_axis();
    test_sphere_normal_on_y_axis();
    test_sphere_normal_on_z_axis();
    test_sphere_normal_on_nonaxial();
    test_normal_is_always_normalized();
    test_normal_on_translated_sphere();
    return 0;
}
