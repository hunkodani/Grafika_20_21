#include "matrix.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
			if (i == j){
				matrix[i][j] = 1.0;
			}
			else{
				matrix[i][j] = 0.0;
			}
        }
    }
}

void print_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
	printf("\n");
}

void multy_by_scalar(float result[3][3], float scalar, float matrix[3][3])
{
	int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

void multy_by_matrix(float result[3][3], float matrix1[3][3], float matrix2[3][3])
{
	int i, j, k;
	for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
			result[i][j] = 0;
			for (k = 0; k < 3; k++){
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
        }
    }
}

void calc_translate_matrix(float m[3][3], float dx, float dy)
{
	m[0][2] = dx;
	m[1][2] = dy;
	if (m[2][2] == 0){			//not needed, if not 0
		m[2][2] = 1;	
	}
}

void calc_translate_matrix1(float result[3][3], float m[3][3], float dx, float dy)
{
	int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = m[i][j];
        }
    }
	result[0][2] += dx;
	result[1][2] += dy;
	if (m[2][2] == 0){			//not needed, if not 0 because it already can be another scale, pl.: 2 or 0.4
		result[2][2] = 1;	
	}
}

void calc_translate_matrix2(float result[3][3], float m[2][2], float dx, float dy)
{
	int i;
    int j;

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            result[i][j] = m[i][j];
        }
    }
	result[0][2] = dx;
	result[1][2] = dy;
	result[2][2] = 1;			//needed, because we created the translation
}

void calc_rotation_matrix(float m[3][3], float alpha)
{
	float val;
	val = PI / 180;
	m[0][0] = cos(alpha * val);
	m[0][1] = -sin(alpha * val);
	m[1][0] = sin(alpha * val);
	m[1][1] = cos(alpha * val);
}

void calc_scale_matrix(float m[3][3], float sx, float sy)
{
	m[0][0] *= sx;
	m[1][1] *= sy;
}

void add_matrices(float a[3][3], float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

