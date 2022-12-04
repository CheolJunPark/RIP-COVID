#include "MyHeader.h"
#include <stdlib.h>

extern humanCurPosX, humanCurPosY;
extern v_num;

//인간 생성
void createHuman() {

	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}
//바이러스 생성
void createVirus() {

	RED
		virus = (Virus*)malloc(100 * sizeof(Virus));

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 5; i++) {
		virus[i].x = rand() % 97 + 1;
		virus[i].y = rand() % 28 + 1;
		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf("*");
	}
	WHITE
}

void createVirusOneby() {

	RED
		srand((unsigned int)time(NULL));

	virusOneby[v_num].x = rand() % 97 + 1;
	virusOneby[v_num].y = rand() % 28 + 1;

	SetCurrentCursorPos(virusOneby[v_num].x, virusOneby[v_num].y);
	printf("*");

	v_num++;
	WHITE
}

void createVirusVertical() {
	RED
		int r[4];
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++)
		r[i] = rand() % 30;

	for (int i = 0; i < GBOARD_HEIGHT - 2; i++) {
		int flag = 0;
		for (int j = 0; j < 4; j++) {
			if (r[j] == i) {
				virusVertical[i].visible = 0;
				virusVertical[i].x = -1;
				virusVertical[i].y = -1;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			continue;

		virusVertical[i].x = 2;
		virusVertical[i].y = 1 + i;

		SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
		printf("*");
		virusVertical[i].visible = 1;
	}
	WHITE
}

void createVirusSquare() {

	int i, k = 0;

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX + i;
		virusSquare[k].y = humanCurPosY - 10;
		k++;

	}

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX - i;
		virusSquare[k].y = humanCurPosY - 10;
		k++;

	}

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX + i;
		virusSquare[k].y = humanCurPosY + 10;
		k++;

	}

	for (i = 0; i < 18; i++) {
		virusSquare[k].x = humanCurPosX - i;
		virusSquare[k].y = humanCurPosY + 10;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX + 18;
		virusSquare[k].y = humanCurPosY + i;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX - 18;
		virusSquare[k].y = humanCurPosY + i;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX + 18;
		virusSquare[k].y = humanCurPosY - i;
		k++;

	}

	for (i = 0; i < 10; i++) {
		virusSquare[k].x = humanCurPosX - 18;
		virusSquare[k].y = humanCurPosY - i;
		k++;

	}

	for (int i = 0; i < 112; i++) {
		SetCurrentCursorPos(virusSquare[i].x, virusSquare[i].y);
		printf("*");
	}
}
