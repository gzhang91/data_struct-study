#include <stdio.h>
#include <stdlib.h>
#include "link_hash.h"

void* DataNew(void *data) {
	int *data_dst = (int *)data;
	int *data_new = (int *)malloc(sizeof(int));

	// null
	if (!data_dst) {
		*data_new = 0;
	} else {
		*data_new = *data_dst;
	}

	return data_new;
}

int DataCmp(void *d1, void *d2) {
	if (*(int *)d1 == *(int *)d2) {
		return 0;
	} else  {
		return 1;
	}

	return 1;
}

void DataDelete(void *data) {
	free(data);
}

int HashFunc(void *data) {
	return *(int *)data % INIT_BUCKET_SIZE;
}

void PrintData(void *data) {
	int *data_dst = (int *)data;
	printf("%d ", *data_dst);
}

void* (*default_new_data)(void *data) = DataNew;
int (*default_cmp_data)(void *d1, void *d2) = DataCmp;
void (*default_delete_data)(void *data) = DataDelete;
int (*default_hash_func)(void *data) = HashFunc;
void (*default_print_data)(void *data) = PrintData;

int main() {
	LinkHash *link_hash = LinkHashNew();
	int d1 = 123;
	LinkHashInsert(link_hash, &d1);
	d1 = 6;
	LinkHashInsert(link_hash, &d1);
	d1 = 8;
	LinkHashInsert(link_hash, &d1);
	d1 = 90;
	LinkHashInsert(link_hash, &d1);
	d1 = 10;
	LinkHashInsert(link_hash, &d1);
	d1 = 119;
	LinkHashInsert(link_hash, &d1);
	d1 = 121;
	LinkHashInsert(link_hash, &d1);
	d1 = 231;
	LinkHashInsert(link_hash, &d1);

	printf("删除前\n");
	PrintList(link_hash);
	d1 = 119;
	LinkHashDelete(link_hash, &d1);

	printf("删除后\n");
	PrintList(link_hash);

	printf("更新后\n");
	d1 = 8;
	LinkHashUpdate(link_hash, &d1);
	PrintList(link_hash);

	LinkHashRelease(link_hash);

	return 0;
}
