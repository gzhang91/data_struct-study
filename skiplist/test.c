#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>
#include "skiplist.h"

int main() {
	srand((unsigned)time(0));

	SkipList *lst = CreatList(4, 0.5);
	InsertElem(lst, 3);
	InsertElem(lst, 5);
	InsertElem(lst, 6);
	InsertElem(lst, 8);
	InsertElem(lst, 9);
	InsertElem(lst, 13);
	InsertElem(lst, 15);
	InsertElem(lst, 19);
	InsertElem(lst, 23);
	InsertElem(lst, 33);
	InsertElem(lst, 45);
	InsertElem(lst, 56);
	InsertElem(lst, 58);
	InsertElem(lst, 60);
	DisplayList(lst);

	printf("delete: \n");
	DeleteElem(lst, 3);
	DeleteElem(lst, 60);
	DisplayList(lst);

	SearchElem(lst, 6);
	SearchElem(lst, 21);

	ReleaseList(lst);
	printf("operate ok\n");
	return 0;
}