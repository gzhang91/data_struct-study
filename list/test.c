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
	List *lst1 = ListCreate();
	lst1->Dup = &DataDup;
	lst1->Free = &DataFree;
	lst1->Cmp = &DataCmp;
	lst1->Visit = &DataVisit;

	Data dt1 = {9};
	ListPushHeader(lst1, &dt1);
	dt1.data = 6;
	ListPushHeader(lst1, &dt1);
	dt1.data = 4;
	ListPushHeader(lst1, &dt1);
	dt1.data = 2;
	ListPushHeader(lst1, &dt1);

	/*ListRetrive(lst1);
	
	// 查找中位节点
	int middle_idx = 0;
	ListNode *pos = ListMiddleNode(lst1, &middle_idx);
	if (pos) {
		printf("list middle point(%d), node(%p)\n", middle_idx, pos);
	}

	// 翻转
	//ListReverse(lst1);
	ListReversePos(lst1, pos);

	printf("reverse: \n");
	ListRetrive(lst1); */

	List *lst2 = ListCreate();
	lst2->Dup = &DataDup;
	lst2->Free = &DataFree;
	lst2->Cmp = &DataCmp;
	lst2->Visit = &DataVisit;

	dt1.data = 10;
	ListPushHeader(lst2, &dt1);
	dt1.data = 8;
	ListPushHeader(lst2, &dt1);
	dt1.data = 5;
	ListPushHeader(lst2, &dt1);
	dt1.data = 3;
	ListPushHeader(lst2, &dt1);

	MergeSortedList(lst1, lst2);

	ListRetrive(lst1);

	ListRelease(lst1);

	return 0;
}