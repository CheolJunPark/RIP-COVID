﻿#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "title.h"
#include <math.h>

#define GBOARD_WIDTH 100
#define GBOARD_HEIGHT 30

#define COL				GetStdHandle(STD_OUTPUT_HANDLE)
#define BLACK			SetConsoleTextAttribute(COL, 0x0000);
#define WHITE			SetConsoleTextAttribute(COL, 0x0007);
#define RED				SetConsoleTextAttribute(COL, 0x000c);
#define GREEN			SetConsoleTextAttribute(COL, 0x0002);
#define BLUE_GREEN		SetConsoleTextAttribute(COL, 0x0003);
#define LIGHT_WHITE		SetConsoleTextAttribute(COL, 0x000f);
#define YELLOW			SetConsoleTextAttribute(COL, 0x000e);
#define DARK_YELLOW		SetConsoleTextAttribute(COL, 0x0006);

#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int curPosX, curPosY;
int humanCurPosX = 50, humanCurPosY = 15;
int virusCurPosX, virusCurPosY;
int mode;
int next = 0;
int curTime;

int v_num = 0;
int vertical_num = 0;

typedef struct Virus {
	int x;
	int y;
}Virus;

typedef struct VirusOneby {
	int x;
	int y;
}VirusOneby;

typedef struct VirusVertical {
	int x;
	int y;
}VirusVertical;

typedef struct VirusCircle {
	int x;
	int y;
}VirusCircle;

typedef struct VirusSquare {
	int x;
	int y;
}VirusSquare;

Virus* virus;
VirusOneby virusOneby[100];
VirusVertical virusVertical[GBOARD_HEIGHT];
VirusCircle virusCircle[100];
VirusSquare virusSquare[200];

struct game_util {
	int score;
	int life;
	int* heart;
};

struct game_util game_util;

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//사각형 그리기
void drawRect(int posX, int posY, int width, int height) {

	int x, y;
	for (y = 0; y < height; y++) {
		SetCurrentCursorPos(posX, posY + y);
		if (y == 0)
			printf("┏");
		else if (y == height - 1)
			printf("┗");
		else
			printf("┃");
	}
	for (y = 0; y < height; y++) {
		SetCurrentCursorPos(posX + width - 2, posY + y);
		if (y == 0)
			printf("┓");
		else if (y == height - 1)
			printf("┛");
		else
			printf("┃");
	}
	for (x = 2; x < width - 2; x++) {
		SetCurrentCursorPos(posX + x, posY);
		printf("━");
	}
	for (x = 2; x < width - 2; x++) {
		SetCurrentCursorPos(posX + x, posY + height - 1);
		printf("━");
	}
}
//보드판 내부 지우기
void redrawGameBoard() {
	int x, y;
	for (y = 1; y < GBOARD_HEIGHT - 1; y++) {
		for (x = 2; x < GBOARD_WIDTH - 4; x++) {
			SetCurrentCursorPos(x, y);
			printf("  ");
		}
	}

	curPosX = GBOARD_WIDTH;
	curPosY = 0;
	SetCurrentCursorPos(GBOARD_WIDTH, 0);
}
//모드 선택 입력 받기
void modeKeyInput() {
	int key;
	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case ONE:
				mode = 1;
				redrawGameBoard();
				next = 1;
				break;
			case TWO:
				mode = 2;
				redrawGameBoard();
				next = 1;
				break;
			case THREE:
				mode = 3;
				redrawGameBoard();
				next = 1;
				break;
			case FOUR:
				mode = 4;
				redrawGameBoard();
				next = 1;
				break;
			case FIVE:
				mode = 5;
				redrawGameBoard();
				next = 1;
				break;
			default:
				continue;
			}
		}
		if (next == 1)
			break;
	}
}
//"SELECT MODE" 출력
void printTitle2() {
	int x = 0, y = 4;
	YELLOW
	//print select
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 4; i++) {
			x = (k * 4) * 2 + i * 2 + 27;
			for (int j = 0; j < 5; j++) {
				SetCurrentCursorPos(x, y + j);
				if (title2[k][j][i] == 1) {
					printf("■");
				}
				else
					printf("  ");
			}
			printf("\n");
		}
		printf("\n");
	}
	//print mode
	y = 12;
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 3; i++) {
			x = (k * 3) * 2 + i * 2 + 6 + 27;
			for (int j = 0; j < 5; j++) {
				SetCurrentCursorPos(x, y + j);
				if (title3[k][j][i] == 1)
					printf("■");

				else
					printf("  ");
			}
			printf("\n");
		}
		printf("\n");
	}
}
//"RIP COVID" 출력
void printTitle1() {
	int x = 0, y = 9;

	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < 3; i++) {
			x = (k * 3) * 2 + i * 2 + 22;
			for (int j = 0; j < 5; j++) {
				SetCurrentCursorPos(x, y + j);
				if (title[k][j][i] == 1)
					printf("■");
				else
					printf("  ");
			}
			printf("\n");
		}
		printf("\n");
	}

	SetCurrentCursorPos(38, 20);
	printf("Press Any Key to Start");
}

void removeCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
//모드 선택
void selectMode() {
	int key;

	drawRect(0, 0, GBOARD_WIDTH, GBOARD_HEIGHT);
	printTitle1();

	while (1) {
		if (_kbhit() != 0) {
			key = _getch();
			redrawGameBoard();
			printTitle2();
			break;
		}
	}

	//classic mode button
	drawRect(5, 20, 16, 5);
	SetCurrentCursorPos(10, 21);
	printf("Classic");
	SetCurrentCursorPos(11, 23);
	printf("Mode");
	//item mode button
	drawRect(23, 20, 16, 5);
	SetCurrentCursorPos(29, 21);
	printf("Item");
	SetCurrentCursorPos(29, 23);
	printf("Mode");
	// invisible mode button
	drawRect(41, 20, 16, 5);
	SetCurrentCursorPos(45, 21);
	printf("Invisible");
	SetCurrentCursorPos(47, 23);
	printf("Mode");
	//hell mode button
	drawRect(59, 20, 16, 5);
	SetCurrentCursorPos(65, 21);
	printf("Hell");
	SetCurrentCursorPos(65, 23);
	printf("Mode");
	//final mode button
	drawRect(78, 20, 16, 5);
	SetCurrentCursorPos(84, 21);
	printf("Final");
	SetCurrentCursorPos(84, 23);
	printf("Mode");

	curPosX = GBOARD_WIDTH;
	curPosY = 0;
	SetCurrentCursorPos(GBOARD_WIDTH, 0);

	//모드 선택하는 입력 키 받기
	modeKeyInput();
}
//목숨 업데이트
void updateLife() {

	SetCurrentCursorPos(104, 5);
	for (int i = 1; i <= 5; i++) {
		if(i <= game_util.life)
			RED
		else
			WHITE
		printf(" ♥ ");
	}
	WHITE
}
//목숨 생성
void createLife() {

	drawRect(101, 4, 27, 3);
	game_util.life = 5;
	game_util.heart = (int*)calloc(5,sizeof(int));

	updateLife();
}
//인간 생성
void createHuman() {

	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}
//바이러스 생성
void createVirus() {

	virus = (Virus*)malloc(5 * sizeof(Virus));

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 5; i++) {
		virus[i].x = rand() % 97 + 1;
		virus[i].y = rand() % 28 + 1;
		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf("*");
	}
}

void createVirusOneby() {

	srand((unsigned int)time(NULL));

	virusOneby[v_num].x = rand() % 97 + 1;
	virusOneby[v_num].y = rand() % 28 + 1;

	SetCurrentCursorPos(virusOneby[v_num].x, virusOneby[v_num].y);
	printf("*");

	v_num++;
}

void createVirusVertical() {
	int i;

	for (i = 0; i < GBOARD_HEIGHT - 2; i++) {
		virusVertical[i].x = 2;
		virusVertical[i].y = 1 + i;

		SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
		printf("*");

	}


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


//바이러스 충돌 검사
int DetectCollisionV() {
	int i, j;

	for (i = 0; i < 10; i++) {
		if (virus[i].x == humanCurPosX && virus[i].y == humanCurPosY) {
			return 2;
		}
	}
	for (i = 0; i < v_num; i++) {
		if (virusOneby[i].x == humanCurPosX && virusOneby[i].y == humanCurPosY) {
			return 2;
		}
	}

	return 1;
}

//충돌 검사
int DetectCollision(int posX, int posY) {

	if (posX == 1 || posX == GBOARD_WIDTH - 2 || posY == 0 || posY == GBOARD_HEIGHT - 1)
		return 0;

	return 1;
}

void ShiftRight(void) {

	if (!DetectCollision(humanCurPosX + 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX += 2;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

}

void ShiftLeft(void) {

	if (!DetectCollision(humanCurPosX - 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX -= 2;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}

void ShiftUp(void) {

	if (!DetectCollision(humanCurPosX, humanCurPosY - 1))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY -= 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}

void ShiftDown(void) {

	if (!DetectCollision(humanCurPosX, humanCurPosY + 1))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY += 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");
}
//추적 바이러스
void trackingVirus() {

	for (int i = 0; i < 5; i++) {
		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf(" ");

		int x, y;
		x = virus[i].x - humanCurPosX;
		y = virus[i].y - humanCurPosY;

		if (x == 0 && y == 0)
			continue;
		else if (x == 0) {
			if (y > 0)
				virus[i].y--;
			else
				virus[i].y++;
		}
		else if (y == 0) {
			if (x > 0)
				virus[i].x--;
			else
				virus[i].x++;
		}
		else if (x > 0 && y > 0) {
			virus[i].x--;
			virus[i].y--;
		}
		else if (x > 0 && y < 0) {
			virus[i].x--;
			virus[i].y++;
		}
		else if (x < 0 && y > 0) {
			virus[i].x++;
			virus[i].y--;
		}
		else {
			virus[i].x++;
			virus[i].y++;
		}

		SetCurrentCursorPos(virus[i].x, virus[i].y);
		printf("*");
	}
}

void trackingVirusOneby() {

	for (int i = 0; i < v_num; i++) {
		SetCurrentCursorPos(virusOneby[i].x, virusOneby[i].y);
		printf(" ");

		int x, y;
		x = virusOneby[i].x - humanCurPosX;
		y = virusOneby[i].y - humanCurPosY;

		if (x == 0 && y == 0)
			continue;
		else if (x == 0) {
			if (y > 0)
				virusOneby[i].y--;
			else
				virusOneby[i].y++;
		}
		else if (y == 0) {
			if (x > 0)
				virusOneby[i].x--;
			else
				virusOneby[i].x++;
		}
		else if (x > 0 && y > 0) {
			virusOneby[i].x--;
			virusOneby[i].y--;
		}
		else if (x > 0 && y < 0) {
			virusOneby[i].x--;
			virusOneby[i].y++;
		}
		else if (x < 0 && y > 0) {
			virusOneby[i].x++;
			virusOneby[i].y--;
		}
		else {
			virusOneby[i].x++;
			virusOneby[i].y++;
		}

		SetCurrentCursorPos(virusOneby[i].x, virusOneby[i].y);
		printf("*");
	}
	vertical_num++;
}

void trackingVirusVertical() {

	for (int i = 0; i < GBOARD_HEIGHT - 2; i++) {

		SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
		printf(" ");

		virusVertical[i].x++;

		SetCurrentCursorPos(virusVertical[i].x, virusVertical[i].y);
		printf("*");
	}
}

//인간 이동
void moveHuman() {
	int key;

	for (int i = 0; i < 100; i++) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key) {
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case UP:
				ShiftUp();
				break;
			case DOWN:
				ShiftDown();
				break;
			}
		}
	}
}

int main() {
	int i, j, num_cnt = 0;
	int check = 0;
	int vertical_cnt = 0;
	int circle_cnt = 0;

	system("mode con:cols=130 lines=30");   // cols: 가로, lines: 세로
	removeCursor();
	selectMode();
	WHITE
	createLife();
	
	createHuman();
	createVirus();

	for (i = 1;; i++) {


		if (_kbhit())
			moveHuman();

		Sleep(100);

		if (_kbhit())
			moveHuman();

		if (i % 100 == 0)
		{
			num_cnt++;
		}

		if (_kbhit())
			moveHuman();

		for (j = 0; j <= num_cnt; j++)
		{
			createVirusOneby();
		}

		if (_kbhit())
			moveHuman();

		trackingVirus();

		if (_kbhit())
			moveHuman();

		trackingVirusOneby();

		if (_kbhit())
			moveHuman();

		check = DetectCollisionV();
		if (check == 2) {
			game_util.life = --game_util.life;
			updateLife();
			SetCurrentCursorPos(humanCurPosX, humanCurPosY);
			RED printf("∩\a");

			Sleep(1000);
		}

		if (check == 2) {
			WHITE
			SetCurrentCursorPos(humanCurPosX, humanCurPosY);
			printf("  ");
			createHuman();
			check = 0;
		}

		if (_kbhit())
			moveHuman();

		if (vertical_num == 10) {
			createVirusVertical();
			//createVirusCircle();
			//createVirusSquare();
			vertical_cnt++;
		}

		if (vertical_cnt >= 1) {
			trackingVirusVertical();
		}

		Sleep(100);

		if (_kbhit())
			moveHuman();

	}
	getchar();
	return 0;
}