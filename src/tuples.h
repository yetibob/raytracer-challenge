/*
A tuple is an array of doubles of length 4. it is represented
it is being represented as a double * to allow returning tuples
from functions
*/
typedef double* Tuple;

Tuple tuple();
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);
int is_point(Tuple t);
int is_vector(Tuple t);
int is_equal(Tuple t1, Tuple t2);
Tuple add_tuples(Tuple t1, Tuple t2);
Tuple subtract_tuples(Tuple t1, Tuple t2);
