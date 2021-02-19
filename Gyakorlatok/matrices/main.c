#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];
	float d[3][3];
	float e[3][3];
	
	float m[3][3] = {
        { 1.0f,  0.0f,  0.0f},
        { 0.0f,  1.0f,  0.0f},
        { 0.0f,  0.0f,  1.0f}
    };
	float transf[3][3] = {
        { 1.0f,  0.0f,  3.0f},
        { 0.0f,  1.0f,  0.0f},
        { 0.0f,  0.0f,  0.5f}
    };
	float nottransf[2][2] = {
        { 1.0f,  0.0f},
        { 0.0f,  1.0f}
    };
	float calctransl[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
    print_matrix(b);
    
    add_matrices(a, b, c);

    print_matrix(c);
	
	init_identity_matrix(a);
	printf("Identity matrix:\n");
	print_matrix(a);
	
	multy_by_scalar(d, 10, b);
	printf("Scalar multiplier:\n");
	print_matrix(d);
	
	multy_by_matrix(e, b, c);
	printf("Matrix multiplier:\n");
	print_matrix(e);
	
	calc_translate_matrix(m, 10, 20);
	printf("Matrix translate:\n");
	print_matrix(m);
	
	calc_translate_matrix1(calctransl, transf, 10, 20);
	printf("Transformed matrix translate:\n");
	print_matrix(calctransl);
	
	calc_translate_matrix2(calctransl, nottransf, 10, 20);
	printf("Not transformed matrix translate:\n");
	print_matrix(calctransl);
	
	calc_rotation_matrix(m, 90);
	printf("Matrix rotation:\n");
	print_matrix(m);
	
	calc_scale_matrix(transf, 2, 3);
	printf("Matrix scaling:\n");
	print_matrix(transf);
	
	return 0;
}

