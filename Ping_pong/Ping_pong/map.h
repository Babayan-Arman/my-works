#pragma once

#include <iostream>
#include <windows.h>
using namespace std;

class map
{
public:
	map();
	~map();

	void displayMap() const;
	void displayPoints() const;
	void updatePlatforms(COORD &position, HANDLE &hconsole) const;
	void updateBall(COORD& position, HANDLE& hconsole) ;
	int* getPoints();
	bool checkPoints();
	bool checkGameOver() const;
	int getLength() const;
	int getWidth() const;
	char** getGrid() ;

private:
	int length;
	int width;
	char** grid; // 2D array to represent the map
	int points[2] = { 0, 0 }; // Points for two players, initialized to 0
	int currentPoints[2] = { 0,0 };
};

