#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct Data {
	int data;
} Data;

void * DataDup(void *data) {
	Data *dt1 = (Data *)data;
	if (!dt1) {
		printf("transter error!\n");
		exit(-1);
	}

	Data *dt2 = (Data *)malloc(sizeof(Data));
	dt2->data = dt1->data;

	return dt2;
}

void *DataFree(void *data) {
	Data *dt1 = (Data *)data;
	if (!dt1) {
		printf("transter error!\n");
		exit(-1);
	}

	free(dt1);
}

int DataCmp(void *data1, void *data2) {
	Data *dt1 = (Data *)data1;
	Data *dt2 = (Data *)data2;

	if (!dt1 || !dt2) {
		printf("transter error!\n");
		exit(-1);
	}

	return dt1->data > dt2->data;
}

void DataVisit(void *data) {
	Data *dt1 = (Data *)data;
	if (!dt1) {
		printf("transter error!\n");
		exit(-1);
	}

	printf("%04d ", dt1->data);
}



int main() {
	List *lst = ListCreate();
	lst->Dup = &DataDup;
	lst->Free = &DataFree;
	lst->Cmp = &DataCmp;
	lst->Visit = &DataVisit;

	Data dt1 = {1};
	ListPushHeader(lst, &dt1);

	dt1.data = 2;
	ListPushHeader(lst, &dt1);

	dt1.data = 3;
	ListPushHeader(lst, &dt1);

	dt1.data = 4;
	ListPushHeader(lst, &dt1);

	ListRetrive(lst);

	// 翻转
	//ListReverse(lst);
	ListReversePos(lst, lst->header->next->next);

	printf("reverse: \n");
	ListRetrive(lst);

	ListRelease(lst);

	return 0;
}