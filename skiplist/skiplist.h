#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <stdio.h>

typedef struct Node {
	int key;
	struct Node **forward;
} Node;

typedef struct SkipList {
	int max_level;
	float p;
	int level;
	Node *header;
} SkipList;

SkipList* CreatList(int max_level, float p);
void ReleaseNode(Node *);
void ReleaseList(SkipList *lst);

int RandomLevel(SkipList* lst);
void InsertElem(SkipList* lst, int key);
void DeleteElem(SkipList* lst, int key);
void SearchElem(SkipList *lst, int key);
void DisplayList(SkipList *lst);

#endif //SKIP_LIST_H_
