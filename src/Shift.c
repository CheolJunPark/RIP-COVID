#include "MyHeader.h"

// 오른쪽
void ShiftRight(void) {
	if (!DetectCollision(humanCurPosX + 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX += 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}

// 왼쪽
void ShiftLeft(void) {
	if (!DetectCollision(humanCurPosX - 1, humanCurPosY))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosX -= 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}

// 위쪽
void ShiftUp(void) {
	if (!DetectCollision(humanCurPosX, humanCurPosY - 1))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY -= 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}

// 아래쪽
void ShiftDown(void) {
	if (!DetectCollision(humanCurPosX, humanCurPosY + 1))
		return;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf(" ");
	humanCurPosY += 1;
	SetCurrentCursorPos(humanCurPosX, humanCurPosY);
	printf("@");

	if (spear_xy.get_check == 1)
		spear_wear();
}
