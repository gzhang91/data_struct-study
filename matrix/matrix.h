#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;

struct matrix_node_s {
    int row;   // 行 
    int col;   // 列
    ElemType value;
};

typedef struct matrix_node_s matrix_node_t;

struct matrix_s {
    int rown;  // 行数
    int coln;  // 列数
    int elmn;  // 有效元素个数
    matrix_node_t *nodes;
};

typedef struct matrix_s matrix_t; 

// 初始化
matrix_t *matrix_init(int size);

// 释放
void matrix_release(matrix_t *matrix);

// 显示
void matrix_show(matrix_t *matrix);

// 简单转置函数
int matrix_transpose_simple(const matrix_t *src, matrix_t *dst);

// 高效率转置函数
int matrix_transpose_complex(const matrix_t *src, matrix_t *dst);

#endif // !_MATRIX_H_
