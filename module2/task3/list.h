#ifndef LIST_H

#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
	char *buf;
	struct Node_t *next;
} Node;

void pushFront(Node **list, char *buf);
void pushBack(Node **list, char *buf);
void push(Node **list, size_t pos, char *buf);

Node *popFront(Node **list);
Node *popBack(Node **list);
Node *pop(Node **list, size_t pos);

void editFront(Node **list, char *buf);
void editBack(Node **list, char *buf);
void edit(Node **list, size_t pos, char *buf);

void clear(Node **list);

void printFront(Node **list);
void printBack(Node **list);

void randomFill(Node **list);

#endif  // LIST_H

