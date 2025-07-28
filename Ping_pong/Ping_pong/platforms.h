#pragma once

#include <iostream>

using namespace std;

class platform
{
public:
	platform(int player_number, int map_length, int map_width);
	~platform();

	void constructPlatform(char** map);
	void upAction(char** map);
	void downAction(char** map);
	int gedMidPosition() const;
protected:
	int column;
	int midPosition;
};


