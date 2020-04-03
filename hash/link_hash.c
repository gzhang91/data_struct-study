#include "link_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void* (*default_new_data)(void *data);
extern int (*default_cmp_data)(void *d1, void *d2);
extern void (*default_delete_data)(void *data);
extern int (*default_hash_func)(void *data);
extern void (*default_print_data)(void *data);

#define LINK_HASH_QUERY(link_hash, data, prev, curr, is_exists) \
	do {\
		int hash_key = link_hash->hash_func(data); \
		curr = &link_hash->bucket[hash_key]; \
		prev = curr; \
		curr = curr->hnext;\
		while (curr && curr->cmp_data(curr->data, data) != 0) { \
			prev = curr; \
			curr = curr->hnext; \
		} \
		if (curr == NULL) { \
			is_exists = 0; \
			break; \
		} \
		is_exists = 1; \
	} while(0)

DNode* NodeNew(void *data) {
	DNode *node = (DNode *)malloc(sizeof(DNode));
	if (!node) {
		abort();
	}

	node->new_data = default_new_data;
	node->cmp_data = default_cmp_data;
	node->delete_data = default_delete_data;
	node->print_data = default_print_data;
	node->data = node->new_data(data);
	node->prev = node->next = node->hnext = NULL;

	return node;
}

LinkHash *LinkHashNew() {
	LinkHash* link_hash = NULL;
	link_hash = (LinkHash *)malloc(sizeof(LinkHash));
	if (!link_hash) {
		abort();
	}
	memset(link_hash, 0x0, sizeof(LinkHash));

	link_hash->bucket = (DNode *)malloc(INIT_BUCKET_SIZE * sizeof(DNode));
	if (!link_hash->bucket) {
		abort();
	}
	memset(link_hash->bucket, 0x0, INIT_BUCKET_SIZE * sizeof(DNode));

	link_hash->dlist = (DLinklist *)malloc(sizeof(DLinklist));
	if (!link_hash->dlist) {
		abort();
	}
	memset(link_hash->dlist, 0x0, sizeof(DLinklist));

	// default func
	link_hash->hash_func = default_hash_func;

	DNode *node = NodeNew(0);
	link_hash->bucket_size = INIT_BUCKET_SIZE;
	link_hash->node_num = 0;
	link_hash->dlist->header = link_hash->dlist->tailer = node;

	return link_hash;
}

void NodeDelete(DNode *node) {
	node->delete_data(node->data);
	free(node);
}

int LinkHashRelease(LinkHash *link_hash) {
	// 释放bucket
	free(link_hash->bucket);
	link_hash->bucket = NULL;

	// 释放双链表
	DNode *header = link_hash->dlist->header;
	DNode *curr = header;
	while (curr->next) {
		DNode *tmp = curr;
		curr = curr->next;
		NodeDelete(tmp);
		tmp = NULL;
	}

	NodeDelete(header);
}

// 只能插入到尾部
int LinkHashInsert(LinkHash *link_hash, void *data) {
	DNode *prev = NULL, *curr = NULL;
	int is_exists = 0;
	LINK_HASH_QUERY(link_hash, data, prev, curr, is_exists);
	if (is_exists) {
		printf("the node is in list\n");
		return 0;
	}

	DNode *node = NodeNew(data);

	// hash拉链, 不存在curr是null
	prev->hnext = node;

	// 双链表
	node->prev = link_hash->dlist->tailer;
	link_hash->dlist->tailer->next = node;
	node->next = NULL;
	link_hash->dlist->tailer = node;

	link_hash->node_num += 1;
}

int LinkHashDelete(LinkHash *link_hash, void *data) {
	DNode *prev = NULL, *curr = NULL;
	int is_exists = 0;
	LINK_HASH_QUERY(link_hash, data, prev, curr, is_exists);
	if (!is_exists) {
		printf("the node is not in list\n");
		return 0;
	}

	// 更改hash拉链的指针
	prev->hnext = curr->hnext;

	// 更改double link的指针
	prev->next = curr->next;
	if (curr == link_hash->dlist->tailer) {
		link_hash->dlist->tailer = prev;
	} else {
		curr->next->prev = prev;
	}
	NodeDelete(curr);

	link_hash->node_num -= 1;
	return 1;
}

int LinkHashUpdate(LinkHash *link_hash, void *data) {
	int ret = 0;
	if (LinkHashDelete(link_hash, data) == 1) {
		ret = LinkHashInsert(link_hash, data);
	}

	return ret;
}

int LinkHashLength(LinkHash *link_hash) {
	return link_hash->node_num;
}

void PrintList(LinkHash *link_hash) {
	if (!link_hash) {
		return;
	}

	printf("打印列表: \n");
	for (int i = 0; i < INIT_BUCKET_SIZE; i++) {
		if (link_hash->bucket[i].hnext) {
			printf("index[%d] ", i);
			DNode *curr = link_hash->bucket[i].hnext;
			while (curr) {
				curr->print_data(curr->data);
				curr = curr->hnext;
			}
			printf("\n");
		}
	}
}