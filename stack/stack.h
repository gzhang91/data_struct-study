#ifndef _STACK_H_
#define _STACK_H_

typedef struct Stack {
	void *data;  // 数据
	int size;    // 每个数据的大小
	int n;       // 数据个数
	int top;     // 栈顶
} Stack;

// 初始化栈
Stack *StackCreate(int size, int n);

// 释放栈
void StackRelease(Stack *st);

// 入栈
int StackPush(Stack *st, const void *data);

// 出栈
int StackPop(Stack *st, void *data);

#endif // !_STACK_H_