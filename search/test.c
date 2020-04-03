#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "search.h"
#include "sort.h"

#define MIN_TEST_SIZE 10
#define MIN_TEST_SIZE_REAP 6
#define MAX_TEST_SIZE 100000

int* GetSortedRandValue(int size) {
	int *rand_val = (int *)calloc(sizeof(int), size);
	if (!rand_val) {
		abort();
	}

	int rand_select[MIN_TEST_SIZE_REAP / 2] = {0};
	int selected_num = 3;
	int i = 0;
	for (i; i < size - MIN_TEST_SIZE_REAP; i++) {
		rand_val[i] = rand() % MAX_TEST_SIZE;
		if (selected_num > 0) {
			rand_select[i] = rand_val[i];
			selected_num --;
		}
	}

	// 3, 2,1
	rand_val[i] = rand_select[0];
	i++;
	rand_val[i] = rand_select[0];
	i++;
	rand_val[i] = rand_select[0];

	i++;
	rand_val[i] = rand_select[1];
	i++;
	rand_val[i] = rand_select[1];

	i++;
	rand_val[i] = rand_select[2];

	quick_sort(rand_val, size);

	return rand_val;
}

void PrintArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int IntCmpFunc(void *left, void *right) {
	if (*(int *)left > *(int *)right) {
		return 1;
	} else if (*(int *)left < *(int *)right) {
		return -1;
	} else {
		return 0;
	}

	return 0;
}

int main() {
	srand(time(0));
	int *array_min = GetSortedRandValue(MIN_TEST_SIZE + MIN_TEST_SIZE_REAP);
	printf("排序之后的原始字符串: \n");
	PrintArray(array_min, MIN_TEST_SIZE + MIN_TEST_SIZE_REAP);
	//int rand_find_val = rand() % MAX_TEST_SIZE;
	int rand_find_val = 0;
	int res = 0;
	
	/*printf("[1] 输入查找的元素> ");
	scanf("%d", &rand_find_val);
	res = BinarySearchBase(array_min, MIN_TEST_SIZE + MIN_TEST_SIZE_REAP, &rand_find_val, &IntCmpFunc);
	if (res < 0) {
		printf("不能找到该值[%d]\n", rand_find_val);
	} else {
		printf("找到该值的任意位置,在下标为[%d]位置\n", res);
	}

	printf("[2] 输入查找的元素> ");
	scanf("%d", &rand_find_val);
	res = BinarySearchFirst(array_min, MIN_TEST_SIZE + MIN_TEST_SIZE_REAP, &rand_find_val, &IntCmpFunc);
	if (res < 0) {
		printf("不能找到该值[%d]的第一个位置\n", rand_find_val);
	} else {
		printf("找到该值的第一个位置,在下标为[%d]位置\n", res);
	}

	printf("[3] 输入查找的元素> ");
	scanf("%d", &rand_find_val);
	res = BinarySearchLast(array_min, MIN_TEST_SIZE + MIN_TEST_SIZE_REAP, &rand_find_val, &IntCmpFunc);
	if (res < 0) {
		printf("不能找到该值[%d]的最后一个位置\n", rand_find_val);
	} else {
		printf("找到该值的最后一个位置,在下标为[%d]位置\n", res);
	}*/

	printf("[4] 输入查找的元素> ");
	scanf("%d", &rand_find_val);
	res = BinarySearchFirstGreatEq(array_min, MIN_TEST_SIZE + MIN_TEST_SIZE_REAP, &rand_find_val, &IntCmpFunc);
	if (res < 0) {
		printf("不能找到该值[%d]的第一个大于等于位置\n", rand_find_val);
	} else {
		printf("找到该值的第一个大于等于位置,在下标为[%d]位置\n", res);
	}

	printf("[5] 输入查找的元素> ");
	scanf("%d", &rand_find_val);
	res = BinarySearchLastLittleEq(array_min, MIN_TEST_SIZE + MIN_TEST_SIZE_REAP, &rand_find_val, &IntCmpFunc);
	if (res < 0) {
		printf("不能找到该值[%d]的最后一个小于等于位置\n", rand_find_val);
	} else {
		printf("找到该值的最后一个小于等于位置,在下标为[%d]位置\n", res);
	}

	return 0;
}