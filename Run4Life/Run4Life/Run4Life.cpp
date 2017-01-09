#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "highscoreSys.h"

using namespace std;

char map[10][500] = {}, cursor = 3;
char name[100];
int jump = 0, y = 4, score = 0, n = 0;
int diff = 100, rarity = 35, hdiff = 3;
int gameStatus = 0;
highScores highscores[5];

void gotoXY(int x, int y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void loadingScreen() {
	system("cls");
	cout << "Loading ... \n\n\n\n\     |";
	for (int i = 0; i < 10; i++)
	{
		cout << "=";
		Sleep(1000-(i*100));
	}
	cout << "|";
	Sleep(300);
}

int mainMenu() {
	string Menu[4] = { "Start Game", "HighScores","Credits", "Exit" };
	int pointer = 0;

	while (true)
	{
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "            Run4Life\n";
		cout << "           Main Menu\n(UP/DOWN to move, SPACE to select)\n\n\n";


		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << Menu[i] << endl;
			}
		}

		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_SPACE) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					cout << "\n\n\nStarting new game...";
					Sleep(1000);
					gameStatus = 0;
					loadingScreen();
					return 0;
				} break;
				case 1:
				{
					showHighscores(highscores);
					Sleep(2000);
				} break;
				case 2:
				{
					system("cls");
					cout << "     Credits: \n Game development: Florin Borceanu \n Some help: Google\n";
					Sleep(4000);
				} break;
				case 3:
					gameStatus = -1;
					updateHighscores(highscores);
					return 0;;
				}
				break;
			}
		}

		Sleep(150);
	}
	return 0;
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
	system("cls");
	cout << "What's your name, you mighty runner? : ";
	cin >> name;
	cout << "Ok, " << name << ", let's start !";
	Sleep(500);
	_mainMenu:
	mainMenu();
	firstGenerator();
	score = 0;
	while (gameStatus == 0)
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
			gameStatus = 1;
		score++;
		if(n > 75 && n % rarity == 0)
			mapGenerator();
		if (n == 495)
			n = 5;
		Sleep(20);
		}

	if (gameStatus == 1)
	{
		cout << endl << endl << endl << endl << "GAME OVER! " << endl;
		Sleep(500);
		if (score > highscores[4].score)
		{
			if (score > highscores[3].score)
				if (score > highscores[3].score)
					if (score > highscores[2].score)
						if (score > highscores[1].score)
						{
							//addScore(highscores, score, name, 0);
						}
						else
						{
							//addScore(highscores, score, name, 1);
						}
					else
					{
						//addScore(highscores, score, name, 2);
					}
				else
				{
					//addScore(highscores, score, name, 3);
				}
			else
			{
				cout << "You beat the 5th highscore !";
				strcpy_s(highscores[4].name, name);
				highscores[4].score = score;
				cout << "Splendid ! !";
				Sleep(500);
			}
		}
		Sleep(2500);
		goto _mainMenu;
	}

	return 0;
}

