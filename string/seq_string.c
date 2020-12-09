#include "seq_string.h"
#include <stdio.h>
#include <string.h>

seq_string_t *seq_string_init(int size) {
	seq_string_t *seq_string = (seq_string_t *)malloc(sizeof(*seq_string));
	if (!seq_string) {
		printf("string malloc failed\n");
		return NULL;
	}

	seq_string->data = NULL;
	seq_string->data = (char *)malloc(sizeof(char) * size);
	if (!seq_string->data) {
		printf("string data malloc failed\n");
		free(seq_string);
		return NULL;
	}

	return seq_string;
}

void seq_string_destroy(seq_string_t *src) {
	free(src->data);
	free(src);
}

int index_simple(const seq_string_t *src, const seq_string_t *pattern, int pos) {
	// src: ab123abchahadfadsfslf
	// pat: abc

	if (!src|| !pattern) {
		return -1; 
	}

	int src_len = strlen(src->data);
	int pat_len = strlen(pattern->data);

	if (src_len < pat_len) {
		return -1;
	}

	if (pos >= src_len) {
		return -1;
	}

	int i = pos, j = 0;
	for (; i < src_len && j < pat_len; ) {
		if (src->data[i] == pattern->data[j]) {
			i++;
			j++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}

	if (j >= pat_len) {
		return i - j;
	}

	return -1;
}

int index_kmp(const seq_string_t *src, const seq_string_t *pattern, int pos) {

	// src: ab123abchahadfadsfslf
	// pat: abc

	if (!src|| !pattern) {
		return -1; 
	}

	int src_len = strlen(src->data);
	int pat_len = strlen(pattern->data);

	if (pos >= src_len) {
		return -1;
	}

	if (src_len < pat_len) {
		return -1;
	}

	int *next = get_next(pattern->data);

	int i = pos, j = 0;
	for (; i < src_len && j < pat_len; ) {
		if (src->data[i] == pattern->data[j] || j == -1) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}

	free(next);

	if (j >= pat_len) {
		return i - j;
	}
	
	return -1;
}

/*
	获取next数组，相当于匹配字符串自生成
*/
int *get_next(const char *src) {
	if (src == NULL) {
		return NULL;
	}

	int len = strlen(src);
	int *next = (int *)malloc(sizeof(int) * len);
	if (!next) {
		printf("next malloc failed\n");
		return NULL;
	}
	
	if (len <= 2) {
		next[0] = -1;
		next[1] = 0;
		return next;
	}

	next[0] = -1;
	next[1] = 0;

	int i = 2, j = 0;
	for (; i < len; ) {
		if (src[i] == src[j] || j == -1) {
			i++;
			j++;
			next[i] = j;
		} else {
			j = next[j];
		}
	}


	return next;
}