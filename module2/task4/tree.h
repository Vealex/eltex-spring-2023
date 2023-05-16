#ifndef TREE_H

#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode {
	int bal;
	int key;
	char *data;
	struct TNode *l;
	struct TNode *r;
} TNode;

void add(TNode **tree, int key, char *data);
void printNode(TNode *node, int depth);
void printTree(TNode **tree);
TNode *addBalanceNode(TNode *node, int key, char *data, int *h, int *ins);
int getDepth(TNode *node, int depth);
TNode *R(TNode *node);
TNode *LR(TNode *node);
TNode *L(TNode *node);
TNode *RL(TNode *node);
void resetBalance(TNode *node);
//TNode * balanceNode(TNode *root, TNode *node);
//void balanceTree(TNode **tree);
void addBalance(TNode **tree, int key, char *data);

#endif  // TREE_H

