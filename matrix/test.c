#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define N_COLS 6
#define N_ROWS 7

int main(void) {

	ElemType matrix_array[N_ROWS][N_COLS] = {
		{0,  12, 9,  0, 0, 0},
		{0,  0,  0,  0, 0, 0},
		{-3, 0,  0,  0, 0, 14},
		{0,  0,  24, 0, 0, 0},
		{0, 18,  0,  0, 0, 0},
		{15, 0,  0, -7, 0, 0},
		{0,  0,  0,  0, 0, 0},
	};

	int size = 0;
	for (int i = 0; i < N_ROWS; i++) {
		for (int j = 0; j < N_COLS; j++) {
			if (matrix_array[i][j] != 0) {
				size ++;
			}
		}
	}

	matrix_t *matrix = matrix_init(size);
	matrix->rown = N_ROWS;
	matrix->coln = N_COLS;
	matrix->elmn = size;

	int idx = 0;
	for (int i = 0; i < N_ROWS; i++) {
		for (int j = 0; j < N_COLS; j++) {
			if (matrix_array[i][j] != 0) {
				matrix->nodes[idx].row = i;
				matrix->nodes[idx].col = j;
				matrix->nodes[idx].value = matrix_array[i][j];
				idx ++;
			}
		}
	}

	printf("============use simple====================\n");
	matrix_t *dst = matrix_init(size);
	int ret = matrix_transpose_simple(matrix, dst);
	if (ret == 0) {
		printf("transe failed!\n");
	} else {
		printf("transe ok!\n");
	}

	matrix_show(matrix);
	matrix_show(dst);
	printf("\n");

	printf("============use complex====================\n");
	matrix_t *dst1 = matrix_init(size);
	ret = matrix_transpose_complex(matrix, dst1);
	if (ret == 0) {
		printf("transe failed!\n");
	} else {
		printf("transe ok!\n");
	}
	matrix_show(matrix);
	matrix_show(dst);

	return 0;
}