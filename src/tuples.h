typedef struct {
    double x;
    double y;
    double z;
    unsigned int w;
} Tuple;

Tuple *point(double x, double y, double z);
Tuple *vector(double x, double y, double z);
