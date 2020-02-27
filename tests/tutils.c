#include "tutils.h"

Matrix *gen_matrix_from_arr(double *a, int dim) {
    Matrix *m = matrix(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            m->data[i][j] = *a++;
        }
    } 
    return m;
}
