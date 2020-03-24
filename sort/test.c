#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "sort.h"

#define SMALL_SIZE 10
#define HUGE_SIZE 100000

void PrintSort(Data data[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", data[i].hash_key);
	}
	printf("\n");
}

void Generator(Data *d_bubble, Data *d_insert, Data *d_select, Data *d_merge, Data *d_quick, int size) {
	memset(d_bubble, 0x0, sizeof(Data) * SMALL_SIZE);
	memset(d_insert, 0x0, sizeof(Data) * SMALL_SIZE);
	memset(d_select, 0x0, sizeof(Data) * SMALL_SIZE);
	memset(d_merge, 0x0, sizeof(Data) * SMALL_SIZE);
	memset(d_quick, 0x0, sizeof(Data) * SMALL_SIZE);

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

		d_merge[i].hash_key = val;
		memcpy(d_merge[i].data, data, sizeof(data) - 1);
		
		d_quick[i].hash_key = val;
		memcpy(d_quick[i].data, data, sizeof(data) - 1);
	}
}

int main() {
	srand(time(0));

	Data *d_bubble, *d_insert, *d_select, *d_merge, *d_quick;
	d_bubble = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	d_insert = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	d_select = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	d_merge = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	d_quick = (Data *)malloc(sizeof(Data) * SMALL_SIZE);
	Generator(d_bubble, d_insert, d_select, d_merge, d_quick, SMALL_SIZE);

	printf("排序前: \n");
	printf("冒泡排序: ");
	PrintSort(d_bubble, SMALL_SIZE);
	printf("插入排序: ");
	PrintSort(d_insert, SMALL_SIZE);
	printf("选择排序: ");
	PrintSort(d_select, SMALL_SIZE);
	printf("归并排序: ");
	PrintSort(d_merge, SMALL_SIZE);
	printf("快速排序: ");
	PrintSort(d_quick, SMALL_SIZE);

	bubble_sort(d_bubble, SMALL_SIZE);
	insert_sort(d_insert, SMALL_SIZE);
	select_sort(d_select, SMALL_SIZE);
	merge_sort(d_merge, SMALL_SIZE);
	quick_sort(d_quick, SMALL_SIZE);

	printf("排序后: \n");
	printf("冒泡排序: ");
	PrintSort(d_bubble, SMALL_SIZE);
	printf("插入排序: ");
	PrintSort(d_insert, SMALL_SIZE);
	printf("选择排序: ");
	PrintSort(d_select, SMALL_SIZE);
	printf("归并排序: ");
	PrintSort(d_merge, SMALL_SIZE);
	printf("快速排序: ");
	PrintSort(d_quick, SMALL_SIZE);
	free(d_bubble);
	free(d_insert);
	free(d_select); 
	free(d_merge);
	free(d_quick);

	d_bubble = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	d_insert = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	d_select = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	d_merge = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	d_quick = (Data *)malloc(sizeof(Data) * HUGE_SIZE);
	Generator(d_bubble, d_insert, d_select, d_merge, d_quick, HUGE_SIZE);

	struct timeval b_begin_time, b_end_time, i_begin_time, i_end_time, s_begin_time, s_end_time;
	struct timeval m_begin_time, m_end_time, q_begin_time, q_end_time;

	printf("开始压力测试: \n");
	gettimeofday(&b_begin_time, NULL);
	bubble_sort(d_bubble, HUGE_SIZE);
	gettimeofday(&b_end_time, NULL);
	//b_end_time = time(NULL);

	//i_begin_time = time(NULL);
	gettimeofday(&i_begin_time, NULL);
	insert_sort(d_insert, HUGE_SIZE);
	gettimeofday(&i_end_time, NULL);
	//i_end_time = time(NULL);

	//s_begin_time = time(NULL);
	gettimeofday(&s_begin_time, NULL);
	select_sort(d_select, HUGE_SIZE);
	gettimeofday(&s_end_time, NULL);
	//s_end_time = time(NULL);

	//m_begin_time = time(NULL);
	gettimeofday(&m_begin_time, NULL);
	merge_sort(d_merge, HUGE_SIZE);
	gettimeofday(&m_end_time, NULL);
	//m_end_time = time(NULL);

	//q_begin_time = time(NULL);
	gettimeofday(&q_begin_time, NULL);
	quick_sort(d_quick, HUGE_SIZE);
	gettimeofday(&q_end_time, NULL);
	//q_end_time = time(NULL);

	printf("冒泡排序(%ld), 插入排序(%ld), 选择排序(%ld), 归并排序(%ld), 快速排序(%ld)\n", 
		( b_end_time.tv_sec * 1000 + b_end_time.tv_usec) - (b_begin_time.tv_sec * 1000 + b_begin_time.tv_usec),
		(i_end_time.tv_sec * 1000 + i_end_time.tv_usec) - (i_begin_time.tv_sec * 1000 + i_begin_time.tv_usec),
		(s_end_time.tv_sec * 1000 + s_end_time.tv_usec) - (s_begin_time.tv_sec * 1000 + s_begin_time.tv_usec),
		(m_end_time.tv_sec * 1000 + m_end_time.tv_usec) - (m_begin_time.tv_sec * 1000 + m_begin_time.tv_usec),
		(q_end_time.tv_sec * 1000 + q_end_time.tv_usec)  - (q_begin_time.tv_sec * 1000 + q_begin_time.tv_usec));
	free(d_bubble);
	free(d_insert);
	free(d_select);
	free(d_merge);
	free(d_quick);

	return 0;
}