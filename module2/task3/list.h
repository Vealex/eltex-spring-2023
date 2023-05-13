#ifndef LIST_H

#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Node_t {
	char *buf;
	struct Node_t *next;
} Node;

void pushFront(Node **list, char *buf);
void pushBack(Node **list, char *buf);
void push(Node **list, size_t pos, char *buf);

char *popFront(Node **list);
char *popBack(Node **list);
char *pop(Node **list, size_t pos);

char *editFront(Node **list, char *buf);
char *editBack(Node **list, char *buf);
char *edit(Node **list, size_t pos, char *buf);

void clear(Node **list);

void printFront(Node **list);
void printBack(Node **list);

void randomFill(Node **list, size_t N);

void swap(Node **list, size_t a, size_t b);
void sortUP(Node **list);
void sortDOWN(Node **list);

#endif  // LIST_H

