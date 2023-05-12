#include <stdio.h>
#include "list.h"

int main() {
	char str1[] = "string1";
	char str2[] = "string2";
	char str3[] = "string3";
	Node *list = NULL;
	
	printf("Insertion----------\n");

	pushBack(&list, str1);
	printFront(&list);
	printBack(&list);
	printf("\n");

	pushFront(&list, str2);
	printFront(&list);
	printBack(&list);
	printf("\n");

	push(&list, 1, str3);
	printFront(&list);
	printBack(&list);
	printf("\n");

	printf("Editing------------\n");

	printf("%s\n", editFront(&list, "string22"));
	printFront(&list);
	printBack(&list);
	printf("\n");

	printf("%s\n", editBack(&list, "string11"));
	printFront(&list);
	printBack(&list);
	printf("\n");

	printf("%s\n", edit(&list, 1, "string33"));
	printFront(&list);
	printBack(&list);
	printf("\n");

	printf("Exsertion----------\n");

	char *strtmp = pop(&list, 0);
	printf("%s\n", strtmp);
	printFront(&list);
	printBack(&list);
	printf("\n");

	strtmp = popFront(&list);
	printf("%s\n", strtmp);
	printFront(&list);
	printBack(&list);
	printf("\n");

	strtmp = popBack(&list);
	printf("%s\n", strtmp);
	printFront(&list);
	printBack(&list);
	printf("\n");

	printf("Filling-------------\n");

	randomFill(&list, 5);
	printFront(&list);

	sortUP(&list);
	printFront(&list);
	
	return 0;
}
