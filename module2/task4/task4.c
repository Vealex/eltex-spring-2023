#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

int main() {
	TNode *tree = NULL;

	srand(time(NULL));
	int leafCount = rand() % (21 - 1) + 1;
	int *keys = (int*)malloc(sizeof(int) * leafCount);
	char *strings = (char*)malloc(sizeof(char) * 6 * leafCount);
	for (int i = 0; i < leafCount; i++) {
		int key = rand() % (1001 + 1000) - 1000;
		keys[i] = key;
		for (int j = 0; j < 5; j++) {
			strings[6 * i + j] = (char)(rand() % (123 - 65) + 65);
		}
		strings[6 * i + 6] = '\0';
		add(&tree, key, strings + (6 * i));
	}

	printTree(&tree);
	
	printf("\n\n\n\n");

	TNode *treeBalanced = NULL;
	for (int i = 0; i < leafCount; i++) {
		addBalance(&treeBalanced, keys[i], strings + (6 * i));
	}

	//balanceTree(&tree);
	printTree(&treeBalanced);

	return 0;
}
