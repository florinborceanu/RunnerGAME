#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

struct highScores {
	char name[100];
	int score;
};

void loadHighscores(highScores scores[5])
{
	ifstream inFlux("highscores.txt");
	for (int i = 0; i < 5; i++)
	{
		inFlux >> scores[i].name;
		inFlux >> scores[i].score;
	}
	inFlux.close();
}

void updateHighscores(highScores scores[5])
{
	ofstream outFlux("highscores.txt");
	for (int i = 0; i < 5; i++)
	{
		outFlux << scores[i].name << " ";
		outFlux << scores[i].score << "\n";
	}
	outFlux.close();
}

void showHighscores(highScores scores[5]) {
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ". " << scores[i].name << endl << "Score: " << scores[i].score << endl;
	}
}

void addScore(highScores scores[5], unsigned int score, char nameOne[100], int position) {
	for (int i = 4; i >= position; i--)
	{
		strcpy_s(scores[i+1].name, scores[i].name);
		scores[i + 1].score = scores[i].score;
	}
	strcpy_s(scores[position].name, nameOne);
	scores[position].score = score;
}