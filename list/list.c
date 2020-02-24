#include "list.h"
#include <stdio.h>

List * ListCreate() {
	List *lst = (List *)malloc(sizeof(List));
	if (!lst) {
		printf("malloc list failed\n");
		return NULL;
	}

	ListNode *header = (ListNode *)malloc(sizeof(ListNode));
	if (!header) {
		printf("malloc list node failed\n");
		return NULL;
	}

	header->data = NULL;//lst->Dup((void *)0);
	header->prev = NULL;
	header->next = NULL;

	lst->header = lst->tailer = header;
	lst->size = 0;

	return lst;
}

void ListRelease(List *lst) {
	if (lst->size <= 0) {
		return;
	}

	while (lst->size > 0) {
		ListNode *node = ListPop(lst);
		lst->Free(node->data);
		free(node);
		lst->size --;
	}

	// free header
	ListNode *header = lst->header;
	lst->Free(header->data);
	free(lst);
}

void ListPushHeader(List *lst, void *data) {
	if (!lst) {
		printf("list is empty!\n");
		return ;
	}

	ListNode *header = lst->header;
	ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
	if (!new_node) {
		printf("malloc new node failed!\n");
		return;
	}

	new_node->data = lst->Dup(data);
	new_node->prev = header;
	new_node->next = header->next;
	if (header->next) {
		header->next->prev = new_node;
	}
	header->next = new_node;

	if (lst->size == 0) {
		lst->tailer = new_node;
	}

	lst->size ++;
}

void ListPushTailer(List *lst, void *data) {
	if (!lst) {
		printf("list is empty!\n");
		return ;
	}

	ListNode *tailer = lst->tailer;
	ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
	if (!new_node) {
		printf("malloc new node failed!\n");
		return;
	}

	new_node->data = lst->Dup(data);
	new_node->prev = tailer;
	new_node->next = NULL;
	tailer = new_node;
	lst->size ++;
}

void ListPushPos(List *lst, ListNode *pos, void *data) {
	if (!lst || !pos) {
		printf("list is empty!\n");
		return ;
	}

	ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
	if (!new_node) {
		printf("malloc new node failed!\n");
		return;
	}

	new_node->data = lst->Dup(data);
	new_node->prev = pos;
	new_node->next = pos->next;
	pos->next = new_node;
	lst->size ++;
}

ListNode* ListPop(List *lst) {
	if (!lst || lst->size <= 0) {
		printf("list is empty!\n");
		return ;
	}

	ListNode *tmp = lst->header->next;
	lst->header->next = tmp->next;
	tmp->next->prev = lst->header;

	return tmp;
}

ListNode* ListPopPos(List *lst, ListNode *pos) {
	if (!lst) {
		printf("list is empty!\n");
		return ;
	}

	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;

	return pos;
}

void ListReverse(List *lst) {
	if (!lst) {
		printf("list is empty!\n");
		return ;
	}

	ListNode *curr = lst->header->next;

	// 拆掉头结点
	lst->header->prev = lst->header->next = NULL;
	lst->tailer = curr;
	
	while (curr) {
		ListNode *tmp = curr->next;

		curr->next = lst->header->next;
		curr->prev = lst->header;

		lst->header->next = curr;
		curr = tmp;
	}
}

void ListReversePos(List *lst, ListNode *pos) {
	if (!lst) {
		printf("list is empty!\n");
		return ;
	}

	ListNode *curr = pos->next;
	while (curr) {
		ListNode *tmp = curr->next;
		curr->next = lst->header->next;
		curr->prev = lst->header;
		lst->header->next = curr;
		curr = tmp;
	}
}

void ListRetrive(List *lst) {
	if (!lst) {
		printf("list is empty!\n");
		return ;
	}

	printf("print list: ");
	ListNode *curr = lst->header->next;
	while (curr) {
		lst->Visit(curr->data);
		curr = curr->next;
	}
	printf("\n");
}