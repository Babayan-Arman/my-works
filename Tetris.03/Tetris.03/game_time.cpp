#include "game_time.h"

void periodic(int& new_time, int& levels_point)
{
	int milliseconds = 600;
	int next_level = 1000, multiplier = 1;
	while (true)
	{
		if (levels_point > multiplier * next_level)
		{
			if (milliseconds >= 100)
			{
				milliseconds -= 50;
				multiplier++;
			}
			else if (milliseconds >= 20)
			{
				milliseconds -= 10;
				multiplier++;
			}
		}
		new_time += 1;
		this_thread::sleep_for(chrono::milliseconds(milliseconds));
	}
}