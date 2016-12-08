#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

char map[10][500] = {}, cursor = 3;;
int diff = 100, row = 0, jump = 0, y = 4, score = 0;
bool gameOver = false;

void gotoXY(int x, int y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void firstGenerator() {
	for (int index = 1; index < 8; index++)
		for (int pave = 0; pave < 500; pave++)
		{
			if (rand() % diff == 0)
				map[index][pave] = '#';
			map[9][pave] = '#';
			map[0][pave] = '#';
			if (pave == 499)
				map[index][pave] = '#';
		}

}

void mapGenerator() {



}

void showMap(int u) {
	for (int index = 0; index < 10; index++)
	{
		for (int pave = u; pave <= u + 70; pave++)
		{
			cout << map[index][pave];
		}
		cout << endl;
	}
	cout << "Score: " << score << endl;
}

int main()
{
	int n = 0;
	//Console configuration

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 600, TRUE); // 800 width, 600 height

	firstGenerator();
	while (gameOver == false)
		{
		gotoXY(0, 0);
		showMap(n);
		n++;
		if (jump == 0 && GetAsyncKeyState(VK_SPACE) && map[y + 1][n + 3] == '#')
			jump = 3;
		if (jump > 0)
		{
			y--; 
			jump--;
		}
		else if (map[y + 1][n + 4] != '#')
		{
			y++;
		}
		gotoXY(4, y);
		cout << cursor;
		if (map[y][n + 3] == '#')
			gameOver = true;
		score++;
		Sleep(50);
		}
	cout << endl << endl << endl << endl <<  "GAME OVER! " << endl;
	return 0;
}

