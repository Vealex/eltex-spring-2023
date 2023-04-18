#include <stdio.h>

void printJarCapacities(unsigned int a, unsigned int b, unsigned int c);

int main() {
	unsigned int a = 0, b = 0, c = 0, K = 0, R = 0, error = 0;
	if (!scanf("%u%u", &a) && !scanf("%u", &b) && !scanf("%u", &c)) {
		error = 1;
	}
	if (!error && !scanf("%u", &K) && !scanf("%u", &R)) {
		error = 1;
	}
	if (!error) {
		
	} else {
		printf("Wrong input data\n");
	}
	return error;
}
