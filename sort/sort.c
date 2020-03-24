#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

void bubble_sort(Data d[], size_t d_len) {
	for (int i = 0; i < d_len - 1; i++) { // 轮次
		int change = 0; 
		for (int j = 0; j < d_len - i - 1; j++) { // 一次冒泡所做的操作
			if (d[j].hash_key > d[j+1].hash_key) {
				change = 1;
				Swap(&d[j], &d[j+1]);
			}
		}

		// 有序了
		if (change == 0) {
			break;
		}
	}
}

void insert_sort(Data d[], size_t d_len) {
	for (int i = 1; i < d_len; i++) { // 无序的列表元素数
		int j = i - 1;
		Data tmp = { 0, 0 };

		Assign(&d[i], &tmp);
		while (j >= 0 && tmp.hash_key < d[j].hash_key) {
			Assign(&d[j], &d[j+1]);
			j--;
		}

		Assign(&tmp, &d[j+1]);
	}
}

// 不稳定， 5，8，5，2，9 第一个5会和2交换，这样，就和第二个5交换顺序了
void select_sort(Data d[], size_t d_len) {
	for (int i = 1; i < d_len; i++) { // 选择每个元素
		
		// 选择一个交换的节点
		int idx = i - 1;
		for (int j = i; j < d_len; j++) {
			if (d[j].hash_key < d[idx].hash_key) {
				idx = j;
			}
		}
		if (idx != i - 1) {
			Swap(&d[i - 1], &d[idx]);
		}
	}
}

// 合并
void merge(Data d[], int begin, int end) {
	int mid = (end + begin) / 2;

	Data *tmp = (Data *)malloc((end - begin + 1) * sizeof(Data));
	if (!tmp) {
		printf("malloc failed\n");
		abort();
	}
	memset(tmp, 0x0, (end - begin) * sizeof(Data));

	int k = 0;
	int i = begin, j = mid + 1;
	for (; i <= mid && j <= end; ) {
		if (d[i].hash_key < d[j].hash_key) {
			Assign(&d[i], &tmp[k++]);
			i++;
		} else {
			Assign(&d[j], &tmp[k++]);
			j++;
		}
	}

	while (i <= mid) {
		Assign(&d[i++], &tmp[k++]);
	}

	while (j <= end) {
		Assign(&d[j++], &tmp[k++]);
	}

	for (i = begin, j = 0; i <= end; i++, j++) {
		Assign(&tmp[j], &d[i]);
	}

	free(tmp);
	tmp = NULL;
}

// 分
void merge_sort_elem(Data d[], int begin, int end) {
	if (begin >= end) {
		return;
	} 

	int mid = (end + begin) / 2;
	merge_sort_elem(d, begin, mid);
	merge_sort_elem(d, mid + 1, end);
	merge(d, begin, end);
}

/*
算法思想是： 分治
1. 先将元素分成相等的两份，分别排序左右两份
2. 对分成的两份数据合并起来
*/
void merge_sort(Data d[], size_t d_len) {
	merge_sort_elem(d, 0, d_len - 1);
}

void quick_sort_elem(Data d[], int begin, int end) {
	if (begin >= end) {
		return;
	}

	int first = d[begin].hash_key;
	int last = d[end].hash_key;
	int mid = d[(begin + end) / 2].hash_key;
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

	Swap(&d[pivot], &d[end]);

	int i = begin, j = end - 1;
	while (i <= j) {
		
		while (d[i].hash_key < d[end].hash_key) {
			i++;
		}

		while (d[j].hash_key > d[end].hash_key) {
			j--;
		}

		if (i <= j) {
			Swap(&d[i], &d[j]);
			i++;
			j--;
		}
	}

	Swap(&d[i], &d[end]);

	quick_sort_elem(d, begin, i - 1);
	quick_sort_elem(d, i + 1, end);
}

/*
算法思想是： 
1. 选择一个轴点，一轮循环将元素所有元素都排列在轴点左右（大于轴点在右，小于轴点在左）
2. 依次对轴点左右两边的元素进行这种操作，直到只有一个元素位置（左，右）
*/
void quick_sort(Data d[], size_t d_len) {
	quick_sort_elem(d, 0, d_len - 1);
}

void bucket_sort(Data d[], size_t d_len) {

}

void count_sort(Data d[], size_t d_len) {

}

void radix_sort(Data d[], size_t d_len) {

}
