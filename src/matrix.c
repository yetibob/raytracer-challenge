#include <stdlib.h>
#include "matrix.h"
#include "utils.h"

Matrix *matrix(int row, int col) {
    Matrix *m = malloc(sizeof(Matrix));
    m->data = malloc(sizeof(double *) * row);
    for (int i = 0; i < row; i++) {
        m->data[i] = calloc(col, sizeof(double));
    }
    return m;
}

int mcompare(const Matrix *m1, const Matrix *m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        return 1;
    }
    
    for (int i = 0; i < m1->rows; i++) { 
        for (int j = 0; j < m1->cols; i++) {
            if (equals(m1->data[i][j], m2->data[i][j]) == 1) {
                return 1;
            } 
        } 
    }
    return 0;
}
