extern humanCurPosX;
extern humanCurPosY;


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
