#include "sort.h"

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