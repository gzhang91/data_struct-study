#include "search.h"
#include <stdio.h>

int BinarySearchBase(void *data, int len, void *search_value, int (*comp_func)(void*, void*)) {
	if (!data) {
		return -1;
	}

	int *data_dst = (int *)data;
	int low = 0, high = len - 1;
	int middle = 0;

	while (low <= high) {
		middle = low + (high - low) / 2;
		// printf("low(%d), middle(%d), high(%d)\n", low, middle, high);

		int cmp_value = comp_func((int *)search_value, &data_dst[middle]);
		if (cmp_value > 0) {
			low = middle + 1;
		} else if (cmp_value < 0) {
			high = middle - 1;
		} else {
			return middle;
		}
	}

	return -1;
}

int BinarySearchFirst(void *data, int len, void *search_value, int (*comp_func)(void*, void*)) {
	if (!data) {
		return -1;
	}

	int *data_dst = (int *)data;
	int low = 0, high = len - 1;
	int middle = 0;

	while (low <= high) {
		middle = low + (high - low) / 2;

		int cmp_value = comp_func((int *)search_value, &data_dst[middle]);
		if (cmp_value > 0) {
			low = middle + 1;
		} else if (cmp_value < 0) {
			high = middle - 1;
		} else {
			if (middle == 0 || comp_func((int *)search_value, &data_dst[middle - 1]) > 0) {
				return middle;
			} else {
				high = middle - 1;
			}
		}
	}

	return -1;
}

int BinarySearchLast(void *data, int len, void *search_value, int (*comp_func)(void*, void*)) {
	if (!data) {
		return -1;
	}

	int *data_dst = (int *)data;
	int low = 0, high = len - 1;
	int middle = 0;

	while (low <= high) {
		middle = low + (high - low) / 2;

		int cmp_value = comp_func((int *)search_value, &data_dst[middle]);
		if (cmp_value > 0) {
			low = middle + 1;
		} else if (cmp_value < 0) {
			high = middle - 1;
		} else {
			if (middle == len - 1 || comp_func((int *)search_value, &data_dst[middle + 1]) < 0) {
				return middle;
			} else {
				low = middle + 1;
			}
		}
	}

	return -1;
}

int BinarySearchFirstGreatEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*)) {
	if (!data) {
		return -1;
	}

	int *data_dst = (int *)data;
	int low = 0, high = len - 1;
	int middle = 0;

	while (low <= high) {
		middle = low + (high - low) / 2;

		int cmp_value = comp_func((int *)search_value, &data_dst[middle]);
		if (cmp_value > 0) {
			low = middle + 1;
		} else if (cmp_value < 0) {
			if (middle - 1 >= 0 len - 1 && comp_func((int *)search_value, &data_dst[middle - 1]) >= 0) {
				return middle;
			}

			high = middle - 1;
		} else {
			if (middle == 0 || comp_func((int *)search_value, &data_dst[middle - 1]) > 0) {
				return middle;
			} else {
				high = middle - 1;
			}
		}
	}

	return -1;
}

int BinarySearchLastGreatEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*)) {
	if (!data) {
		return -1;
	}

	int *data_dst = (int *)data;
	// 无意义,比较最后一个就行了
	if (comp_func((int *)search_value, &data_dst[len - 1]) >= 0) {
		return len - 1;
	}

	return -1;
}

int BinarySearchFirstLittleEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*)) {
	if (!data) {
		return -1;
	}

	int *data_dst = (int *)data;
	// 无意义,比较第一个就行了
	if (comp_func((int *)search_value, &data_dst[0]) <= 0) {
		return 0;
	}

	return -1;
}

int BinarySearchLastLittleEq(void *data, int len, void *search_value, int (*comp_func)(void*, void*)) {
	if (!data) {
		return -1;
	}

	int *data_dst = (int *)data;
	int low = 0, high = len - 1;
	int middle = 0;

	while (low <= high) {
		middle = low + (high - low) / 2;

		int cmp_value = comp_func((int *)search_value, &data_dst[middle]);
		if (cmp_value > 0) {
			if (middle + 1 < len && comp_func((int *)search_value, &data_dst[middle + 1]) <= 0) {
				return middle;
			}

			low = middle + 1;
		} else if (cmp_value < 0) {
			high = middle - 1;
		} else {
			if (middle == len - 1 || comp_func((int *)search_value, &data_dst[middle + 1]) < 0) {
				return middle;
			} else {
				low = middle + 1;
			}
		}
	}

	return -1;
}