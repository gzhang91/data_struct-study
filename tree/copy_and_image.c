#include "tree.h"

// copy
void CopyTree(BTree root, BTree *copy) {
    if (!root) {
        return;
    }

    CopyNode(root, copy);
}

void CopyNode(TNode *node, TNode **copy_node) {
    if (!node) {
        return;
    }

    TNode *tmp = (TNode *)malloc(sizeof(TNode));
    memset(tmp, 0x0, sizeof(TNode));
    tmp->data = (int *)malloc(sizeof(int));
    tmp->visited = (int *)malloc(sizeof(int));
    *(tmp->visited) = 0;
    *(tmp->data) = *(node->data);
    tmp->left = tmp->right = NULL;

    *copy_node = tmp;

    if (node->left) {
        CopyNode(node->left, &(tmp->left));
    }
    
    if (node->right) {
        CopyNode(node->right, &(tmp->right));
    }
}

// image
void ImageTree(BTree root, BTree *image) {
    if (!root) {
        return;
    }

    ImageNode(root, image);
}

void ImageNode(TNode *node, TNode **image_node) {
    if (!node) {
        return;
    }

    TNode *tmp = (TNode *)malloc(sizeof(TNode));
    memset(tmp, 0x0, sizeof(TNode));
    tmp->data = (int *)malloc(sizeof(int));
    tmp->visited = (int *)malloc(sizeof(int));
    *(tmp->visited) = 0;
    *(tmp->data) = *(node->data);
    tmp->left = tmp->right = NULL;

    *image_node = tmp;

    if (node->left) {
        ImageNode(node->left, &(tmp->right));
    }
    
    if (node->right) {
        ImageNode(node->right, &(tmp->left));
    }
}