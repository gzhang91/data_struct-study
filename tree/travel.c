#include "travel.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

void Visit(TNode *node) {
	printf("%d ", *(node->data));
}

void InsertNode(BTree *root, int data) {
	if (!root) {
		*root = (TNode *)malloc(sizeof(TNode));
		memset(*root, 0x0, sizeof(TNode));
		(*root)->data = (int *)malloc(sizeof(int));
		(*root)->visited = (int *)malloc(sizeof(int));
		*(*root)->visited = 0;
		*((*root)->data) = data;
		(*root)->left = (*root)->right = NULL;
		return;
	}

	TNode **curr = root;
	while (*curr) {
		if (*((*curr)->data) > data) {
			curr = &((*curr)->left);
		} else {
			curr = &((*curr)->right);
		}
	}

	TNode *node = (TNode *)malloc(sizeof(TNode));
	memset(node, 0x0, sizeof(TNode));
	node->data = (int *)malloc(sizeof(int));
	node->visited = (int *)malloc(sizeof(int));
	*node->visited = 0;
	*node->data = data;
	node->left = node->right = NULL;
	*curr = node;
}

BTree CreatTree(int *src, int size) {
	BTree root = NULL;

	for (int i = 0; i < size; i++) {
		InsertNode(&root, src[i]);
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

	InOrderRecurse(root->left);
	Visit(root);
	InOrderRecurse(root->right);
}

void PostOrderRecurse(BTree root) {
	if (!root) {
		return;
	}

	PostOrderRecurse(root->left);
	PostOrderRecurse(root->right);
	Visit(root);
}

/*
说明：
创建一个栈，使用sizeof(TNode)和使用sizeof(TNode*)的区别
1. 如果使用TNode*，存入的是一个地址，在下面TNode *node = root中可以看到，将会使用StackPush(stack, node)存入栈中，
实现中拷贝的是节点的地址，需要使用二级指针来保存
2. 如果使用的是TNode，存入的是该节点的数据，StackPop获取时候需要用TNode，而不能用TNode*
*/

/*
	1. 遇到一个元素，入栈，并访问
	2. 如果遇到空节点，取出栈中的元素，往右边执行
	3. 重复上面两个步骤
*/
void PreOrderNoRecurse(BTree root) {
	if (!root) {
		return;
	}

	
	Stack *stack = StackCreate(sizeof(TNode *), 1024);
	assert(stack);

	TNode **node = &root;

	while (*node || !StackEmpty(stack)) {

		// 1. 一直往左，遇到一个节点访问一个节点
		while (*node) {
			Visit(*node);
			StackPush(stack, node);
			*node = (*node)->left;
		}

		// 2. 到达左边最小节点，如果右节点存在，偏向右边，继续循环第1步骤
		if (!StackEmpty(stack)) {
			//TNode node_tmp;
			//StackPop(stack, &node_tmp);
			//node = node_tmp.right;
			StackPop(stack, node);
			*node = (*node)->right;
		}
	}
}

/*
	1. 一直向左偏移，并将节点push到栈中
	2. 直到不能向左了，取出栈节点，访问
	3. 判断右节点是否存在，若存在，执行1,2,3操作；若不存在，从栈中弹出节点，执行2,3操作
*/
void InorderNoRecurse(BTree root) {
	if (!root) {
		return;
	}

	// 创建一个栈，使用sizeof(TNode)而不是sizeof(TNode*)
	// 在下面TNode *node = root中可以看到，
	// 将会使用StackPush(stack, node)存入栈中，实现中拷贝的是node指向的对象的数据
	Stack *stack = StackCreate(sizeof(TNode), 1024);
	assert(stack);

	TNode *node = root;

	while (1) {
		// 1. 全力向左，直到达到最小节点
		while (node) {
			StackPush(stack, node);
			node = node->left;
		}

		// 2. 从栈中弹出节点，访问，判断如果右子树存在，就往右重复第一个步骤
		if (!StackEmpty(stack)) {
			TNode node_tmp;
			StackPop(stack, &node_tmp);
			Visit(&node_tmp);

			if (node_tmp.right) {
				node = node_tmp.right;
			}
		} else {
			break;
		}
	}
}

/*
	不足之处需要加上一个标志节点，本案例中标志使用的是指针，如果不用指针，
	需要先取出节点，更新值后再放入
*/
void PostOrderNoRecurse(BTree root) {
	if (!root) {
		return;
	}

	Stack *stack = StackCreate(sizeof(TNode), 1024);
	assert(stack);

	TNode *node = root;

	while (1) {
		while (node && !(*node->visited)) {
			StackPush(stack, node);
			node = node->left;
		}

		if (!StackEmpty(stack)) {
			TNode node_tmp;
			StackTop(stack, &node_tmp);
			node = node_tmp.right;

			if (node && !(*node->visited)) {
				StackPush(stack, node);
				node = node->left;
				continue;
			}

			if (!StackEmpty(stack)) {
				StackPop(stack, &node_tmp);
				Visit(&node_tmp);
				node = &node_tmp;
				*node->visited = 1;
			}

		} else {
			break;
		}
	}
}

/*
	不需要标志进行遍历
*/
void PostOrderNoRecurse1(BTree root) {
	if (!root) {
		return;
	}

	Stack *stack = StackCreate(sizeof(TNode), 1024);
	assert(stack);

	int *prev = NULL;
	TNode *node;
	StackPush(stack, root);

	while (!StackEmpty(stack)) {
		TNode tmp_node;
		StackTop(stack, &tmp_node);
		node = &tmp_node;

		// 1. 如果左右孩子为空，或者现在访问的节点是之前已经访问了的，直接访问这个节点
		// 这里直接使用data地址进行比较，而没有用node的地址，是因为个人写的stack保存的是栈里面的数据，而不是地址
		if ((node &&  node->left == NULL && node->right == NULL) ||
			(prev && (node->left && prev == node->left->data || node->right && prev == node->right->data ))) {
			Visit(node);
			prev = node->data;
			StackPop(stack, node);
		} 
		// 2. 否则不满足这两种情况，将左右节点入栈，这里先入右节点
		else {
			if (node->right) {
				StackPush(stack, node->right);
			} 

			if (node->left) {
				StackPush(stack, node->left);
			}
		}
	}
}