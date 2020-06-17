#ifndef TUPLES_H
#define TUPLES_H

typedef double* Tuple;

Tuple ztuple();
void tuple_destroy(Tuple t);
double tuple_x(Tuple t);
double tuple_y(Tuple t);
double tuple_z(Tuple t);
double tuple_w(Tuple t);
Tuple tuple_point(double x, double y, double z);
Tuple tuple_vector(double x, double y, double z);
int tuple_is_point(Tuple t);
int tuple_is_vector(Tuple t);
int tuple_compare(Tuple t1, Tuple t2);
Tuple tuple_add(Tuple t1, Tuple t2);
Tuple tuple_subtract(Tuple t1, Tuple t2);
Tuple tuple_negate(Tuple t);
Tuple tuple_scale(Tuple t, double scalar);
Tuple tuple_dscale(Tuple t, double scalar);
Tuple tuple_normalize(Tuple t);
double tuple_magnitude(Tuple t);
double tuple_dot(Tuple v1, Tuple v2);
Tuple tuple_cross(Tuple v1, Tuple v2);

#endif
