#ifndef TUPLES_H
#define TUPLES_H
#define TUPLE_LEN 4

typedef double Tuple[TUPLE_LEN];

double tuple_x(const Tuple t);
double tuple_y(const Tuple t);
double tuple_z(const Tuple t);
double tuple_w(const Tuple t);
void   tuple_point(Tuple t);
void   tuple_vector(Tuple t);
int    tuple_is_point(const Tuple t);
int    tuple_is_vector(const Tuple t);
int    tuple_compare(const Tuple t1, const Tuple t2);
void   tuple_add(const Tuple t1, const Tuple t2, Tuple res);
void   tuple_subtract(const Tuple t1, const Tuple t2, Tuple res);
void   tuple_negate(const Tuple t, Tuple res);
void   tuple_scale(const Tuple t, Tuple res, double scalar);
void   tuple_dscale(const Tuple t, Tuple res, double scalar);
void   tuple_normalize(const Tuple t, Tuple res);
double tuple_magnitude(const Tuple t);
double tuple_dot(const Tuple v1, const Tuple v2);
void   tuple_cross(const Tuple v1, const Tuple v2, Tuple res);

#endif
