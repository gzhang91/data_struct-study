#include <stdio.h>
#include <string.h>
#include "stack.h"

typedef struct Data {
	int idx;
	char data[32];
} Data;

int main() {
	Stack *stack = StackCreate(sizeof(Data), 5);
	Data d1;
	
	printf("入栈开始: \n");
	d1.idx = 1;
	memcpy(d1.data, "C++", sizeof(d1.data));
	StackPush(stack, &d1);

	d1.idx = 2;
	memset(d1.data, 0x0, sizeof(d1.data));
	memcpy(d1.data, "C", sizeof(d1.data));
	StackPush(stack, &d1);

	d1.idx = 3;
	memset(d1.data, 0x0, sizeof(d1.data));
	memcpy(d1.data, "Java", sizeof(d1.data));
	StackPush(stack, &d1);

	d1.idx = 4;
	memset(d1.data, 0x0, sizeof(d1.data));
	memcpy(d1.data, "C#", sizeof(d1.data));
	StackPush(stack, &d1);

	d1.idx = 5;
	memset(d1.data, 0x0, sizeof(d1.data));
	memcpy(d1.data, "Python", sizeof(d1.data));
	StackPush(stack, &d1);

	d1.idx = 6;
	memset(d1.data, 0x0, sizeof(d1.data));
	memcpy(d1.data, "delphi", sizeof(d1.data));
	StackPush(stack, &d1);

	printf("出栈开始: \n");
	memset(d1.data, 0x0, sizeof(d1.data));
	if (StackPop(stack, &d1)) {
		printf("Node: idx(%d), data(%s)\n", d1.idx, d1.data);
	}

	memset(d1.data, 0x0, sizeof(d1.data));
	if (StackPop(stack, &d1)) {
		printf("Node: idx(%d), data(%s)\n", d1.idx, d1.data);
	}

	memset(d1.data, 0x0, sizeof(d1.data));
	if (StackPop(stack, &d1)) {
		printf("Node: idx(%d), data(%s)\n", d1.idx, d1.data);
	}

	memset(d1.data, 0x0, sizeof(d1.data));
	if (StackPop(stack, &d1)) {
		printf("Node: idx(%d), data(%s)\n", d1.idx, d1.data);
	}

	memset(d1.data, 0x0, sizeof(d1.data));
	if (StackPop(stack, &d1)) {
		printf("Node: idx(%d), data(%s)\n", d1.idx, d1.data);
	}

	memset(d1.data, 0x0, sizeof(d1.data));
	if (StackPop(stack, &d1)) {
		printf("Node: idx(%d), data(%s)\n", d1.idx, d1.data);
	}

	StackRelease(stack);

	return 0;
}