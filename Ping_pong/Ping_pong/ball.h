#pragma once

#include <iostream>
#include <windows.h>
using namespace std;

class ball
{
public:
	ball(char** map, int map_length, int map_width);
	~ball();


	void resetPosition(char** map, int map_length, int map_width, COORD& position,int& angle); // Function to reset the position of the ball
	
	void ballCOORD(COORD& position) ;
	void clearCurrentPos(char** map, COORD& position);

	void setDirectionX(int dirX); // Set the direction of movement in X axis
	

	bool move(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player,int dx, int dy);
	
private:
	int x; // X coordinate of the ball
	int y; // Y coordinate of the ball
	int directionX; // Direction of movement in X axis (1 for right, -1 for left)
	int directionY; // Direction of movement in Y axis (1 for down, -1 for up)
	int speed; // Speed of the ball
	char symbol; // Symbol representing the ball
	int* movementQueue; // Queue for movement directions

};














/* 

bool angle90(char** map, int map_width, int map_length, COORD& position, int * points,int& touch, int& player); // Function to move the ball in a straight line
	bool angle45(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player);
	bool angle15(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player);
	bool angle75(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player);
	bool angle30(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player);
	bool angle60(char** map, int map_width, int map_length, COORD& position, int* points, int& touch, int& player);

*/