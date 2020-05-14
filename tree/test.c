#include <stdio.h>
#include <string.h>
#include "travel.h"
#include "stack.h"
#include "queue.h"

int main() {
	int src[] = { 4, 8, 1, 2, 10, 32, 9, 10 };

	BTree root = CreatTree(src, sizeof(src) / sizeof(src[0]));
	PreOrderRecurse(root);
	InOrderRecurse(root);
	PostOrderRecurse(root);

	return 0;
}