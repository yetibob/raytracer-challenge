#include <math.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

int equals(double x, double y) {
    if (fabs(x - y) < EPSILON) {
        return 1;
    }
    return 0;
}

void write_to_file(char *file_name, char *str) {
    int len = strlen(str);
    FILE *fp = fopen(file_name, "w");
    fwrite(str, sizeof(char), len, fp);
    fclose(fp);
}
