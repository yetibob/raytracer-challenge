#include <assert.h>
#include "../src/matrix.h"
#include "../src/utils.h"

void test_create_matrix() {
    Matrix *m = matrix(2, 2);
    double **data = m->data;
    assert(equals(0, data[0][0]) == 0);
    assert(equals(0, data[0][1]) == 0);
    assert(equals(0, data[1][0]) == 0);
    assert(equals(0, data[1][1]) == 0);
}

void test_compare_matrices() {
    Matrix *m1 = matrix(4, 4);
    Matrix *m2 = matrix(4, 4);

    int val = 1;
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            m1->data[i][j] = val;
            m2->data[i][j] = val;
        }
    }

    assert(mcompare(m1, m2) == 0);
}

int main() {
    test_create_matrix();
    test_compare_matrices();
}
