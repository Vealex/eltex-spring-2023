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



void printFront(Node **list) {
	Node *iter = *list;
	while (iter != NULL) {
		printf("%s -> ", iter->buf);
		iter = iter->next;
	}
	printf("\n");
}

void printBack(Node **list) {
	Node *iter = *list;
	Node *last = NULL;
	while (iter != last) {
		while (iter->next != last) iter = iter->next;
		printf("%s <- ", iter->buf);
		last = iter;
		iter = *list;
	}
	printf("\n");
}

