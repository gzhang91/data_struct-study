#ifndef _LIST_H_
#define _LIST_H_

typedef struct ListNode {

	struct ListNode *prev;
	struct ListNode *next;
	void *data;
} ListNode;

typedef struct List {

	ListNode *header;
	ListNode *tailer;
	int size;

	void *(*Dup)(void *data);
	void *(*Free)(void *data);
	int (*Cmp)(void *data1, void *data2);
	void (*Visit)(void *data);

} List;

// 新建一个带头结点的list
List * ListCreate();

// 释放一个list
void ListRelease(List *lst);

// 头部加入一个节点
void ListPushHeader(List *lst, void *data);

// 尾部加入一个节点
void ListPushTailer(List *lst, void *data);

// 在某处加入一个节点
void ListPushPos(List *lst, ListNode *pos, void *data);

// 删除一个节点
ListNode* ListPop(List *lst);

// 删除某个位置的节点
ListNode* ListPopPos(List *lst, ListNode *pos);

// 翻转列表
void ListReverse(List *lst);

// 遍历列表
void ListRetrive(List *lst);

// 查找中位节点
ListNode *ListMiddleNode(List *lst, int *idx);

// 合并列表
void MergeSortedList(List *lst1, List *lst2);

#endif // !_LIST_H_
