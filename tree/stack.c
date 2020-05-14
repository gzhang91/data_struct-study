#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Stack *StackCreate(int size, int n) {
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	if (!stack) {
		printf("malloc failed\n");
		exit(-1);
	}

	stack->data = (void *)malloc(size * n);
	stack->size = size;
	stack->n = n;
	stack->top = -1;
}

void StackRelease(Stack *st) {
	if (st) {
		free(st);
		free(st->data);
	}
}

int StackPush(Stack *st, const void *data) {
	if (st->top == st->n - 1) {
		printf("栈已经满了\n");
		return 0;
	}

	st->top ++;
	memcpy(st->data + st->top * st->size, data, st->size);
	return 1;
}

int StackPop(Stack *st, void *data) {
	if (st->top < 0) {
		printf("栈已经空了\n");
		return 0;
	}

	memcpy(data, st->data + st->top * st->size, st->size);
	st->top --;
	return 1;
}
