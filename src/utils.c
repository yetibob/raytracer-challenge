#include <math.h>
#include "utils.h"

inline int equals(double x, double y) {
    if (fabs(x - y) < EPSILON) {
        return 0;
    }
    return 1;
}
