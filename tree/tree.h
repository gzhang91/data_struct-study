#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode {
	int *data;
	int *visited;
	struct TNode *left;
	struct TNode *right;
} TNode;

typedef TNode * BTree;

void Visit(TNode *node);

void InsertNode(BTree *root, int data);
BTree CreatTree(int *src, int size);
void PreOrderRecurse(BTree root);
void InOrderRecurse(BTree root);
void PostOrderRecurse(BTree root);

void PreOrderNoRecurse(BTree root);
void InorderNoRecurse(BTree root);
void PostOrderNoRecurse(BTree root);
void PostOrderNoRecurse1(BTree root);

// copy
void CopyTree(BTree root, BTree *copy);
void CopyNode(TNode *node, TNode **copy_node);
// image
void ImageTree(BTree root, BTree *image);
void ImageNode(TNode *node, TNode **image_node);

#endif // _TREE_H_