#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h> 

void helloSpeech();
void setOptions(int* options);
int getNumber(int mode);
int runGame(int number, int try_count);
int calcPoints(int win, int mode, int try_count);
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
	int coins = 0;
	int points = 0;
	int options[] = {-1, 0};
	int playing = 2;
	helloSpeech();
	while (playing) {
		if (playing == 2) setOptions(options);
		int number = getNumber(options[0]);
		int win = runGame(number, options[1]);
		points += calcPoints(win, options[0], options[1]);
		playing = continueDialog();
	}
	goodbyeSpeech(coins);
}

void helloSpeech() {
	printf("Привет мир... ой, то есть игрок! Добро пожаловать на абсолютно легальное НЕ казино!\n");
	printf("У нас есть очки (не деньги), ставки и очень простые правила. Начнем же!\n");
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
	printf("%d\n", num);
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
		}
		if (player_num == number) {
			printf("Поздравляем, ты угадал!\n");
			win = 1;
			break;
		}
	}
	if (!win) printf("Ты проиграл. К сожалению, интуиция у тебя не очень развита...\n");
	return win;
}

int calcPoints(int win, int mode, int try_count) {
	int points = 0;
	points = win + mode + try_count;
	return points;
}

int continueDialog() {
	int continueAgree = 0, resetOptions = 0;
	printf("Хочешь сыграть ещё разок? [0 - нет, 1 - да]: ");
	while (!scanf("%d", &continueAgree) || continueAgree < 0 || continueAgree > 1) {
		printf("Хочешь сломать программу? Ну-ну, пробуй дальше.\n");
		printf("Хочешь сыграть ещё разок? [0 - нет, 1 - да]: ");
		clearCharInBuffer();
	}
	if (continueAgree) {
		printf("Хочешь изменить настройки? [0 - нет, 1 - да]");
		while (!scanf("%d", &resetOptions) || resetOptions < 0 || resetOptions > 1) {
			printf("Честно говоря, такая одержимость багами пугает...\n");
			printf("Хочешь изменить настройки? [0 - нет, 1 - да]: ");
			clearCharInBuffer();
		}
	}
	//printf("%d\n", continueAgree + resetOptions);
	return (continueAgree + resetOptions);
}

void goodbyeSpeech(int coins) {
	printf("Ну что же, игра подошла к концу. Ты заработал %d§. Встретимся еще!\n", coins);
}

void clearCharInBuffer() {
	while (getchar() != '\n');
}
