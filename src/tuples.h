typedef struct {
    double x;
    double y;
    double z;
    unsigned int w : 1;
} Tuple;

Tuple *point(double x, double y, double z);
Tuple *vector(double x, double y, double z);
