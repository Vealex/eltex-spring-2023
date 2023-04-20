#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uint_ unsigned int

void printJars(uint_ num, uint_ *jarsCaps, uint_ K, char *dst);
int fillJar(uint_ *src, uint_ *dst, uint_ dstCap);
int detectRepeat(char *str1, char *str2);
void findCapacity(uint_ num, uint_ *jarsCaps, uint_ KCap, uint_ R);
void sortJars(uint_ num, uint_ *jars);

int main() {
	uint_ num = 0;
	uint_ *jars;
	uint_ K = 0, R = 0, error = 0;
	if (scanf("%u", &num)) {
		//printf("There is %u jars\n", num);
		jars = (uint_*)malloc(sizeof(uint_) * num);
		for (uint_ i = 0; i < num && !error; i++) {
			//printf("Insert #%u value: ", i);
			if (!scanf("%u", jars + i)) {
				printf("Error #1_%u\n", i);
				error = 1;
			}
	       }
	} else {
		printf("Error #2\n");
		error = 1;
	}
	if (error || !scanf("%u", &K)) {
		printf("Error #3\n");
		error = 1;
	}
	if (error || !scanf("%u", &R)) {
		printf("Error #4\n");
		error = 1;
	}
	if (!error) {
		findCapacity(num, jars, K, R);
	} else {
		printf("Wrong input data\n");
	}
	return error;
}

void printJars(uint_ num, uint_ *jars, uint_ K, char *dst) {	
	int shift = strlen(dst);
	shift += sprintf(dst + shift, "%4u", K);
	for (uint_ i = 0; i < num * 2; i += 2) {
		shift += sprintf(dst + shift, "%4u", jars[i]);
	}
	sprintf(dst + shift, "\n");
}

int fillJar(uint_ *src, uint_ *dst, uint_ dstCap) {
	//printf("Start with %u %u %u\n", *src, *dst, dstCap);
	uint_ i = 0;
	for (; *src != 0 && *dst < dstCap; i++) {
		(*src)--;
		//printf("%u ", *src);
		(*dst)++;
		//printf("%u\n", *dst);
	}
	return i;
}

void sortJars(uint_ num, uint_ *jars) {
	for (uint_ i = 0; i < num * 2; i += 2) {
		for (uint_ j = i + 2; j < num * 2; j += 2) {
			if (jars[i + 1] > jars[j + 1]) {
				uint_ tmp[2] = {jars[i], jars[i + 1]};
				jars[i] = jars[j];
				jars[i + 1] = jars[j + 1];
				jars[j] = tmp[0];
				jars[j + 1] = tmp[1];
			}
		}
	}
}

int detectRepeat(char *str1, char *str2) {
	int repeat = 1, i = 0;
	//printf("Compare string\n%swith\n%s", str1, str2);
	for (; str1[i] != '\0' && str2[i] != '\0'; i++)
		if (str1[i] != str2[i])
			repeat = 0;
	if (repeat && str1[i] != str2[i])
		repeat = 0;
	if (!repeat) {
		for (i = 0; str2[i] != '\0'; i++)
			str1[i] = str2[i];
		str1[i + 1] = '\0';
	}
	return repeat;
}

void findCapacity(uint_ num, uint_ *jarsCaps, uint_ KCap, uint_ R) {
	uint_ *jars = (uint_*)malloc(sizeof(uint_) * num * 2);
	for (uint_ i = 0; i < num * 2; i += 2) {
		jars[i] = 0;
		jars[i + 1] = jarsCaps[i / 2];
		//printf("%u = %u %u\n", jars[i + 1], jarsCaps[i / 2], i);
	}
	//sortJars(num, jars);
	char str1[200] = "";
	uint_ K = KCap;
	int notFound = 1;
	while (notFound) {
		char str2[200] = "";	
		fillJar(&K, jars + (num * 2 - 2), jars[num * 2 - 1]);
		printJars(num, jars, K, str2);
		if (K == R)
			break;
		uint_ i = num * 2 - 2;
		for (; i > 0; i -= 2) {
			fillJar(jars + i, jars + i - 2, jars[i - 1]);
			printJars(num, jars, K, str2);
			if (jars[i] == R) {
				notFound = 0;
				break;
			}
			//getchar();
		}
		int shifted = 0;
		while (notFound && !shifted) {	
			if (jars[0] == jars[1]) {
				fillJar(jars, &K, KCap);
				printJars(num, jars, K, str2);
				if (K == R)
					notFound = 0;
			}
			fillJar(jars + i + 2, jars + i, jars[i + 1]);
			printJars(num, jars, K, str2);
			//printf("Current i is %u\n", i);
			if (i + 2 < num * 2 - 2)	
				i += 2;
			else
				i = 0;
			if (i == 2 && jars[2])
				i = 0;
			shifted = 1;
			for (uint_ j = 2; j < num * 2; j += 2)
				if (jars[j])
					shifted = 0;
				else if (jars[j] == R)
					notFound = 0;	
			//getchar();
		}
		printf("%s", str2);
		if (detectRepeat(str1, str2))
			break;
		getchar();
		//break;
	}
	if (notFound)
		printf("Need to change order of jars capacities or impossible to find R\n");
}
