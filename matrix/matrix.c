#include "matrix.h"

matrix_t *matrix_init(int size) {
    matrix_t *matrix = (matrix_t *)malloc(sizeof(*matrix));
    if (!matrix) {
        printf("matrix malloc failed!\n");
        return NULL;
    }

    matrix->coln = matrix->elmn = matrix->rown = 0;
    matrix->nodes = NULL;

    matrix->nodes = (matrix_node_t *)malloc(size * sizeof(* matrix->nodes));
    if (!matrix->nodes) {
        printf("matrix nodes malloc failed!\n");
        return NULL;
    }

    return matrix;
}

void matrix_release(matrix_t *matrix) {
    if (!matrix && matrix->nodes) {
        return;
    }

    free(matrix->nodes);
    free(matrix);
}

void matrix_show(matrix_t *matrix) {
    printf("row: %d\tcol: %d\n", matrix->rown, matrix->coln);
    printf("num of elems: %d\n", matrix->elmn);

    int i = 0;
    for (; i < matrix->elmn; i++) {
        printf("(%d, %d, %d)", matrix->nodes[i].row, matrix->nodes[i].col, matrix->nodes[i].value);
        if (i != matrix->elmn - 1) {
            printf("-->");
        }
    }
    printf("\n");
}

/*
    返回值：
    0：转置出错
    1：转置正确
*/
int matrix_transpose_simple(const matrix_t *src, matrix_t *dst) {
    if (!src || !dst) {
        return 0;
    }

    if (src->elmn <= 0) {
        return 0;
    }

    dst->coln = src->rown;
    dst->rown = src->coln;
    dst->elmn = src->elmn;

    int elm_i = 0;
    int idx_i = 0;
    int idx_dst_i = 0;

    // 根据列进行遍历，从上到下遍历，而不是从左到右遍历
    for (; idx_i < src->coln; idx_i++) {
        
        for (elm_i = 0; elm_i < src->elmn; elm_i++) {
            if (src->nodes[elm_i].col == idx_i) {
                dst->nodes[idx_dst_i].row = src->nodes[elm_i].col;
                dst->nodes[idx_dst_i].col = src->nodes[elm_i].row;
                dst->nodes[idx_dst_i].value = src->nodes[elm_i].value;
                idx_dst_i ++;
            }
        }
    }

    return 1;
}

/*
    返回值：
    0：转置出错
    1：转置正确
*/
int matrix_transpose_complex(const matrix_t *src, matrix_t *dst) {
    if (!src || !dst) {
        return 0;
    }

    if (src->elmn <= 0) {
        return 0;
    }

    int i = 0;

    dst->coln = src->rown;
    dst->rown = src->coln;
    dst->elmn = src->elmn;

    // 用来存储每一列中元素的个数
    int *num = (int *)malloc(sizeof(int) * src->coln);
    if (!num) {
        printf("num malloc failed!\n");
        return 0;
    }
    memset(num, 0x0, sizeof(int) * src->coln);

    // 计算每一列的开头元素
    for (i = 0; i < src->elmn; ++i) {
        num[src->nodes[i].col] += 1;
    }

    // 计算每个元素的位置
    int *cpot = (int *)malloc(sizeof(int) * src->coln);
    if (!cpot) {
        printf("cpot malloc failed!\n");
        return 0;
    }
    memset(cpot, 0x0, sizeof(int) * src->coln);

    // 计算每行开始元素的位置
    cpot[0] = 0;
    for (i = 1; i < src->coln; ++i) {
        cpot[i] = cpot[i - 1] + num[i - 1];
    }

    int j = 0;
    for (i = 0; i < src->elmn; i++) {
        j = cpot[src->nodes[i].col];
        dst->nodes[j].col = src->nodes[i].row;
        dst->nodes[j].row = src->nodes[i].col;
        dst->nodes[j].value = src->nodes[i].value;
        cpot[src->nodes[i].col]++;
    }

    return 1;
}