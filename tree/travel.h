#ifndef _TRAVEL_H_
#define _TRAVEL_H_

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

#endif // _TRAVEL_H_