#include "skiplist.h"
#include<stdlib.h>
#include <string.h>

Node* CreateNode(int key, int level) {
	Node *node = NULL;
	node = (Node *)malloc(sizeof(Node));
	if (!node) {
		printf("create node failed!\n");
		return NULL;
	}

	node->key = key;
	node->forward = (Node **)malloc(sizeof(Node *) * (level + 1));
	memset(node->forward, 0x0, sizeof(Node *) * (level + 1));

	return node;
}

SkipList* CreatList(int max_level, float p) {
	SkipList *lst = NULL;
	lst = (SkipList *)malloc(sizeof(SkipList));
	if (!lst) {
		printf("create skiplist failed!\n");
		return NULL;
	}

	lst->header = CreateNode(-1, max_level);
	lst->p = p;
	lst->max_level = max_level;
	lst->level = 0;

	return lst;
}

void ReleaseList(SkipList *lst) {
	Node *current = lst->header->forward[0];

	while (current != NULL) {
		Node *next = current->forward[0];
		free(current);
		current = next;
	}

	free(lst->header);
	free(lst);
}

int RandomLevel(SkipList* lst) {
	float r = (float)rand() / RAND_MAX; // 得到0-1的数
	int level = 1;

	while (r < lst->p && level < lst->max_level) {
		level ++;
		r = (float)rand() / RAND_MAX; 
	}

	return level;
}

void InsertElem(SkipList* lst, int key) {
	Node *current = lst->header;
	Node **update = NULL;
	update = (Node **)malloc(lst->max_level * sizeof(Node *));
	
	if (!update) {
		printf("create update array failed\n");
		return;
	} 

	memset(update, 0x0, sizeof(Node *) * lst->max_level);

	for (int i = lst->level - 1; i >= 0; i--) {
		while (current->forward[i] != NULL &&
			current->forward[i]->key < key) {
			current = current->forward[i];
		}

		update[i] = current;
	}

	current = current->forward[0];
	if (current == NULL ||
		current->key != key) {
		int rlevel = RandomLevel(lst);

		printf("random level: %d\n", rlevel);
		if (rlevel > lst->level) {
			for (int i = lst->level; i < rlevel; ++i) {
				update[i] = lst->header;
			}

			lst->level = rlevel;
		}

		Node *n = CreateNode(key, rlevel);
		for (int i = 0; i < rlevel; i++) {
			n->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = n;
		}

		printf("successfully insert key %d\n", key);
	}
}

void DeleteElem(SkipList* lst, int key) {
	Node *current = lst->header;
	Node **update = NULL;
	update = (Node **)malloc(lst->max_level* sizeof(Node *));
	
	if (!update) {
		printf("create update array failed\n");
		return;
	} 

	memset(update, 0x0, sizeof(Node *) * lst->max_level);

	for (int i = lst->level - 1; i >= 0; i--) {
		while (current->forward[i] != NULL &&
			current->forward[i]->key < key) {
			current = current->forward[i];
		}

		update[i] = current;
	}

	current = current->forward[0];

	if (current != NULL &&
		current->key == key) {
		for (int i = 0; i < lst->level; i++) {
			if (update[i]->forward[i] != current) {
				break;
			}

			update[i]->forward[i] = current->forward[i];
		}
	}

	free(current);

	while (lst->level - 1 > 0 &&
		lst->header->forward[lst->level - 1] == 0) {
		lst->level --;
	}

	printf("successfully delete key: %d\n", key);
}

void SearchElem(SkipList *lst, int key) {
	Node *current = lst->header;
	for (int i = lst->level - 1; i >= 0; i--) {
		while (current->forward[i] != NULL &&
			current->forward[i]->key < key) {
			current = current->forward[i];
		}
	}

	current = current->forward[0];
	if (current && current->key == key) {
		printf("Found key: %d\n", key);
	} else {
		printf("Not found key: %d\n", key);
	}
}

void DisplayList(SkipList *lst) {
	printf("\t skiplist \n");
	for (int i = lst->level - 1; i >= 0; i--) {
		Node *node = lst->header->forward[i];
		printf("level: %d\n", i + 1);

		while (node != NULL) {
			printf("%d ", node->key);
			node = node->forward[i];
		}

		printf("\n");
	}
}
