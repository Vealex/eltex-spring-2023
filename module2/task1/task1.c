#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define uint_ unsigned int 

int init();
void play(uint_ mode);
void mainLoop(uint_ number);

int main() {
	int mode = init();
	if (mode > -1) {
		play((uint_)mode);
	}
	return 0;
}

int init() {
	int mode = -1;
	printf("Welcome player! It's absolute legal ELTEX casino.\n");
	printf("First type game mode (0 - EASY, 1 - NORMAL, >=2 - HARD): ");
	if (!scanf("%d", &mode)) printf("You're idiot, it is not a number!\n");
	return mode;
}

void play(uint_ mode) {
	uint_ max_num = 10;
	if (mode == 1) max_num = 100;
	else if (mode >= 2) for (uint_ i = 0; i < mode; i++, max_num *= 10);
	srand(time(NULL));
	uint_ num = rand() % (max_num + 1);
	//printf("%d\n", num);

	mainLoop(num);
}

void mainLoop(uint_ number) {
	uint_ playing = 1;
	while (playing) {
		for (uint_ i = 0; i < 3; i++) {
			uint_ player_num = 0;
			printf("Type your number: ");
			if (!scanf("%u", &player_num)) {
				printf("You're moran, it is not a number!\n");
				playing = 0;
				break;
			}
			if (player_num == number) {
				printf("You win!\n");
				break;
			}
		}
	}
}
