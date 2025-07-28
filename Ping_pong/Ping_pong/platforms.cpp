#include "platforms.h"

platform::platform(int player_number, int map_length, int map_width)
{
	if (player_number == 0)
	{
		column = 0; // Player 1 starts at the leftmost column
	}
	else
	{
		column = map_width - 1; // Player 2 starts at the rightmost column
	}
	// Default column position
	midPosition = map_length/2+1; // Default mid position

	cout << "Platform created for player " << player_number + 1 << " at column " << column << " with mid position " << midPosition << "." << endl;
}
	
void platform::downAction(char** map)
{
	if (map[midPosition+3+3][column] != '#') // Ensure the platform doesn't go out of bounds
	{
		map[midPosition - 2-3][column] = ' '; // Clear the previous position
		midPosition++;
		constructPlatform(map); // Reconstruct the platform at the new position
	}
}

void platform::upAction(char** map)
{
	if (map[midPosition - 3-3][column] != '#') // Ensure the platform doesn't go out of bounds
	{
		map[midPosition + 2+3][column] = ' '; // Clear the previous position
		midPosition--;
		constructPlatform(map); // Reconstruct the platform at the new position
	}
}

void platform::constructPlatform(char** map)  {
	for (int i = -2-3; i < 3+3; i++) {
	//	cout  << " at column " << column << " with mid position " << midPosition+i << "." << endl;

		map[midPosition + i][column] = '#'; // Construct the platform

	}
	

}

int platform::gedMidPosition() const
{
	return midPosition;
}

platform::~platform()
{
}