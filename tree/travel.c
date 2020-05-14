#include "travel.h"
#include <stdlib.h>
#include <stdio.h>

void Visit(TNode *node) {
	printf("%d ", *(node->data));
}

void InsertNode(BTree *root, int data) {
	if (!(*root)) {
		(*root) = (TNode *)malloc(sizeof(TNode));
		(*root)->data = (int *)malloc(sizeof(int));
		*(*root)->data = data;
		(*root)->left = (*root)->right = NULL;
		return;
	}

	TNode *curr = *root;
	while (curr) {
		if (*(curr->data) > data) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}

	TNode *node = (TNode *)malloc(sizeof(TNode));
	node->data = (int *)malloc(sizeof(int));
	*node->data = data;
	node->left = node->right = NULL;
	curr = node;
}

BTree CreatTree(int *src, int size) {
	BTree root = NULL;

	for (int i = 0; i < size; i++) {
		if (!root) {
			root = (TNode *)malloc(sizeof(TNode));
			root->data = (int *)malloc(sizeof(int));
			*(root->data) = src[i];
			root->left = root->right = NULL;
			continue;
		}

		TNode *curr = root;
		while (curr) {
			if (*(curr->data) > src[i]) {
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}

		TNode *node = (TNode *)malloc(sizeof(TNode));
		node->data = (int *)malloc(sizeof(int));
		*node->data = src[i];
		node->left = node->right = NULL;
		curr = node;
		printf("111\n");
	}

	return root;
}

void PreOrderRecurse(BTree root) {
	if (!root) {
		return;
	}

	Visit(root);
	PreOrderRecurse(root->left);
	PreOrderRecurse(root->right);
}

void InOrderRecurse(BTree root) {
	if (!root) {
		return;
	}

	PreOrderRecurse(root->left);
	Visit(root);
	PreOrderRecurse(root->right);
}

void PostOrderRecurse(BTree root) {
	if (!root) {
		return;
	}

	PreOrderRecurse(root->left);
	PreOrderRecurse(root->right);
	Visit(root);
}

void PreOrderNoRecurse(BTree root) {

}

void InorderNoRecurse(BTree root) {

}

void PostOrderNoRecurse(BTree root) {

}