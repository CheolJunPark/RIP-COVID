#include "MyHeader.h"

int curtime;
extern game_over_flag;

unsigned __stdcall ThreadTime(void) {
	int min = 0;
	int sec = 0;
	while (1)
	{
		if (game_over_flag == 1) 
			break;
		
		Sleep(1000);
		curtime += 1;

		if (game_over_flag == 1)
			break;

		min = sec / 60;
		sec = curtime % 60;
		if (min < 10 && sec < 10) {
			WHITE
			SetCurrentCursorPos(110, 1);
			printf("0%d  :  0%d", min, sec);
		}

		else if (min < 10 && sec >= 10) {
			WHITE
			SetCurrentCursorPos(110, 1);
			printf("0%d  :  %d", min, sec);
		}
		else if (min >= 10 && sec < 10) {
			WHITE
			SetCurrentCursorPos(110, 1);
			printf("%d  :  0%d", min, sec);
		}
		else {
			WHITE
			SetCurrentCursorPos(110, 1);
			printf("%d  :  %d", min, sec);
		}
	}
}

//시간 생성
void createTime() {
	drawRect(101, 0, 27, 3);
	SetCurrentCursorPos(110, 1);
	printf("00  :  00");
}
