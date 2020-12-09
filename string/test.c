#include <stdio.h>
#include <stdlib.h>
#include "seq_string.h"

int main(void) {

	seq_string_t *src = seq_string_init(32);
	seq_string_t *pat = seq_string_init(5);
	strncpy(src->data, "ababababbabababaxyzxyadsfasdfasdfxyzabc", strlen("ababababbabababaxyzxyadsfasdfasdfxyzabc"));
	strncpy(pat->data, "xyzxy", strlen("xyzxy"));

	// 简单的模式匹配算法
	int idx = index_simple(src, pat, 0);
	if (idx == -1) {
		printf("cannot find out[%s] in [%s]\n", pat->data, src->data);
	} else {
		printf("find out[%s] in [%s] pos[%d]\n", pat->data, src->data, idx);
	}

	idx = 0;
	// kmp算法
	idx = index_kmp(src, pat, 0);
	if (idx == -1) {
		printf("cannot find out[%s] in [%s]\n", pat->data, src->data);
	} else {
		printf("find out[%s] in [%s] pos[%d]\n", pat->data, src->data, idx);
	}

	return 0;
}