#include "MyHeader.h"
#include <stdlib.h>
#include <time.h>

extern start_time;
extern end_time;
extern humanCurPosX, humanCurPosY;
extern clock_item_flag;
extern phoenix_item_flag;
extern trackingVirus_flag;
extern trackingVirusOneby_flag;
extern trackingVirusVertical_flag;
extern clockCurPosX, clockCurPosY;
extern clock_item_time;
extern clock_item_time_plus_5sec;

extern phoenixCurPosX, phoenixCurPosY;
extern phoenix_item_time;
extern phoenix_item_time_plus_5sec;


void clock_item() {
	ClockItem clock;
	int my_number = 1;
	int random_number;
	int f = 0;
	int t;


	srand((unsigned int)time(NULL));
	random_number = rand() % 3;
	clock.pos_x = rand() % 97 + 1;
	clock.pos_y = rand() % 28 + 1;
	
	// "C" 아이템 생성
	if (my_number == random_number && clock_item_flag == 0) {
		clockCurPosX = clock.pos_x;
		clockCurPosY = clock.pos_y;
		SetCurrentCursorPos(clockCurPosX, clockCurPosY);
		printf("C");
		clock_item_flag = 1;
	}

	// 인간이 "C" 아이템 먹으면 5초간 일시정지
	if (humanCurPosX == clockCurPosX && humanCurPosY == clockCurPosY) {
		clock_item_flag = 0;
		trackingVirus_flag = 1;
		trackingVirusOneby_flag = 1;
		trackingVirusVertical_flag = 1;


		if (f == 0) {
			t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
			clock_item_time = t;
			clock_item_time_plus_5sec = clock_item_time + 5;
			if (clock_item_time_plus_5sec >= 60)
				clock_item_time_plus_5sec %= 60;
			f = 1;
		}
	}

	// 5초가 지나면 바이러스 다시 움직임
	if (trackingVirus_flag == 1) {
		t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
		if (t == clock_item_time_plus_5sec) {
			trackingVirus_flag = 0;
			trackingVirusOneby_flag = 0;
			trackingVirusVertical_flag = 0;
			f = 0;
		}
	}


}

void phoenix_item() {
	PhoenixItem phoenix;
	int my_number = 2;
	int random_number;
	int f = 0;
	int t;


	srand((unsigned int)time(NULL));
	random_number = rand() % 3;
	phoenix.pos_x = rand() % 97 + 1;
	phoenix.pos_y = rand() % 28 + 1;

	// "P" 아이템 생성
	if (my_number == random_number && phoenix_item_flag == 0) {
		phoenixCurPosX = phoenix.pos_x;
		phoenixCurPosY = phoenix.pos_y;
		SetCurrentCursorPos(phoenixCurPosX, phoenixCurPosY);
		printf("P");
		phoenix_item_flag = 1;
	}

	// 인간이 "P" 아이템 먹으면 5초간 무적 상태
	if (humanCurPosX == phoenixCurPosX && humanCurPosY == phoenixCurPosY) {
		phoenix_item_flag = 2; // 아이템 먹으면 flag = 2



		if (f == 0) {
			t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
			phoenix_item_time = t;
			phoenix_item_time_plus_5sec = phoenix_item_time + 5;
			if (phoenix_item_time_plus_5sec >= 60)
				phoenix_item_time_plus_5sec %= 60;
			f = 1;
		}
	}

	// 5초가 지나면 무적 상태 풀림
	if (phoenix_item_flag == 2) {
		t = (int)(end_time - start_time) / CLOCKS_PER_SEC % 60;
		if (t == phoenix_item_time_plus_5sec) {
			phoenix_item_flag = 0;
			f = 0;
		}
	}
}
