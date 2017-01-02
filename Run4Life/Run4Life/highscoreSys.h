#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

struct highScores {
	char name[100];
	int score;
};

void showHighscores(highScores scores[5]) {
	ifstream inFlux("highscores.txt");
	for (int i = 0; i < 5; i++)
	{
		inFlux >> scores[i].name;
		inFlux >> scores[i].score;
		cout << i + 1 << ". " << scores[i].name << endl << "Score: " << scores[i].score << endl;
	}
}

void addScore(highScores scores[5], unsigned int score, char name[50], int position) {
	for (int i = 4; i >= position; i++)
		
}