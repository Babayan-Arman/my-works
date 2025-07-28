#include "time.h"

void periodic(int& new_time, bool& game_over,int &angle)
{
	int faster = 0, addToTicks = 0;
	int ticks;
	switch (angle)
	{
	case 90:
		ticks = 30;
		break;
	case 60:
		ticks = 30;
		break;
	case 30:
		ticks = 20;
		break;
	case 75:
		ticks = 30;
		break;
	case 45:
		ticks = 50;
		break;
	case 15:
		ticks = 50;
		break;
	default:
		break;
	}
	
	while (game_over)
	{
		new_time += 1;
		faster++;
		if (faster == 30) addToTicks += 5;
		this_thread::sleep_for(chrono::milliseconds(ticks - addToTicks));
	}
}