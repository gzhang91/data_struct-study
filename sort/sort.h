#ifndef _SORT_H_
#define _SORT_H_

#include <string.h>

typedef struct Data {
	int hash_key;
	char data[32];
} Data;

static void Assign(Data *src, Data *dst) {
	dst->hash_key = src->hash_key;
	memcpy(dst->data, src->data, sizeof(src->data) - 1);
}

static void Swap(Data *d1, Data *d2) {
	Data tmp;
	memset(&tmp, 0x0, sizeof(tmp));

	Assign(d1, &tmp);
	Assign(d2, d1);
	Assign(&tmp, d2);
}

void bubble_sort(Data d[], size_t d_len);
void insert_sort(Data d[], size_t d_len);
void select_sort(Data d[], size_t d_len);

#endif // _SORT_H_