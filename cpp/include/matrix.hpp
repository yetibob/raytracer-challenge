#ifndef MATRIX_H
#define MATRIX_H

#include "tuples.hpp"

// The matrix is the backbone of our computations
// It consists of a dim where the amount of rows and columns
// are always equal to dim
// Therefore matrix data always looks like Matrix->data[dim][dim]
typedef struct Matrix {
    int dim;
    double **data;
} Matrix;


// Generates a new matrix with `dim` and all values initialized to 0
Matrix *matrix(int dim);
void matrix_destroy(Matrix *m);

void matrix_init(Matrix *m, int dim);
void matrix_free(Matrix *m);

// Creates an returns the Identiy Matrix
Matrix *matrix_IdentityMatrix();

// Generates a matrix of `dim` from array
Matrix *matrix_gen(double *a, int dim);

// Compares two matrices
int matrix_compare(const Matrix *m1, const Matrix *m2);

// Multiplies two matrices
Matrix *matrix_multiply(const Matrix *m1, const Matrix *m2);

// Multiples a matrix with a tuple
void matrix_multiply_tuple(const Matrix *m, const Tuple t, Tuple res);

// Generates a transposed matrix from `m` 
Matrix *matrix_transpose(const Matrix *m);

// Returnes the derminant of a matrix
double matrix_determinant(const Matrix *m);

// Returns a submatrix at row,col
Matrix *matrix_sub(const Matrix *m, int row, int col);

// Returns the minor of a matrix at row,col
double matrix_minor(const Matrix *m, int row, int col);

// Returns the cofactor of a matrix at row,col
double matrix_cofactor(const Matrix *m, int row, int col);

// Generates the inverse of a matrix
Matrix *matrix_inverse(const Matrix *m);

// Generates a translation matrix
Matrix *matrix_translation(double x, double y, double z);

// Generates a scaling matrix
Matrix *matrix_scaling(double x, double y, double z);

// Generates a matrix to rotate around the x axis by `radians`
Matrix *matrix_rotation_x(double radians);

// Generates a matrix to rotate around the y axis by `radians`
Matrix *matrix_rotation_y(double radians);

// Generates a matrix to rotate around the z axis by `radians`
Matrix *matrix_rotation_z(double radians);

// Generates a shearing matrix
Matrix *matrix_shearing(double xy, double xz, double yx, double yz, double zx, double zy);
#endif
