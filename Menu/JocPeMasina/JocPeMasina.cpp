#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#define MAX_MAPHEIGHT 20
#define MAX_MAPLENGTH 50
using namespace std;

CHAR name[100];
CHAR screen[MAX_MAPHEIGHT][MAX_MAPLENGTH] = {};
int gameStatus;

void gotoXY(int x, int y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void startMenu() {
	for (int i = 0; i < MAX_MAPHEIGHT; i++)
		for (int j = 0; j < MAX_MAPLENGTH; j++)
		{
			screen[i][j] = ' ';
			if (i == 0 || i == MAX_MAPHEIGHT-1)
				screen[i][j] = '*';
			if (j == 0 || j == MAX_MAPLENGTH-1)
				screen[i][j] = '|';
		}
	//while (GetAsyncKeyState(VK_ENTER))
}

void showMap() {
	for (int i = 0; i < MAX_MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAX_MAPLENGTH; j++)
			cout << screen[i][j];
		cout << endl;
	}
}

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 470, 350, TRUE);
	startMenu();
	showMap();
	while (gameStatus != -1)
	{
		//showMap();
		Sleep(50);
	}

    return 0;
}

