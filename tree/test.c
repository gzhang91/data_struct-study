#include <stdio.h>
#include <string.h>
#include "tree.h"

int main() {
	int src[] = { 4, 8, 1, 2, 10, 32, 9, 15 };

	BTree root = CreatTree(src, sizeof(src) / sizeof(src[0]));
	printf("原始字符串: ");
	for (int i = 0; i < sizeof(src) / sizeof(src[0]); ++i) {
		printf("%d ", src[i]);
	}
	printf("\n");

	printf("先根遍历: ");
	PreOrderRecurse(root);
	printf("\n");

	printf("中根遍历: ");
	InOrderRecurse(root);
	printf("\n");

	printf("后根遍历: ");
	PostOrderRecurse(root);
	printf("\n");

	printf("先根遍历(非递归): ");
	PreOrderNoRecurse(root);
	printf("\n");

	printf("中根遍历(非递归): ");
	InorderNoRecurse(root);
	printf("\n");

	printf("后根遍历(非递归): ");
	PostOrderNoRecurse1(root);
	printf("\n");

	printf("========================\n");
	BTree copy = CreatTree(NULL, 0);
	CopyTree(root, &copy);

	printf("拷贝后先根遍历: ");
	PreOrderRecurse(copy);
	printf("\n");

	printf("========================\n");
	BTree image = CreatTree(NULL, 0);
	ImageTree(root, &image);

	printf("镜像后先根遍历: ");
	PreOrderRecurse(image);
	printf("\n");

	return 0;
}