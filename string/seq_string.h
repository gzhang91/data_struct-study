#ifndef _SEQ_STRING_H_
#define _SEQ_STRING_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	本测试主要是关注于字符串的模式匹配算法，不关心是否动态扩容等问题
*/

struct seq_string_s {
	char *data;
};

typedef struct seq_string_s seq_string_t;

seq_string_t *seq_string_init(int size);
void seq_string_destroy(seq_string_t *src);
int index_simple(const seq_string_t *src, const seq_string_t *pattern, int pos);
int index_kmp(const seq_string_t *src, const seq_string_t *pattern, int pos);

int *get_next(const char *src);
#endif // !_SEQ_STRING_H_
