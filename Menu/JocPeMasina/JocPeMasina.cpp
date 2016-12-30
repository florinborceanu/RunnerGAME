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

void showMap() {
	for (int i = 0; i < MAX_MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAX_MAPLENGTH; j++)
			cout << screen[i][j];
		cout << endl;
	}
}

void startMenu() {

	INT index = 0;
	CHAR cursor = '>';
	for (int i = 0; i < MAX_MAPHEIGHT; i++)
		for (int j = 0; j < MAX_MAPLENGTH; j++)
		{
			screen[i][j] = ' ';
			if (i == 0 || i == MAX_MAPHEIGHT-1)
				screen[i][j] = '*';
			if (j == 0 || j == MAX_MAPLENGTH-1)
				screen[i][j] = '|';
		}


	screen[13][6] = 'S'; screen[13][7] = 't'; screen[13][8] = 'a'; screen[13][9] = 'r'; screen[13][10] = 't'; screen[13][11] = ' '; screen[13][12] = 'G'; screen[13][13] = 'a'; screen[13][14] = 'm'; screen[13][15] = 'e';
	screen[14][6] = 'H'; screen[14][7] = 'i'; screen[14][8] = 'g'; screen[14][9] = 'h'; screen[14][10] = ' '; screen[14][11] = 'S'; screen[14][12] = 'c'; screen[14][13] = 'o'; screen[14][14] = 'r'; screen[14][15] = 'e'; screen[14][16] = 's';
	screen[15][6] = 'C'; screen[15][7] = 'r'; screen[15][8] = 'e'; screen[15][9] = 'd'; screen[15][10] = 'i'; screen[15][11] = 't'; screen[15][12] = 's'; 
	
	while (!GetKeyState(VK_SPACE))
	{
		if (GetAsyncKeyState(VK_UP) && index>0)
		{
			index--;
			screen[4][index] = '>';
			screen[4][index + 1] = ' ';
		}
		if (GetAsyncKeyState(VK_DOWN) && index<3)
		{
			index++;
			screen[4][index] = '>';
			screen[4][index - 1] = ' ';
		}
		Sleep(50);
		showMap();
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

