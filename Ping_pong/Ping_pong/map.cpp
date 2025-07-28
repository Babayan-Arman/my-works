#include "map.h"

using namespace std;

map::map()
{
	int numL = 2;
	int numW = 8;
	//int a =9 , b = 5 , c = 14;
	length =  (31 * numL)- (numL-1) + 2 ;//numL * 6 - (numL -1) + 2;//3 * 5 + 2;
	width = (31 * numW) - (numW-1) + 2;//numW * 6 - (numW -1) + 2;//15 * 5 + 2;
	grid = new char* [length];

	for (size_t i = 0; i < length; i++)
	{
		grid[i] = new char[width];
	}

	for (size_t i = 0; i < width; i++)
	{
		grid[0][i] = '#'; // Initialize the first row with '#'
		grid[length - 1][i] = '#'; // Initialize the last column with '#'
	}

	for (size_t j = 1; j < length - 1; j++)
	{
		grid[j][0] = ' '; // Initialize the first column with '#'
		grid[j][width - 1] = ' '; // Initialize the first column with '#'
	}

	for (size_t i = 1; i < length - 1; i++)
	{
		for (size_t j = 1; j < width - 1; j++)
		{
			grid[i][j] = ' ';
		}
	}

	//cout << "Map created with default dimensions." << endl;
}

map::~map()
{
	for (size_t i = 0; i < length; i++)
	{
		delete[] grid[i]; // Free each row
	}
	delete[] grid; // Free the array of pointers
	//cout << "Map destroyed." << endl;
}

void map::displayPoints() const
{
	cout << "\t\t\t\t\t\t\tPlayer 1 Points: " << points[0] << " <-> " << points[1] << " :Player 2 Points" <<  endl;
}

void map::displayMap() const
{
	displayPoints();
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << grid[i][j];
		}
		cout << endl;
	}
}

void map::updatePlatforms(COORD &position,HANDLE& hconsole) const
{
	
	for (int i = 1; i < length-1; i++)
	{
		position.X = 0; // Reset X position to the first column
		position.Y = i+1; // Reset Y position to the first row
		SetConsoleCursorPosition(hconsole, position); 
		cout << grid[i][0]; // Display the first column

		position.X = width-1; // Reset X position to the first column
		SetConsoleCursorPosition(hconsole, position);

		cout << grid[i][width - 1]; // Display the first column

	}
	position.X = 0;
	position.Y = 0;
}
void map::updateBall(COORD& position, HANDLE& hconsole) 
{
	int y = position.X, x = position.Y;
	position.Y += 1;
	SetConsoleCursorPosition(hconsole, position);
	//position.Y += 1;

	//grid[position.Y][position.X]  = 'W';
	cout << grid[x][y];
}
int* map::getPoints() { return points; } // Returns the points array for both players
bool  map::checkPoints()
{
	if (points[0] != currentPoints[0] || points[1] != currentPoints[1])
	{
		currentPoints[0] = points[0] ;
		currentPoints[1] = points[1] ;
		return true;
	}
	else false;
}
bool map::checkGameOver() const { return points[0] >= 5 || points[1] >= 5; } // Check if any player has reached 5 points

int map::getLength() const { return length; }
int map::getWidth() const { return width; }
char** map::getGrid()  { return grid; }