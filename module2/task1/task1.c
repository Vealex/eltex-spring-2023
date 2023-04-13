#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h> 

void helloSpeech();
int doDonate(int course);
void menu(int* options, int* points, int* playing, int course);
void setOptions(int* options);
int getNumber(int mode);
int runGame(int number, int try_count);
int setDebt(int points);
void printTips(int orig_num, int player_num);
int calcPoints(int try_count, int total_try_count, int mode, int debt);
int continueDialog();
void goodbyeSpeech(int coins);
void clearCharInBuffer();
void play();

int main() {
	setlocale(LC_ALL, "Russian");
	play();
	return 0;
}

void play() {
	int options[] = {-1, 0};
	int playing = 2;
	srand(time(NULL));
	int course = rand() % (100 + 1);
	helloSpeech();
	setOptions(options);
	int points = doDonate(course);
	while (playing) {
		menu(options, &points, &playing, course);
		
	}
	goodbyeSpeech((double)(points) / ((double)(100) / (double)(course)));
}

void helloSpeech() {
	printf("Привет мир... ой, то есть игрок! Добро пожаловать на абсолютно легальное НЕ казино!\n");
	printf("У нас есть очки (не деньги), ставки и очень простые правила. Начнем же!\n");
}

int doDonate(int course) {
	int points = 0;
	printf("Сколько вечно деревянных ты готов задонатить?\nКурс 100 монет = %d очков.\n:", course);
	while (!scanf("%d", &points) || points < 0) {
		printf("Эх, ну что ты будешь делать...\n:");
		clearCharInBuffer();
	}
	points =(double)(points) * ((double)(100) / (double)(course));
	return points;
}

void menu(int* options, int* points, int* playing, int course) {
	printf("Пункты меню:\n1 - Опции\n2 - Задонатить\n3 - Количество очков\n4 - Сыграть\n5 - Выйти\n:");
	int pt = 0;
	while (!scanf("%d", &pt) || pt < 1 || pt > 5) {
		printf("Просто выбери пункт!\n:");
		clearCharInBuffer();
	}
	if (pt == 1) {
		setOptions(options);
	} else if (pt == 2) {
		*points += doDonate(course);
	} else if (pt == 3) {
		printf("У вас %d очков\n", *points);
	} else if (pt == 4) {
		int number = getNumber(options[0]);
		int debt = setDebt(*points);
		int win = runGame(number, options[1]);
		*points += calcPoints(win, options[1], options[0], debt);
		*playing = continueDialog();
	} else if (pt == 5) {
		*playing = 0;
	}
}


void setOptions(int* options) {
	printf("Зададим параметры нашей игры!\n");
	printf("Выбери сложность, от нее зависит диапазон искомого числа (0 - ЛЕГК, 1 - НРМ, >=2 - УЖС): ");
	while (!scanf("%d", options) || options[0] < 0) { 
		printf("Ты типо тестер, да? Иди потести что-нибудь другое.\n");
		printf("Выбери сложность, от нее зависит диапазон искомого числа (0 - ЛЕГК, 1 - НРМ, >=2 - УЖС): ");
		clearCharInBuffer();
	}
	printf("Тепеь выбери количество попыток на отгадку: ");
	while (!scanf("%d", options + 1) || options[1] < 1) {
		printf("Я же сказал - это игра для крутых. Тестерам сюда нельзя.\n");
		printf("Тепеь выбери количество попыток на отгадку: ");
		clearCharInBuffer();
	}
}

int getNumber(int mode) {
	int max_num = 10;
	if (mode == 1) max_num = 100;
	else if (mode >= 2) for (int i = 0; i < mode; i++, max_num *= 10);
	srand(time(NULL));
	int num = rand() % (max_num + 1);
	//printf("%d\n", num);
	return num;
}

int runGame(int number, int try_count) {
	int win = 0;
	for (int i = 0; i < try_count; i++) {
		printf("Попытка №%d\n", i + 1);
		int player_num = 0;
		printf("Введи своё число: ");
		if (!scanf("%u", &player_num)) {
			printf("Ты опять выходишь на связь, тестер?\n");
			clearCharInBuffer();
			i--;
		} else if (player_num == number) {
			printf("Поздравляем, ты угадал!\n");
			win = i + 1;
			break;
		} else {
			printTips(number, player_num);
		}
	}
	if (!win) printf("Ты проиграл. К сожалению, интуиция у тебя не очень развита...\n");
	return win;
}

int setDebt(int points) {
	int debt = 0;
	printf("У вас имеется %d очков. Желаете ли сделать ставку? [0 - нет, N - ставка]: ", points);
	while (!scanf("%d", &debt) || debt < 0) {
		printf("Да что с тобой не так? Играй уже по правилам!\n");
		clearCharInBuffer();
		printf("У вас имеется %d очков. Желаете ли сделать ставку? [0 - нет, N - ставка]: ", points);

	}
	return debt;
}

void printTips(int orig_num, int player_num) {
	int diff = orig_num - player_num;
	
	if (diff < 0) {
		diff *= -1;
		printf("Загаданное число меньше\n");
	} else {
		printf("Загаданное число больше\n");
	}

	if (diff > 80) {
		printf("Вообще мороз...\n");
	} else if (diff > 30) {
		printf("Холодно\n");
	} else if (diff > 15) {
		printf("Тепло\n");
	} else if (diff > 10) {
		printf("Теплее\n");
	} else if (diff > 5) {
		printf("Вообще жара!\n");
	} else {
		printf("Темпиратура как на солнце\n");
	}
}

int calcPoints(int try_count, int total_try_count, int mode, int debt) {
	int points = 0;
	double try_bonus = 1;
	if (total_try_count <= 3)
		try_bonus = 10;
	else if (total_try_count <= 5)
		try_bonus = 5;
	else if (total_try_count <= 10)
		try_bonus = 2;
	try_bonus *= 1 + (total_try_count - try_count);
	int mode_bonus = 100;
	if (mode == 1)
		mode_bonus = 1000;
	else if (mode > 1)
		mode_bonus = mode * 10000;
	if (try_count == 0) {
		debt *= -2;
		try_bonus = 1;
		mode_bonus = 0;
	} else {
		debt *= 2;
	}
	points = mode_bonus * try_bonus + debt;
	return points;
}

int continueDialog() {
	int continueAgree = 0/*, resetOptions = 0*/;
	printf("Хочешь сыграть ещё разок? [0 - нет, 1 - да]: ");
	while (!scanf("%d", &continueAgree) || continueAgree < 0 || continueAgree > 1) {
		printf("Хочешь сломать программу? Ну-ну, пробуй дальше.\n");
		printf("Хочешь сыграть ещё разок? [0 - нет, 1 - да]: ");
		clearCharInBuffer();
	}
	/*if (continueAgree) {
		printf("Хочешь изменить настройки? [0 - нет, 1 - да]: ");
		while (!scanf("%d", &resetOptions) || resetOptions < 0 || resetOptions > 1) {
			printf("Честно говоря, такая одержимость багами пугает...\n");
			printf("Хочешь изменить настройки? [0 - нет, 1 - да]: ");
			clearCharInBuffer();
		}
	}*/
	//printf("%d\n", continueAgree + resetOptions);
	return (continueAgree);
}

void goodbyeSpeech(int coins) {
	printf("Ну что же, игра подошла к концу. Ты заработал %d§. Встретимся еще!\n", coins);
}

void clearCharInBuffer() {
	while (getchar() != '\n');
}
