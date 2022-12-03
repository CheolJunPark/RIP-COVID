#include <windows.h>
#include <process.h>
#include <time.h>

#define GBOARD_WIDTH 100
#define GBOARD_HEIGHT 30

#define COL				GetStdHandle(STD_OUTPUT_HANDLE)
#define BLACK			SetConsoleTextAttribute(COL, 0x0000);
#define DARK_RED		SetConsoleTextAttribute(COL, 0x0004);
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
	int visible;
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

typedef struct ClockItem {
	int pos_x;
	int pos_y;
}ClockItem;

typedef struct PhoenixItem {
	int pos_x;
	int pos_y;
}PhoenixItem;

typedef struct LifeItem {
	int pos_x;
	int pos_y;
}LifeItem;

void ThreadTime();