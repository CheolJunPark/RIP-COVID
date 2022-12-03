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
	

	if (my_number == random_number && clock_item_flag == 0) {
		clockCurPosX = clock.pos_x;
		clockCurPosY = clock.pos_y;
		SetCurrentCursorPos(clockCurPosX, clockCurPosY);
		printf("C");
		clock_item_flag = 1;
	}
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

