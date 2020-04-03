#ifndef _SEARCH_H_
#define _SEARCH_H_



// 二叉查找
/*
 * 返回值:
 *    -1: 没有找到
 *     其他表示找到的下标
*/
int BinarySearchBase(void *data, int len, void *search_value, int (*comp_func)(void*, void*));

// 上面算法不适合重复的元素, 下面算法1. 查找第一个值等于给定值的元素
int BinarySearchFirst(void *data, int len, void *search_value, int (*comp_func)(void*, void*));

// 2. 查找最后一个值等于给定值的元素
int BinarySearchLast(void *data, int len, void *search_value, int (*comp_func)(void*, void*));

// 3. 查找第一个大于等于给定值的元素
int BinarySearchFirstGreatEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*));

// 4. 查找最后一个大于等于给定值的元素
int BinarySearchLastGreatEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*));

// 5. 查找第一个小于等于给定值的元素
int BinarySearchFirstLittleEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*));

// 6. 查找最后一个小于等于给定值的元素
int BinarySearchLastLittleEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*));

#endif // _SEARCH_H_