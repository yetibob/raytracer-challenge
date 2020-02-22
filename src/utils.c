#include <math.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

inline int equals(double x, double y) {
    if (fabs(x - y) < EPSILON) {
        return 0;
    }
    return 1;
}

void write_to_file(char *file_name, char *str) {
    int len = strlen(str);
    FILE *fp = fopen(file_name, "w");
    fwrite(str, sizeof(char), len, fp);
    fclose(fp);
}
