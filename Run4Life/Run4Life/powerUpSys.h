#include <iostream>
#include <string.h>
using namespace std;

void activatePowerUp(int powerup) {
	if (powerup == 5)
	{
		score = score + 100;
		activatedPowerUp = 0;
	}
	if (powerup == 6)
	{
		activatedPowerUp = 1;
	}
	if (powerup == 7)
	{
		activatedPowerUp = 2;
	}
	if (powerup == 8)
	{
		activatedPowerUp = 3;
	}
}