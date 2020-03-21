#ifndef TUPLES_H
#define TUPLES_H

typedef double* Tuple;

Tuple ztuple();
double x(Tuple t);
double y(Tuple t);
double z(Tuple t);
double w(Tuple t);
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);
int is_point(Tuple t);
int is_vector(Tuple t);
int tcompare(Tuple t1, Tuple t2);
Tuple add(Tuple t1, Tuple t2);
Tuple subtract(Tuple t1, Tuple t2);
Tuple negate(Tuple t);
Tuple mscale(Tuple t, double scalar);
Tuple dscale(Tuple t, double scalar);
Tuple normalize(Tuple t);
double magnitude(Tuple t);
double dot(Tuple v1, Tuple v2);
Tuple cross(Tuple v1, Tuple v2);

#endif
