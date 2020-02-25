#include <stdio.h>
#include <string.h>
#include "queue.h"

typedef struct Data {
	char data[32];
} Data;

int main() {

	// 初始化一个8 * sizeof(Data)的队列
	Queue *queue = QueueCreate(sizeof(Data), 8);

	printf("入队: \n");
	
	Data d1;
	memcpy(d1.data, "C", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "C++", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Java", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Python", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Perl", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Perl", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Golang", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Erlang", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Unkown", sizeof(Data));
	QueueEn(queue, &d1);

	printf("出队: \n");

	Data des;
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	printf("再次进队: \n");
	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Ruby", sizeof(Data));
	QueueEn(queue, &d1);

	memset(d1.data, 0x0, sizeof(Data));
	memcpy(d1.data, "Flex", sizeof(Data));
	QueueEn(queue, &d1);

	printf("再次出队: \n");
	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	memset(des.data, 0x0, sizeof(des.data));
	if (QueueDe(queue, &des)) {
		printf("data: %s\n", des.data);
	}

	QueueRelease(queue);

	return 0;
}