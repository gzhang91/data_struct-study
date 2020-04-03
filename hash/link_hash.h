#ifndef _LINK_HASH_H_
#define _LINK_HASH_H_

// just test
#define INIT_BUCKET_SIZE 113

typedef struct DNode {
	struct DNode *prev;   // 双链表前节点
	struct DNode *next;   // 双链表后节点
	struct DNode *hnext;  // hash表后节点
	void *data;

	void* (*new_data)(void *data);
	int (*cmp_data)(void *d1, void *d2);
	void (*delete_data)(void *data);
	void (*print_data)(void *data);
} DNode;

typedef struct DLinklist {
	DNode *header;
	DNode *tailer;
} DLinklist;

typedef struct LinkHash {
	DNode *bucket;
	DLinklist *dlist;
	int bucket_size;
	int node_num;

	int (*hash_func)(void *data);
} LinkHash;

LinkHash *LinkHashNew();
int LinkHashRelease(LinkHash *link_hash);
int LinkHashInsert(LinkHash *link_hash, void *data); 
int LinkHashDelete(LinkHash *link_hash, void *data);
int LinkHashUpdate(LinkHash *link_hash, void *data);
int LinkHashLength(LinkHash *link_hash);
void PrintList(LinkHash *link_hash);

#endif // _LINK_HASH_H_