#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;

char map[10][500] = {}, cursor = 3;;
int jump = 0, y = 4, score = 0, n = 0;
int diff = 100, rarity = 35, hdiff = 3;
bool gameOver = false;

void gotoXY(int x, int y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loadingScreen() {
	cout << "Loading ... \n\n\n\n\     |";
	for (int i = 0; i < 10; i++)
	{
		cout << "=";
		Sleep(1000-(i*50));
	}
	cout << "|";
	Sleep(300);
}

void firstGenerator() {
	int hight = rand() % hdiff;
		for (int pave = 0; pave < 500; pave++)
		{
			if(pave % rarity == 0)
				for (int index = 8; index >= 8 - hight; index--)
				{
					map[index][pave] = '#';
					hight = rand() % hdiff;
				}
			map[9][pave] = '=';
			map[0][pave] = '_';
		}


}

void mapGenerator() {

}

void showMap(int u) {
	for (int i = 0; i <= 9; i++)
	{
		for (int j = u; j <= u + 50; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "Score: " << score << endl;
}

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 600, TRUE); // 800 width, 600 height
	loadingScreen();
	firstGenerator();
	while (gameOver == false)
		{
		gotoXY(0, 0);
		showMap(n);
		n++;
		if ((jump == 0 || jump < 6)&& GetAsyncKeyState(VK_SPACE) && map[y + 1][n + 3] == '=')
			jump++;
		else if (jump>0)
		{
			y--; jump--;
		}
		else if (map[y + 1][n + 3] != '=')
		{
			y++;
		}
		gotoXY(1, y);
		cout << cursor;
		if (map[y][n] == '#')
			gameOver = true;
		score++;
		if(n > 75 && n % rarity == 0)
			mapGenerator();
		if (n == 495)
			n = 5;
		Sleep(20);
		}
	cout << endl << endl << endl << endl << "GAME OVER! " << endl;
	return 0;
}

