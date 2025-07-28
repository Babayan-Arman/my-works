#include "ball.h"

ball::ball(char** map, int map_length, int map_width)
{
	x = (map_length / 2); // Start in the middle of the map
	y = (map_width / 2 ); // Start in the middle of the map
	directionX = 0; // Start moving up/down
	directionY = -1; // Start moving right/left
	speed = 1; // Speed of the ball
	symbol = 'O'; // Symbol representing the ball
	
	// Place the ball on the map
	map[x][y] = symbol;
}

void ball::resetPosition(char** map, int map_length, int map_width, COORD& position,int &angle)
{
	x = (map_length / 2 ); // Start in the middle of the map
	y = (map_width / 2 ); // Start in the middle of the map
	ballCOORD(position);
	angle = 90; // Reset angle to 90 degrees
}


void ball::clearCurrentPos(char** map, COORD& position)
{
	map[x][y] = ' ';
	position.X = y; // Set X coordinate of the ball
	position.Y = x; // Set Y coordinate of the ball
}

void ball::setDirectionX(int dirX) { directionX = dirX; } // Set the direction of movement in X axis

void ball::ballCOORD(COORD& position)
{
	position.X = y; // Set X coordinate of the ball
	position.Y = x; // Set Y coordinate of the ball
}

bool ball::move(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player,int dx, int dy)
{
	int platformTouchCoord = -1;
	if (directionY < 0) player = 0; // Player 1
	else player = 1; // Player 2
	if (x + directionX == 0 || x + directionX == (map_length - 1))
	{
		directionX = -directionX;
	}

	if (y + directionY != 0 && y + directionY != map_width - 1)
	{
		y += dy * directionY;  //  <---->
		x += dx * directionX; //      |
		ballCOORD(position);
		map[x][y] = symbol; // Move the ball in the X direction
		if (map[x][y + directionY] == '#')
		{
			platformTouchCoord = x;
		}

		touch = platformTouchCoord;
		return false; //chi poxel uxutyun@
	}
	else
	{
		touch = platformTouchCoord;
		if (map[x][y + directionY] == '#')
		{
			directionY = -directionY;
			y += dy * directionY;
			x += dx * directionX;
			ballCOORD(position);
			map[x][y] = symbol; // Move the ball in the X direction
			
			return false; // poxela uxutyun@
		}
		else
		{
			if (directionY == 1)
			{
				points[0]++;
				cout << "player 1 wins";
			}
			else if (directionY == -1)
			{
				points[1]++;
				cout << "player 2 wins";
			}
			return true; //poxela uxutyun@
		}
	}

}

ball::~ball()
{
}





























/*
bool ball::angle90(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player)
{
	int platformTouchCoord = -1;
	if (directionY < 0) player = 0; // Player 1
	else player = 1; // Player 2
	if (y + directionY != 0 && y + directionY != map_width - 1)
	{
		y += 5 * directionY;
		x += 0 * directionX;
		ballCOORD(position);
		map[x][y] = symbol; // Move the ball in the X direction
		touch = platformTouchCoord;
		return false; //chi poxel uxutyun@
	}
	else
	{
		if (map[x][y + directionY] == '#')
		{
			directionY = -directionY;
			y += 5*directionY;
			ballCOORD(position);
			map[x][y] = symbol; // Move the ball in the X direction
			platformTouchCoord = x;
			touch = platformTouchCoord;
			return false; // poxela uxutyun@
		}
		else
		{
			if (directionY ==1)
			{
				points[1]++;
				cout << "player 1 wins";
			}
			else if(directionY ==-1)
			{
				points[0]++;
				cout << "player 2 wins";
			}
			return true; //poxela uxutyun@
		}
	}

}


bool ball::angle45(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player)
{
	int platformTouchCoord = -1;
	if (directionY < 0) player = 0; // Player 1
	else player = 1; // Player 2
	if(x + directionX == 0 || x + directionX == (map_length - 1))
	{
		directionX = -directionX;
	}

	if (y + directionY != 0 && y + directionY != map_width - 1)
	{
		y += 5 * directionY;
		x += 5 * directionX;
		ballCOORD(position);
		map[x][y] = symbol; // Move the ball in the X direction
		platformTouchCoord = x;
		touch = platformTouchCoord;
		return false; //chi poxel uxutyun@
	}
	else
	{
		if (map[x][y + directionY] == '#')
		{
			directionY = -directionY;
			y += 5 * directionY;
			x += 5 * directionX;
			ballCOORD(position);
			map[x][y] = symbol; // Move the ball in the X direction
			touch = platformTouchCoord;
			return false; // poxela uxutyun@
		}
		else
		{
			if (directionY == 1)
			{
				points[1]++;
				cout << "player 1 wins";
			}
			else if (directionY == -1)
			{
				points[0]++;
				cout << "player 2 wins";
			}
			return true; //poxela uxutyun@
		}
	}
}


bool ball::angle15(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player)
{
	int platformTouchCoord = -1;
	if (directionY < 0) player = 0; // Player 1
	else player = 1; // Player 2
	if (x + directionX == 0 || x + directionX == (map_length - 1))
	{
		directionX = -directionX;
	}

	if (y + directionY != 0 && y + directionY != map_width - 1)
	{
		y += 5 * directionY;
		x += directionX;
		ballCOORD(position);
		map[x][y] = symbol; // Move the ball in the X direction
		platformTouchCoord = x;
		touch = platformTouchCoord;
		return false; //chi poxel uxutyun@
	}
	else
	{
		if (map[x][y + directionY] == '#')
		{
			directionY = -directionY;
			y += 5 * directionY;
			x += directionX;
			ballCOORD(position);
			map[x][y] = symbol; // Move the ball in the X direction
			touch = platformTouchCoord;
			return false; // poxela uxutyun@
		}
		else
		{
			if (directionY == 1)
			{
				points[1]++;
				cout << "player 1 wins";
			}
			else if (directionY == -1)
			{
				points[0]++;
				cout << "player 2 wins";
			}
			return true; //poxela uxutyun@
		}
	}
}

bool ball::angle75(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player)
{
	int platformTouchCoord = -1;
	if (directionY < 0) player = 0; // Player 1
	else player = 1; // Player 2
	if (x + directionX == 0 || x + directionX == (map_length - 1))
	{
		directionX = -directionX;
	}

	if (y + directionY != 0 && y + directionY != map_width - 1)
	{
		y += directionY;
		x += 3 * directionX;
		ballCOORD(position);
		map[x][y] = symbol; // Move the ball in the X direction
		platformTouchCoord = x;
		touch = platformTouchCoord;
		return false; //chi poxel uxutyun@
	}
	else
	{
		if (map[x][y + directionY] == '#')
		{
			directionY = -directionY;
			y += directionY;
			x += 3 * directionX;
			ballCOORD(position);
			map[x][y] = symbol; // Move the ball in the X direction
			touch = platformTouchCoord;
			return false; // poxela uxutyun@
		}
		else
		{
			if (directionY == 1)
			{
				points[1]++;
				cout << "player 1 wins";
			}
			else if (directionY == -1)
			{
				points[0]++;
				cout << "player 2 wins";
			}
			return true; //poxela uxutyun@
		}
	}
}

bool ball::angle30(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player)
{
	int platformTouchCoord = -1;
	if (directionY < 0) player = 0; // Player 1
	else player = 1; // Player 2
	if (x + directionX == 0 || x + directionX == (map_length - 1))
	{
		directionX = -directionX;
	}

	if (y + directionY != 0 && y + directionY != map_width - 1)
	{
		y += 2 * directionY;
		x +=  directionX;
		ballCOORD(position);
		map[x][y] = symbol; // Move the ball in the X direction
		platformTouchCoord = x;
		touch = platformTouchCoord;
		return false; //chi poxel uxutyun@
	}
	else
	{
		if (map[x][y + directionY] == '#')
		{
			directionY = -directionY;
			y += 2 * directionY;
			x += directionX;
			ballCOORD(position);
			map[x][y] = symbol; // Move the ball in the X direction
			touch = platformTouchCoord;
			return false; // poxela uxutyun@
		}
		else
		{
			if (directionY == 1)
			{
				points[1]++;
				cout << "player 1 wins";
			}
			else if (directionY == -1)
			{
				points[0]++;
				cout << "player 2 wins";
			}
			return true; //poxela uxutyun@
		}
	}
}
bool ball::angle60(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player)
{
	int platformTouchCoord = -1;
	if (directionY < 0) player = 0; // Player 1
	else player = 1; // Player 2
	if (x + directionX == 0 || x + directionX == (map_length - 1))
	{
		directionX = -directionX;
	}

	if (y + directionY != 0 && y + directionY != map_width - 1)
	{
		y += 2 * directionY;
		x += 3 * directionX;
		ballCOORD(position);
		map[x][y] = symbol; // Move the ball in the X direction
		touch = platformTouchCoord;
		return false; //chi poxel uxutyun@
	}
	else
	{
		if (map[x][y + directionY] == '#')
		{
			directionY = -directionY;
			y += 2 * directionY;
			x += 3 * directionX;
			ballCOORD(position);
			map[x][y] = symbol; // Move the ball in the X direction
			platformTouchCoord = x;
			touch = platformTouchCoord;
			return false; // poxela uxutyun@
		}
		else
		{
			if (directionY == 1)
			{
				points[1]++;
				cout << "player 1 wins";
			}
			else if (directionY == -1)
			{
				points[0]++;
				cout << "player 2 wins";
			}
			return true; //poxela uxutyun@
		}
	}
}

*/