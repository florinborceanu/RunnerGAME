#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "highscoreSys.h"

using namespace std;
struct mapStruct {
	int blockType;
	// 0 - empty
	// 1 - wall
	// 2 - spike
	// 3 - border
	// 4 - floor
	// 5 - scoreBonusPowerup
	// 6 - scoreMultiplierPowerup
	// 7 - slowSpeedPowerup
	char blockStyle;
	// * - border
	// = - floor
	// # - wall
	// ^ - floorSpike
	// v - roofSpike
};
mapStruct map[10][500];
char name[100], password[10];
char cursor = 3;
int jump = 0, y = 4, score = 0, dist = 0, n = 0;
int diff = 100, rarity = 50, hdiff = 3;
int gameStatus = 0, godMode = 0, activatedPowerUp = 0;
int scoreMultiplier, mapSpeed, invulnerability;
highScores highscores[5];

int startMenu();

void gotoXY(int x, int y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#include "powerUpSys.h"
void loadingScreen() {
	system("cls");
	cout << "Loading ... \n\n\n\n\     |";
	for (int i = 0; i < 10; i++)
	{
		cout << "=";
		Sleep(500-(i*50));
	}
	cout << "|";
	Sleep(300);
}

int mainMenu() {
	string Menu[6] = { "Start Game","Instructions", "HighScores","Credits","Reset Highscores", "Exit" };
	int pointer = 0;
	Sleep(250);
	while (true)
	{
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "            Run4Life\n";
		cout << "           Main Menu\n(UP/DOWN to move, SPACE to select)\n\n\n";


		for (int i = 0; i < 6; ++i)
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
					pointer = 5;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 6)
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
					if (startMenu() == 1)
						return 1;
					return 0;
					break;
				} break;
				case 1:
				{
					system("cls");
					cout << "     Instructions: \n - SPACE - jump (chargeable)\n - BonusPowerUP - +100 score";
					cout << "\n - ScoreMultiplierPowerUP - more score for less map";
					cout << "\n - SlowSpeedPowerUP - slow that speed!";
					cout << "\n - InvulnerabilityPowerUP - you are Hulk now";
					cout << "\n - GodMode - you are Hulk, but no highscore for you";
					cout << "\n - When map blinks, prepare for more!";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << "\n\n< Go Back";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Sleep(100);
					while (GetAsyncKeyState(VK_SPACE) == 0)
					{
						Sleep(1);
					}
					return 1;
				} break;
				case 2:
				{
					system("cls");
					cout << "     Highscores:\n";
					showHighscores(highscores);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << "\n\n< Go Back";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Sleep(100);
					while (GetAsyncKeyState(VK_SPACE) == 0)
					{
						Sleep(1);
					}
					return 1;
				} break;
				case 3:
				{
					system("cls");
					cout << "     Credits: \n Game development: Florin Borceanu \n Some help: Google\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << "\n\n< Go Back";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Sleep(100);
					while (GetAsyncKeyState(VK_SPACE) == 0)
					{
						Sleep(1);
					}
					return 1;
				} break;
				case 4:
				{
					system("cls");
					strcpy_s(password, "root");
					char pass[10];
					cout << "Enter the root password: "; cin >> pass;
					if (strcmp(password, pass) == 0)
					{
						resetHighscores(highscores);
						updateHighscores(highscores);
						cout << "\nOk.";
						Sleep(500);
					}
					else
						cout << "Wrong!";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					cout << "\n\n< Go Back";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					Sleep(100);
					while (GetAsyncKeyState(VK_SPACE) == 0)
					{
						Sleep(1);
					}
					return 1;
				}
				break;
				case 5:
				{
					gameStatus = -1;
					updateHighscores(highscores);
					return 0;
				}
				break;
				}
			}
		}

		Sleep(150);
	}
	return 0;
}

int startMenu() {
	string Menu[3] = { "Normal Mode >>","GodMode >>", "<Go Back" };
	int pointer = 0;
	Sleep(250);
	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "      Start new game:\n\n\n";


		for (int i = 0; i < 3; ++i)
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
				Sleep(70);
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				Sleep(70);
				pointer += 1;
				if (pointer == 3)
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
					system("cls");
					cout << "Starting new game ...";
					gameStatus = 0;
					godMode = 0;
					Sleep(500);
					loadingScreen();
					return 0;
				} break;

				case 1:
				{
					strcpy_s(password, "root");
					char pass[10];
					system("cls");
					cout << "Enter the root password: "; cin >> pass;
					if (strcmp(password, pass) == 0)
					{
						cout << "Starting new game as a God ...";
						gameStatus = 0;
						godMode = 1;
						Sleep(500);
						return 0;
					}
					else
						cout << "Wrong ! ";
					Sleep(500);
					return 1;
				} break;
				case 2:
				{
					return 1;
				} break;
				}
			}

			Sleep(150);
		}
	}
	return 0;
}

void firstGenerator() {
	int hight = rand() % hdiff;
	for (int pave = 0; pave < 435; pave++)
	{
		for (int i = 8; i >= 8; i--)
		{
			map[i][pave].blockType = 0;
			map[i][pave].blockStyle = ' ';
		}
		map[9][pave].blockType = 4;
		map[0][pave].blockType = 3;
		map[9][pave].blockStyle = '*';
		map[0][pave].blockStyle = '_';
		if (pave % rarity == 0 && pave < 435 && pave >35)
		{
			if (rand() % 3 == 1)
				for (int i = 0; i < 6 - hight; i++)
				{
					map[8][pave - i].blockType = 2;
					map[8][pave - i].blockStyle = '^';
					if (rand() % 3 == 2)
					{
						map[1][pave - i].blockType = 2;
						map[1][pave - i].blockStyle = 'v';
					}
				}
			else
				for (int i = 8; i >= 8 - hight; i--)
				{
					map[i][pave].blockType = 1;
					map[i][pave].blockStyle = '#';
				}
		}
		if (pave % 100 == 0)
		{
			int random = 0;
			random = rand() % 3 + 6;
			map[5][pave].blockStyle = '?';
			map[5][pave].blockType = random;
		}
	}
}

void mapGenerator(int pave) {
	int hight = rand() % hdiff;	
	for (int i = 0; i <= 8; i++)
	{
		map[i][pave].blockType = 0;
		map[i][pave].blockStyle = ' ';
	}
	map[9][pave].blockType = 4;
	map[0][pave].blockType = 3;
	map[9][pave].blockStyle = '*';
	map[0][pave].blockStyle = '_';
	if (pave % rarity == 0 && pave < 435)
	{
			for (int i = 8; i >= 8 - hight; i--)
			{
				map[i][pave].blockType = 1;
				map[i][pave].blockStyle = '#';
			}
	}
	else if (pave % rarity == 30 && pave < 435)
	{
		for (int i = 0; i <4 - hight; i++)
		{
			map[1][pave - i].blockType = 2;
			map[1][pave - i].blockStyle = 'v';
			map[8][pave-i].blockType = 2;
			map[8][pave-i].blockStyle = '^';			
		}
	}
	if (pave % 200 == 0)
	{
		int random = 0;
		random = rand() % 3 + 6;
		map[5][pave].blockStyle = '?';
		map[5][pave].blockType = random;
	}
	hight = rand() % hdiff;
}


void showMap(int u) {
	char difficultyName[100] = {};
	char powerUpName[100] = {};
	for (int i = 0; i <= 9; i++)
	{
		for (int j = u; j <= u + 50; j++)
		{
			cout << map[i][j].blockStyle;
		}
		cout << endl;
	}
	cout << "Score: " << score;
	if (dist > -1) 
	{
		strcpy_s(difficultyName, "Easy");
	}
	if (dist > 500)
	{
		strcpy_s(difficultyName, "                       ");
		strcpy_s(difficultyName, "Medium-Easy                ");
	}
	if (dist > 1000)
	{
		strcpy_s(difficultyName, "                       ");
		strcpy_s(difficultyName, "Medium                      ");
	}
	if (dist > 1500)
	{
		strcpy_s(difficultyName, "                       ");
		strcpy_s(difficultyName, "Medium-Hard                     ");
	}
	if (dist > 2000)
	{
		strcpy_s(difficultyName, "                       ");
		strcpy_s(difficultyName, "Hard                          ");
	}
	cout << "\nDifficulty: " << difficultyName << endl;
	if (activatedPowerUp == 0)
	{
		strcpy_s(powerUpName, "                       ");
			strcpy_s(powerUpName, "No-One                   ");
	}
	if (activatedPowerUp == 1)
	{
		strcpy_s(powerUpName, "                       ");
		strcpy_s(powerUpName, "Score Multiplier                   ");
	}
	if (activatedPowerUp == 2)
	{
		strcpy_s(powerUpName, "                       ");
		strcpy_s(powerUpName, "Slow Speed                    ");
	}
	if (activatedPowerUp == 3)
	{
		strcpy_s(powerUpName, "                       ");
			strcpy_s(powerUpName, "Invulnerability               ");
	}
	cout << "Active Powerup: " << powerUpName;
	if (godMode == 1) {
		cout << "Distance: " << dist << endl;
	}
}

void clearMap() {
	for (int pave = 0; pave < 500; pave++)
		for (int i = 0; i < 10; i++)
		{
			map[i][pave].blockType = 0;
			map[i][pave].blockStyle = ' ';
		}
}

int main()
{
	unsigned old_clock;
	unsigned current_clock;
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 600, TRUE); // 800 width, 600 height
	loadHighscores(highscores);
	system("cls");
	cout << "What's your name, you mighty runner? : ";
	cin >> name;
	cout << "Ok, " << name << ", let's start !";
	Sleep(1500);
_mainMenu:
	int mainMenuValue;
	mainMenuValue = mainMenu();
	while (mainMenuValue == 1)
		mainMenuValue=mainMenu();
	firstGenerator();
	score = 0;
	rarity = 50;
	dist = 0;
	n = 5;
	activatedPowerUp = 0; mapSpeed = 10; invulnerability = 0; scoreMultiplier = 1;
	while (gameStatus == 0)
		{
		gotoXY(0, 0);
		showMap(n);
		n++;
		if ((jump == 0 || jump < 6)&& GetAsyncKeyState(VK_SPACE) && map[y + 1][n + 3].blockType == 4)
			jump++;
		else if (jump>0)
		{
			y--; jump--;
		}
		else if (y < 8)
		{
			y++;
		}
		if (map[y + 1][n].blockType == 1)
			y--;
		gotoXY(1, y);
		cout << cursor;
		if (godMode == 1 && GetAsyncKeyState(VK_SPACE))
			gameStatus = 1;
		if (map[y][n].blockType != 0 && godMode == 0)
			if (map[y][n].blockType > 4)
			{
				if (map[y][n].blockType > 5)
					old_clock = clock();
				activatePowerUp(map[y][n].blockType);
			}
			else
				if (invulnerability == 0)
					gameStatus = 1;


		current_clock = clock();
		if(activatedPowerUp == 1)
			if (((current_clock - old_clock) / CLOCKS_PER_SEC) <= 5)
			{
				current_clock = clock();
				scoreMultiplier = 2;
			}
			else
			{
				scoreMultiplier = 1;
				activatedPowerUp = 0;
			}
		if (activatedPowerUp == 2)
			if (((current_clock - old_clock) / CLOCKS_PER_SEC) <= 5)
			{
				current_clock = clock();
				mapSpeed = 45;
			}
			else
			{
				mapSpeed = 10;
				activatedPowerUp = 0;
			}
		if (activatedPowerUp == 3)
			if (((current_clock - old_clock) / CLOCKS_PER_SEC) <= 5)
			{
				current_clock = clock();
				invulnerability = 1;
			}
			else
			{
				invulnerability = 0;
				activatedPowerUp = 0;
			}


		if (n % 3 == 0)
			score = score + (1 * scoreMultiplier);
		dist++;
		if(n > 3)
			mapGenerator(n-3);
		if (n == 425)
			n = 5;
		if (dist > 500 && diff == 100)
		{
			rarity = rarity - 5;
			diff = diff - 25;
		}
		if (dist > 1000 && diff ==75)
		{
			rarity = rarity - 5;
			diff = diff - 25;
			hdiff++;
		}
		if (dist > 1500 && diff == 50)
	    {
			rarity = rarity - 5;
			diff = diff - 25;
		}
		if (dist > 2000 && diff == 25)
		{
			rarity = rarity - 5;
			diff = diff - 25;
		}
		Sleep(mapSpeed);
		}

	if (gameStatus == 1)
	{
		system("cls");
		cout << "GAME OVER! " << endl;
		Sleep(500);
		if (score > highscores[4].score && godMode != 1)
		{
				if (score > highscores[3].score)
					if (score > highscores[2].score)
						if (score > highscores[1].score)
							if (score > highscores[0].score)
							{
								cout << "You beat the 1st highscore !";
								addScore(highscores, score, name, 0);
							}
							else
							{
								cout << "You beat the 2nd highscore !";
								addScore(highscores, score, name, 1);
							}
						else
						{
							cout << "You beat the 3rd highscore !";
							addScore(highscores, score, name, 2);
						}
					else
					{
						cout << "You beat the 4th highscore !";
						addScore(highscores, score, name, 3);
					}
				else
				{
					cout << "You beat the 5th highscore !";
					strcpy_s(highscores[4].name, name);
					highscores[4].score = score;
					Sleep(500);
				}
		}
		clearMap();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "\n\n< Go Back to MainMenu";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		Sleep(100);
		while (GetAsyncKeyState(VK_SPACE) == 0)
		{
			Sleep(1);
		}
		goto _mainMenu;
	}

	return 0;
}

