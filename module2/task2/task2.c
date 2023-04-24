#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uint_ unsigned int

uint_ RFound(uint_ num, uint_ *jars, uint_ K, uint_ R);
void printJars(uint_ num, uint_ *jars, uint_ K, char *dst);
int fillJar(uint_ *src, uint_ *dst, uint_ dstCap);
void swap(uint_ *jars, int i, int j);
uint_ NextSet(uint_ *jars, uint_ num);
int detectRepeat(char *str1, char *str2);
void findCapacity(uint_ num, uint_ *jarsCaps, uint_ KCap, uint_ R);
void sortJars(uint_ num, uint_ *jars);

int main() {
	uint_ num = 0;
	uint_ *jars;
	uint_ K = 0, R = 0, error = 0;
	if (scanf("%u", &num)) {
		//printf("There is %u jars\n", num);
		jars = (uint_*)malloc(sizeof(uint_) * num * 2);
		for (uint_ i = 0; i < num * 2 && !error; i += 2) {
			//printf("Insert #%u value: ", i);
			if (!scanf("%u", jars + i + 1)) {
				printf("Error #1_%u\n", i);
				error = 1;
			}
			jars[i] = 0;
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

uint_ RFound(uint_ num, uint_ *jars, uint_ K, uint_ R) {  // функция проверки нахождения нужного значения в ёмкостях на текущем шаге
	uint_ found = 0;
	if (K == R)
		found = 1;
	else
		for (uint_ i = 0; i < num * 2 && !found; i += 2)
		       if (jars[i] == R)
			       found = 1;
	return found;
}

void printJars(uint_ num, uint_ *jars, uint_ K, char *dst) {  // функция записи текущего шага в буффер
	int shift = strlen(dst);
	shift += sprintf(dst + shift, "%4u", K);
	for (uint_ i = 0; i < num * 2; i += 2) {
		shift += sprintf(dst + shift, "%4u", jars[i]);
	}
	sprintf(dst + shift, "\n");
}

int fillJar(uint_ *src, uint_ *dst, uint_ dstCap) {  // функция переливания из одной ёмкости в другую до опустошения первой или заполнения первой
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

/*
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
*/

void swap(uint_ *jars, int i, int j) {  // функция обмена местами двух ёмкостей
	uint_ tmp[2] = {jars[i], jars[i + 1]};
	jars[i] = jars[j];
	jars[i + 1] = jars[j + 1];
	jars[j] = tmp[0];
	jars[j + 1] = tmp[1];
}

uint_ NextSet(uint_ *jars, uint_ num) {  // функция размещения емкостей без повторений (меняет местами перебирая все возможные варианты)
	int j;
	do {
		j = (int)(num * 2) - 1;
		//printf("j: %u\n", j);	
		while (j != -1 && jars[j] >= jars[j + 2])
			j -= 2;
		if (j == -1)
			return 0;
		int k = (int)(num * 2) - 1;
		//printf("j: %u\n", j);
		//printf("k: %u\n", k);
		while (jars[j] >= jars[k])
			k -= 2;
		//printf("k: %u\n", k);
		swap(jars, j - 1, k - 1);
		int l = j + 2, r = (int)(num * 2) - 1;
		while (l < r) {
			l += 2;
			r -= 2;
			swap(jars, l - 1, r - 1);
		}
	} while (j > (int)(num * 2) - 1);
	return 1;	
}

int detectRepeat(char *str1, char *str2) {  // функция сравнения записанных в виде строк шагов предыдущей и текущей итерации 
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
		str1[i] = '\0';
	}
	//printf("Repeat: %d\n", repeat);
	return repeat;
}

void findCapacity(uint_ num, uint_ *jars, uint_ KCap, uint_ R) {
	/*
	uint_ *jars = (uint_*)malloc(sizeof(uint_) * num * 2);
	for (uint_ i = 0; i < num * 2; i += 2) {
		jars[i] = 0;
		jars[i + 1] = jarsCaps[i / 2];
		printf("%u = %u %u\n", jars[i + 1], jarsCaps[i / 2], i);
	}
	sortJars(num, jars);
	*/
	char buffer[10000] = "";  // выделяем буффер для хранения пройденных шагов
	while (NextSet(jars, num)) {  // перебираем размещения ёмкостей, подходящие для данного алгоритма
		char str1[2000] = "";  // буффер для предыдущих шагов
		uint_ K = KCap;  // осановная ёмкость
		int notFound = 1;  // флаг ненахождения
		while (notFound) {
			char str2[2000] = "";  // буффер для текущих шагов
			fillJar(&K, jars + (num * 2 - 2), jars[num * 2 - 1]);  // переливаем из основной ёмкости
			printJars(num, jars, K, str2);
			if (RFound(num, jars, K, R)) {
				sprintf(buffer + strlen(buffer), "%s", str2);
				notFound = 0;
				break;
			}
			uint_ i = num * 2 - 2;  // начинаем с последней ёмкости
			for (; i > 0; i -= 2) {  // водопадом переливаем с последней ёмкости до первой
				fillJar(jars + i, jars + i - 2, jars[i - 1]);
				printJars(num, jars, K, str2);
				if (RFound(num, jars, K, R)) {
					sprintf(buffer + strlen(buffer), "%s", str2);
					notFound = 0;
					break;
				}
				//getchar();
			}
			int shifted = 0;
			while (notFound && !shifted) { 	// переливаем из правой в текущую, перемещаясь слева направо, пока в первой не останется значение меньше максимального, а в остальных не останется ничего
				if (jars[0] == jars[1]) {  // как только первая ёмкость наполняется - выливаем из нее в основную
					fillJar(jars, &K, KCap);
					printJars(num, jars, K, str2);
					if (RFound(num, jars, K, R)) {
						notFound = 0;
						break;
					}
				}
				fillJar(jars + i + 2, jars + i, jars[i + 1]);
				printJars(num, jars, K, str2);
				if (RFound(num, jars, K, R)) {
					notFound = 0;
					break;
				}
				//printf("Current i is %u\n", i);
				if (i + 2 < num * 2 - 2)  // смещаемся вправо пока следующая ёмкость не будет последней, иначе - возвращаемся к первой
					i += 2;
				else
					i = 0;
				if (i == 2 && jars[2])  // если текущая ёмкость вторая и если она не пуста - возвращаемся к первой
					i = 0;
				shifted = 1;
				for (uint_ j = 2; j < num * 2; j += 2)  // проверяем на пустоту остальные ёемкости кроме первой
					if (jars[j])
						shifted = 0;	
				//getchar();
			}
			sprintf(buffer + strlen(buffer), "%s", str2);
			if (detectRepeat(str1, str2))  // как только замечаем что предыдущие шаги повторяют текущие - выходим из цикла без подтвержения нахождения
				break;
			//getchar();
			//break;
		}
		for (uint_ i = 0; i < num * 2; i += 2)  // обнуляем ёмкости для работы алгоритма на следующем варианте размещения
			jars[i] = 0;
		if (notFound) {  // если не нашли нужное значение очищаем буффер и переходим к следующему варианту размещения
			//printf("Need to change order of jars capacities or impossible to find R\n");
			for (int i = 0; buffer[i] != '\0'; i++)
				buffer[i] = '\0';
		} else {
			break;
		}
	}
	if (strlen(buffer)) {
		printf("%4u", KCap);
		for (uint_ i = 1; i < num * 2 + 1; i += 2)
			printf("%4u", jars[i]);
		printf("\n");
		for (uint_ i = 0; i < num + 1; i++)
			printf("----");
		printf("\n");
		printf("%s", buffer);
	} else {
		printf("Impossible to find %u with current jars!\n", R);
	}
}
