#include "list.h"

void pushFront(Node **list, char* buf) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->buf = buf;
	newNode->next = *list;
	*list = newNode;
}

void pushBack(Node **list, char *buf) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->buf = buf;
	newNode->next = NULL;
	if (*list == NULL) {
		*list = newNode;
	} else {
		Node *iter = *list;
		while (iter->next != NULL) iter = iter->next;
		iter->next = newNode;
	}

}

void push(Node **list, size_t pos, char *buf) {
	if (*list != NULL) {
		size_t i = 0;
		Node *iter = *list;
		while (i < pos - 1 && iter->next != NULL) {
			iter = iter->next;
			i++;
		}
		if (i == pos - 1) {
			Node *newNode = (Node*)malloc(sizeof(Node));
			newNode->buf = buf;
			newNode->next = iter->next;
			iter->next = newNode;
		}
	} else {
		if (pos == 0) {
			Node *newNode = (Node*)malloc(sizeof(Node));
			newNode->buf = buf;
			newNode->next = NULL;
			*list = newNode;
		}
	}
}

char *popFront(Node **list) {
	Node *curNode = *list;
	char *value = NULL;
	if (*list != NULL) {
		*list = (*list)->next;
		value = curNode->buf;
		free(curNode);
	}
	return value;
}

char *popBack(Node **list) {
	Node *curNode = NULL;
	char *value = NULL;
	if (*list != NULL) {
		Node *iter = *list;
		Node *prev = *list;
		while (iter->next != NULL) {
			prev = iter;
			iter = iter->next;
		}
		curNode = iter;
		if ((*list)->next == NULL)
			*list = (*list)->next;
		else
			prev->next = iter->next;
		value = curNode->buf;
		free(curNode);
	}
	return value;
}

char *pop(Node **list, size_t pos) {
	Node *curNode = NULL;
	char *value = NULL;
	if (*list != NULL) {
		Node *iter = *list;
		Node *prev = *list;
		size_t i = 0;
		while (iter != NULL && i != pos) {
			i++;
			prev = iter;
			iter = iter->next;
		}
		if (i == pos && iter != NULL) {
			curNode = iter;
			if (pos == 0)
				*list = (*list)->next;
			else
				prev->next = iter->next;
			value = curNode->buf;
			free(curNode);
		}
	}
	return value;
}

char *editFront(Node **list, char *buf) {
	char *prevValue = NULL;
	if (*list != NULL) {
		prevValue = (*list)->buf;
		(*list)->buf = buf;
	}
	return prevValue;
}

char *editBack(Node **list, char *buf) {
	char *prevValue = NULL;
	if (*list != NULL) {
		Node *iter = *list;
		while (iter->next != NULL) iter = iter->next;
		prevValue = iter->buf;
		iter->buf = buf;
	}
	return prevValue;
}

char *edit(Node **list, size_t pos, char *buf) {
	char *prevValue = NULL;
	if (*list != NULL) {
		Node *iter = *list;
		size_t i = 0;
		while (iter != NULL && i != pos) {
			iter = iter->next;
			i++;
		}
		if (i == pos && iter != NULL) {
			prevValue = iter->buf;
			iter->buf = buf;
		}
	}
	return prevValue;
}

void printFront(Node **list) {
	Node *iter = *list;
	while (iter != NULL) {
		printf("%s -> ", iter->buf);
		iter = iter->next;
	}
	printf("NULL\n");
}

void printBack(Node **list) {
	Node *iter = *list;
	Node *last = NULL;
	printf ("NULL");
	while (iter != last) {
		while (iter->next != last) iter = iter->next;
		printf(" <- %s", iter->buf);
		last = iter;
		iter = *list;
	}
	printf("\n");
}

void clear(Node **list) {
	while (*list != NULL) {
		Node *tmp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = tmp;
	}
}

void randomFill(Node **list, size_t N) {
	srand(time(NULL));
	char *text = NULL;
	for (size_t i = 0; i < N; i++) {
		text = (char*)malloc(sizeof(char) * 20);	
		size_t length = rand() % 21;
		for (size_t j = 0; j < 20; j++) {
			if (j < length) {
				text[j] = (char) (rand() % (123 - 65) + 65);
			} else {
				text[j] = '\0';
			}
		}
		pushBack(list, text);
	}
}

void swap(Node **list, size_t a, size_t b) {
	if (*list != NULL) {
		Node *A = *list;
		Node *B = *list;
		size_t i = 0;
		while (i != a && A != NULL) {
			i++;
			A = A->next;
		}
		if (i == a && A != NULL) {
			i = 0;
			while (i != b && B != NULL) {
				i++;
				B = B->next;
			}
			if (i == b && B != NULL) {
				/*Node *A = prevA->next;
				Node *nextA = A->next;
				Node *B = prevB->next;
				Node *nextB = B->next;
				A->next = nextB;
				B->next = nextA;
				prevA->next = B;
				prevB->next = A;*/
				char *tmp = A->buf;
				A->buf = B->buf;
				B->buf = tmp;
			}
		}
	}
}

void sortUP(Node **list) {
	int swapCount = 0;
	if (*list != NULL) {
		do {
			swapCount = 0;
			Node *iter = *list;
			size_t i = 0;
			while (iter->next != NULL) {
				if (strcmp(iter->buf, iter->next->buf) > 0) {
					swap(list, i, i + 1);
					swapCount++;
				}
				//printFront(list);
				iter = iter->next;
				i++;
			}
			//printFront(list);
			//printf("%d\n", swapCount);
		} while (swapCount > 0);
	}
}

void sortDOWN(Node **list) {
	int swapGap = 0;
	Node *iter = *list;
	while (iter != NULL) {
		swapGap++;
		iter = iter->next;
	}
	while (swapGap > 0) {
		swapGap = (int)((double)swapGap / 1.247);
		//printf("%d\n", swapGap);
		iter = *list;
		size_t i = 0;
		while (iter->next != NULL) {
			Node *nextIter = iter;
			size_t j = i;
			while (nextIter->next != NULL && j != i + swapGap - 1) {
				nextIter = nextIter->next;
				j++;
			}
			if (j == i + swapGap - 1)
				if (strcmp(iter->buf, nextIter->buf) < 0)
					swap(list, i, j);
			iter = iter->next;
			i++;
		}
	}
}

