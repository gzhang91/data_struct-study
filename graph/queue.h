#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue {
	void *data;
	int size;
	int n;
	int header;
	int tailer;
} Queue;

// 初始化队列
Queue *QueueCreate(int size, int n);

// 释放队列
void QueueRelease(Queue *queue);

// 入队
int QueueEn(Queue *queue, void *data);

// 出队
int QueueDe(Queue *queue, void *data);

// 判空
int QueueEmpty(Queue *queue);

// 判满
int QueueFull(Queue *queue);

#endif // !_QUEUE_H_