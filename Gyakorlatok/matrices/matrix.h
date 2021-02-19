#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 *Initializes identity matrix
 */
void init_identity_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(float matrix[3][3]);

/**
 *Multiple a matrix by a scalar parameter
 */
void multy_by_scalar(float result[3][3], float scalar, float matrix[3][3]);

/**
 *Multiple matrix1 by matrix2
 */
void multy_by_matrix(float result[3][3], float matrix1[3][3], float matrix2[3][3]);

/**
 *Calculate a matrix translation (basic)
 */
void calc_translate_matrix(float m[3][3], float dx, float dy);

/**
 *Calculate a matrix translation (that already a 3X3 matrix)
 */
void calc_translate_matrix1(float result[3][3], float m[3][3], float dx, float dy);

/**
 *Calculate a matrix translation (a 2X2 matrix)
 */
void calc_translate_matrix2(float result[3][3], float m[2][2], float dx, float dy);

/**
 *Calculate a matrix rotation (basic)
 */
void calc_rotation_matrix(float m[3][3], float alpha);

/**
 *Calculate a matrix scale (basic)
 */
void calc_scale_matrix(float m[3][3], float sx, float sy);

/**
 * Add matrices.
 */
void add_matrices(float a[3][3], float b[3][3], float c[3][3]);

#endif // MATRIX_H

