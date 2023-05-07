#include <stdio.h>
#include "list.h"

int main() {
	char str1[] = "string1";
	char str2[] = "string2";
	char str3[] = "string3";
	Node *list = NULL;
	
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
	
	return 0;
}
