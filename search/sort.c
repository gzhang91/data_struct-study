#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

void quick_sort_elem(int d[], int begin, int end) {
	if (begin >= end) {
		return;
	}

	int first = d[begin];
	int last = d[end];
	int mid = d[begin + (end - begin) / 2];
	int pivot = begin;

	if (first > last) {
		if (first > mid) {
			pivot = begin;
		} else {
			pivot = (begin + end) / 2; 
		}
	} else {
		if (last > mid) {
			pivot = end;
		} else {
			pivot = (begin + end) / 2;
		}
	}

	int tmp = d[pivot];
	d[pivot] = d[end];
	d[end] = tmp;

	int i = begin, j = end - 1;
	while (i <= j) {
		
		while (d[i] < d[end]) {
			i++;
		}

		while (d[j] > d[end]) {
			j--;
		}

		if (i <= j) {
			tmp = d[i];
			d[i] = d[j];
			d[j] = tmp;
			i++;
			j--;
		}
	}

	tmp = d[i];
	d[i] = d[end];
	d[end] = tmp;

	quick_sort_elem(d, begin, i - 1);
	quick_sort_elem(d, i + 1, end);
}

/*
算法思想是： 
1. 选择一个轴点，一轮循环将元素所有元素都排列在轴点左右（大于轴点在右，小于轴点在左）
2. 依次对轴点左右两边的元素进行这种操作，直到只有一个元素位置（左，右）
*/
void quick_sort(int d[], int d_len) {
	quick_sort_elem(d, 0, d_len - 1);
}
