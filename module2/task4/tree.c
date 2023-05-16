#include "tree.h"

void add(TNode **tree, int key, char *data) {
	if (*tree != NULL) {
		int added = 0;
		TNode *iter = *tree;
		while (!added) {
			if (iter->key > key) {
				if (iter->l != NULL) {
					iter = iter->l;
				} else {
					iter->l = (TNode*)malloc(sizeof(TNode));
					iter->l->bal = 0;
					iter->l->key = key;
					iter->l->data = data;
					iter->l->l = NULL;
					iter->l->r = NULL;
					added = 1;
				}
			} else if (iter->key < key) {
				if (iter->r != NULL) {
					iter = iter->r;
				} else {
					iter->r = (TNode*)malloc(sizeof(TNode));
					iter->r->bal = 0;
					iter->r->key = key;
					iter->r->data = data;
					iter->r->l = NULL;
					iter->r->r = NULL;
					added = 1;
				}
			}
		}
	} else {
		*tree = (TNode*)malloc(sizeof(TNode));
		(*tree)->key = key;
		(*tree)->data = data;
		(*tree)->l = NULL;
		(*tree)->r = NULL;
	}
}

void printNode(TNode *node, int depth) {
	if (node != NULL) {
		printNode(node->r, depth + 1);
		for (int i = 0; i < depth; i++)
			printf("          ");
		//if (depth > 0) printf("     +----");
		printf("%d (%d): %s\n", node->key, node->bal, node->data);
		printNode(node->l, depth + 1);
	}
}

void printTree(TNode **tree) {
	printNode(*tree, 0);
}

TNode *addBalanceNode(TNode *node, int key, char *data, int *h, int *ins) {
	if (node == NULL) {
		//printf("New node %d\n", key);
		node = (TNode*)malloc(sizeof(TNode));
		node->bal = 0;
		node->key = key;
		node->data = data;
		node->l = NULL;
		node->r = NULL;
		*h = 1;
		*ins = 1;
		return node;
	}
	*h = 0;
	if (key == node->key) {
		*ins = 0;
		return node;
	}
	int inserted = 0;
	if (key < node->key) {
		int hh = 0;
		//printf("%d [%d]\n", node->key, node->bal);
		node->l = addBalanceNode(node->l, key, data, &hh, &inserted);
		//printf("RETURN %d [%d]\n", node->key, node->bal);
		if (hh) {
			if (node->bal == 1) {
				node->bal = 0;
			} else if (node->bal == 0) {
				node->bal = -1;
				*h = 1;
			} else if (node->l->bal == -1) {
				//printf("R rotate\n");
				node = R(node);
			} else {
				//printf("LR rotate\n");
				node = LR(node);
			}
		}
	} else {
		int hh = 0;
		//printf("%d [%d]\n", node->key, node->bal);
		node->r = addBalanceNode(node->r, key, data, &hh, &inserted);
		//printf("RETURN %d [%d]\n", node->key, node->bal);
		if (hh) {
			if (node->bal == -1) {
				node->bal = 0;
			} else if (node->bal == 0) {
				node->bal = 1;
				*h = 1;
			} else if (node->r->bal == 1) {
				//printf("L rotate\n");
				node = L(node);
			} else {
				//printf("RL rotate\n");
				node = RL(node);
			}
		}
	}
	//printf("%d [%d]\n", node->key, node->bal);
	*ins = inserted;
	return node;
}

int getDepth(TNode *node, int depth) {
	int maxDepth = depth;
	if (node != NULL) {
		int r = getDepth(node->r, depth + 1);
		int l = getDepth(node->l, depth + 1);
		if (r > l)
			maxDepth = r;
		else
			maxDepth = l;
	}
	return maxDepth;
}

TNode *R(TNode *node) {
	//printf("R rotate %d\n", node->key);
	TNode *x = node->l;
	node->l = x->r;
	x->r = node;
	if (x->bal == -1) {
		x->bal = 0;
		node->bal = x->bal;
	} else {
		node->bal = -1;
		x->bal = 1;
	}
	return x;
}

TNode *LR(TNode *node) {
	//printf("LR rotate %d\n", node->key);
	TNode *x = node->l;
	TNode *y = x->r;
	//printf("Inside LR> %p %p\n", x, y);
	x->r = y->l;
	//printf("Inside LR< %p %p\n", x, y);
	y->l = x;
	node->l = y->r;
	y->r = node;
	if (y->bal == -1) {
		node->bal = 1;
		x->bal = 0;
	}
	if (y->bal == 0) {
		x->bal = 0;
		node->bal = x->bal;
	}
	if (y->bal == 1) {
		node->bal = 0;
		x->bal = -1;
	}
	y->bal = 0;
	return y;
}

TNode *L(TNode *node) {
	//printf("L rotate %d\n", node->key);
	TNode *x = node->r;
	node->r = x->l;
	x->l = node;
	if (x->bal == 1) {
		x->bal = 0;
		node->bal = x->bal;
	} else {
		node->bal = 1;
		x->bal = -1;
	}
	return x;
}

TNode *RL(TNode *node) {
	//printf("RL rotate %d\n", node->key);
	TNode *x = node->r;
	TNode *y = x->l;
	//printf("Inside RL> %p %p\n", x, y);
	x->l = y->r;
	//printf("Inside RL< %p %p\n", x, y);
	y->r = x;
	node->r = y->l;
	y->l = node;
	if (y->bal == 1) {
		node->bal = -1;
		x->bal = 0;
	}
	if (y->bal == 0) {
		x->bal = 0;
		node->bal = x->bal;
	}
	if (y->bal == -1) {
		node->bal = 0;
		x->bal = 1;
	}
	y->bal = 0;
	return y;
}

void resetBalance(TNode *node) {
	if (node != NULL) {
		resetBalance(node->r);
		resetBalance(node->l);
		int diff = getDepth(node->r, 1) - getDepth(node->l, 1);
		if (diff < 0)
			node->bal = -1;
		else if (diff > 0)
			node->bal = 1;
		else
			node->bal = 0;
	}
}

void addBalance(TNode **tree, int key, char *data) {
	int hh = 0, ins = 0;
	//printf("start\n");
	//resetBalance(*tree);
	*tree = addBalanceNode(*tree, key, data, &hh, &ins);
	//printTree(tree);
}

/*
TNode *balanceNode(TNode *root, TNode *node) {
	if (node != NULL) {
		printf("%d [%d]\n", node->key, node->bal);
		node->l = balanceNode(root, node->l);
		if (node->l != NULL && node->bal < -1) {
			if (node->l->bal == -1)
				node = R(node);
			else
				node = LR(node);
			resetBalance(root);
		}
		node->r = balanceNode(root, node->r);	
		if (node->r != NULL && node->bal > 1) {
			if (node->r->bal == 1)
				node = L(node);
			else
				node = RL(node);
			resetBalance(root);
		}
	}
	return node;
}


void balanceTree(TNode **tree) {
	resetBalance(*tree);
	*tree = balanceNode(*tree, *tree);
}
*/

