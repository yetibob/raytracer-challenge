#ifndef TUPLES_H
#define TUPLES_H
#define TUPLE_LEN 4

typedef double Tuple[TUPLE_LEN];

double tuple_x(Tuple t);
double tuple_y(Tuple t);
double tuple_z(Tuple t);
double tuple_w(Tuple t);
void   tuple_point(Tuple t);
void   tuple_vector(Tuple t);
int    tuple_is_point(Tuple t);
int    tuple_is_vector(Tuple t);
int    tuple_compare(Tuple t1, Tuple t2);
void   tuple_add(Tuple t1, Tuple t2, Tuple res);
void   tuple_subtract(Tuple t1, Tuple t2, Tuple res);
void   tuple_negate(Tuple t, Tuple res);
void   tuple_scale(Tuple t, Tuple res, double scalar);
void   tuple_dscale(Tuple t, Tuple res, double scalar);
void   tuple_normalize(Tuple t, Tuple res);
double tuple_magnitude(Tuple t);
double tuple_dot(Tuple v1, Tuple v2);
void   tuple_cross(Tuple v1, Tuple v2, Tuple res);

#endif
