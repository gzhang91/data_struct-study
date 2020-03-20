#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"

#define SMALL_SIZE 10
#define HUGE_SIZE 100000

void PrintSort(Data data[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", data[i].hash_key);
	}
	printf("\n");
}

void Generator(Data *d_bubble, Data *d_insert, Data *d_select, int size) {
	memset(d_bubble, 0x0, sizeof(Data) * SMALL_SIZE);
	memset(d_insert, 0x0, sizeof(Data) * SMALL_SIZE);
	memset(d_select, 0x0, sizeof(Data) * SMALL_SIZE);

	for (int i = 0; i < size; i++) {
		int val = rand() % 100000;
		char data[32] = {0};
		sprintf(data, "%d", val);

		d_bubble[i].hash_key = val;
		memcpy(d_bubble[i].data, data, sizeof(data) - 1);

		d_insert[i].hash_key = val;
		memcpy(d_insert[i].data, data, sizeof(data) - 1);
		
		d_select[i].hash_key = val;
		memcpy(d_select[i].data, data, sizeof(data) - 1);
	}
}

int main() {
	srand(time(0));

	Data *d_bubble, *d_insert, *d_select;
	d_bubble = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	d_insert = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	d_select = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	Generator(d_bubble, d_insert, d_select, SMALL_SIZE);

	printf("排序前: \n");
	printf("冒泡排序: ");
	PrintSort(d_bubble, SMALL_SIZE);
	printf("插入排序: ");
	PrintSort(d_insert, SMALL_SIZE);
	printf("选择排序: ");
	PrintSort(d_select, SMALL_SIZE);

	bubble_sort(d_bubble, SMALL_SIZE);
	insert_sort(d_insert, SMALL_SIZE);
	select_sort(d_select, SMALL_SIZE);

	printf("排序后: \n");
	printf("冒泡排序: ");
	PrintSort(d_bubble, SMALL_SIZE);
	printf("插入排序: ");
	PrintSort(d_insert, SMALL_SIZE);
	printf("选择排序: ");
	PrintSort(d_select, SMALL_SIZE);
	free(d_bubble);
	free(d_insert);
	free(d_select);

	printf("进行性能测试: \n");
	d_bubble = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	d_insert = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	d_select = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	Generator(d_bubble, d_insert, d_select, HUGE_SIZE);

	time_t b_begin_time, b_end_time, i_begin_time, i_end_time, s_begin_time, s_end_time;

	b_begin_time = time(NULL);
	bubble_sort(d_bubble, HUGE_SIZE);
	b_end_time = time(NULL);

	i_begin_time = time(NULL);
	insert_sort(d_insert, HUGE_SIZE);
	i_end_time = time(NULL);

	s_begin_time = time(NULL);
	select_sort(d_select, HUGE_SIZE);
	s_end_time = time(NULL);

	printf("冒泡排序(%ld), 插入排序(%ld), 选择排序(%ld)\n", 
		b_end_time - b_begin_time,
		i_end_time - i_begin_time,
		s_end_time - s_begin_time);
	free(d_bubble);
	free(d_insert);
	free(d_select);

	return 0;
}