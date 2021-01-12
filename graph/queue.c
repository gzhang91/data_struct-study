#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Queue *QueueCreate(int size, int n) {
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	if (!queue) {
		printf("malloc failed!\n");
		exit(-1);
	}

	queue->data = (char *)malloc(size * n);
	if (!queue->data) {
		printf("malloc failed!\n");
		exit(-1);
	}

	queue->size = size;
	queue->n = n;
	queue->header = 0;
	queue->tailer = 0;
}

void QueueRelease(Queue *queue) {
	if (!queue) {
		return;
	}

	if (queue->header == queue->tailer) {
		return;
	}

	free(queue->data);
	free(queue);
}

int QueueEn(Queue *queue, void *data) {
	if (!queue) {
		return 0;
	}

	if (QueueFull(queue)) {
		printf("队列已满\n");
		return 0;
	}

	memcpy(queue->data + queue->tailer * queue->size, (char *)data, queue->size);
	queue->tailer ++;
	queue->tailer = (queue->tailer) % queue->n;
	return 1;
}

int QueueDe(Queue *queue, void *data) {
	if (!queue) {
		return 0;
	}

	if (QueueEmpty(queue)) {
		printf("队列已空\n");
		return 0;
	}

	char *target = (char *)data;
	memcpy(target, queue->data + queue->header * queue->size, queue->size);
	queue->header ++;
	queue->header = (queue->header) % queue->n;
	return 1;
}

int QueueEmpty(Queue *queue) {
	return queue->header == queue->tailer;
}

int QueueFull(Queue *queue) {
	return (queue->tailer + 1) % queue->n == queue->header;
}
