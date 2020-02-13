/*
A tuple is an array of doubles of length 4. it is represented
it is being represented as a double * to allow returning tuples
from functions
*/
typedef double* Tuple;

Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);
int is_point(double *t);
int is_vector(double *t);
