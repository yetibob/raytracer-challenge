typedef struct Matrix {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix *matrix(int row, int col);
int mcompare(const Matrix *m1, const Matrix *m2);
