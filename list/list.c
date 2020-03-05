#include "list.h"
#include <stdio.h>
#include <stdlib.h>

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
	//lst->Free(header->data);
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
		return NULL;
	}

	ListNode *tmp = lst->header->next;
	lst->header->next = tmp->next;
	if (tmp->next) {
		tmp->next->prev = lst->header;
	}
	
	return tmp;
}

ListNode* ListPopPos(List *lst, ListNode *pos) {
	if (!lst) {
		printf("list is empty!\n");
		return NULL;
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

	// 拆掉头结点
	pos->next = NULL;
	lst->tailer = curr;

	while (curr) {
		ListNode *tmp = curr->next;
		curr->next = pos->next;
		curr->prev = pos;
		pos->next = curr;
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

ListNode *ListMiddleNode(List *lst, int *idx) {
	ListNode *fast_ptr = lst->header->next;
	ListNode *slow_ptr = lst->header->next;
	
	while (fast_ptr) {
		(*idx) ++;
		if (fast_ptr->next && fast_ptr->next->next) {
			fast_ptr = fast_ptr->next->next;
		} else {
			break;
		}

		if (slow_ptr->next) {
			slow_ptr = slow_ptr->next;
		} else {
			break;
		}
	}

	return slow_ptr;
}

void MergeSortedList(List *lst1, List *lst2) {
	if (!lst1) {
		printf("list is empty!\n");
		return ;
	}

	if (!lst2) {
		printf("list is empty!\n");
		return ;
	}

	int i = lst1->size, j = lst2->size;
	ListNode *lst1_node = lst1->header->next;
	ListNode *lst2_node = lst2->header->next;
	while (i > 0 && j > 0) {
		if (lst1->Cmp(lst1_node->data, lst2_node->data) == 1) {
			// 将lst2_node解开
			lst2_node->prev->next = lst2_node->next;
			if (lst2_node->next) {
				lst2_node->next->prev = lst2_node->prev;
			}
			lst2->size --;

			// 将lst2_node加在lst1_node上
			ListNode *insert_pos = lst1_node->prev;
			lst2_node->prev = insert_pos;
			lst2_node->next = insert_pos->next;
			insert_pos->next->prev = lst2_node;
			insert_pos->next = lst2_node;

			lst1->size ++;
			j--;

			lst2_node = lst2->header->next;

		} else {
			i--; lst1_node = lst1_node->next;
		}
	}

	if (j > 0) {
		lst1->tailer->next = lst2->header->next;
		lst2->header->next->prev = lst1->tailer;
		lst1->tailer = lst2->tailer;
		lst1->size += j;
	}
}
