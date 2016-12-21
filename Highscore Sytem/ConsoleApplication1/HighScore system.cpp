// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct highScores {
	char name[100];
	int score;
};

int main()
{
	highScores scores[5];
	int i = 0;
	ifstream inFlux("date.txt");
	while (i<5)
	{
		inFlux >> scores[i].name;
		inFlux >> scores[i].score;
		i++;
	}
	for (int j = 0; j < i; j++)
	{
		cout << scores[j].name << " " << scores[j].score << endl;
	}
	inFlux.close();
	ofstream outFlux("date.txt");
	for (int j = 0; j < i; j++)
	{
		outFlux << "Nume" << j << " " << j << endl;
	}
	outFlux.close();
	return 0;
}

