#include <iostream>
#include "headers_package.h"
#include <iostream>


int main()
{


	int next_time = 0, prev_time = 0;
	bool game_over = true;
	int platform1Position , platform2Position ; // Variables to store platform positions
	int touch; // Variable to store the touch count
	int player;
	int directionAngle = 90;
	int dx, dy;
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorinfo;
	GetConsoleCursorInfo(hconsole, &cursorinfo);
	cursorinfo.bVisible = false;
	SetConsoleCursorInfo(hconsole, &cursorinfo);
	COORD position = { 0,0 };
	
	char go = '0'; // Variable to store user input
	thread t(periodic, ref(next_time), ref(game_over), ref(directionAngle));
	map myMap;
	myMap.displayMap();

	platform player1(0, myMap.getLength(), myMap.getWidth());
	platform player2(1, myMap.getLength(), myMap.getWidth());
	ball gameBall(myMap.getGrid(), myMap.getLength(), myMap.getWidth());
	
	
	player1.constructPlatform(myMap.getGrid());
	player2.constructPlatform(myMap.getGrid());

	myMap.updatePlatforms(position, hconsole);

	
	gameBall.ballCOORD(position);
	myMap.updateBall(position, hconsole);
	
	platform1Position = myMap.getLength() / 2 + 1, platform2Position = myMap.getLength() / 2 + 1;


	
	while (game_over)
	{
		if (next_time / 2 > prev_time)
		{
			prev_time = next_time / 2;
		//if (GetAsyncKeyState('Q') & 0x8000) {

			gameBall.clearCurrentPos(myMap.getGrid(), position);
			myMap.updateBall(position, hconsole);
			switch (directionAngle)
			{
			case 90:
			{
				dx = 0; dy = 3;
				break;
			}
			case 75:
			{
				dx = 3; dy = 1;
				break;
			}
			case 60:
			{
				dx = 3; dy = 2;
				break;
			}
			case 45:
			{
				dx = 3; dy = 3;
				break;
			}
			case 30:
			{
				dx = 1; dy = 2;
				break;
			}
			case 15:
			{
				dx = 1; dy = 5;
				break;
			}
			default:
				break;
			}
			if (gameBall.move(myMap.getGrid(), myMap.getWidth(), myMap.getLength(), position, myMap.getPoints(), touch, player, dx, dy))
			{
				myMap.updateBall(position, hconsole);
				if (myMap.checkPoints())
				{
					std::this_thread::sleep_for(std::chrono::seconds(3));
					gameBall.resetPosition(myMap.getGrid(), myMap.getLength(), myMap.getWidth(), position, directionAngle);
					system("cls");
					myMap.displayMap();
					
				}
			}
			myMap.updateBall(position, hconsole);
			if (touch > 0)
			{
				if (player == 0) // Player 1
				{
					switch (abs(platform1Position - touch))
					{
					case(1):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 15) % 90;
						break;
					}
					case(2):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 30) % 90;
						break;
					}
					case(3):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 45) % 90;
						break;
					}
					case(4):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 60) % 90;
						break;
					}
					case(5):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 75) % 90;
						break;
					}
					case(-1):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 15) % 90;
						break;
					}
					case(-2):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 30) % 90;
						break;
					}
					case(-3):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 45) % 90;
						break;
					}
					case(-4):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 60) % 90;
						break;
					}
					case(-5):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 75) % 90;
						break;
					}
					default:
						break;

					}
				}
				else if (player == 1) // Player 2
				{
					switch (abs(platform2Position - touch))
					{
					case(1):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 15) % 90;
						break;
					}
					case(2):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 30) % 90;
						break;
					}
					case(3):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 45) % 90;
						break;
					}
					case(4):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 60) % 90;
						break;
					}
					case(5):
					{
						gameBall.setDirectionX(1);
						directionAngle = (directionAngle + 75) % 90;
						break;
					}
					case(-1):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 15) % 90;
						break;
					}
					case(-2):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 30) % 90;
						break;
					}
					case(-3):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 45) % 90;
						break;
					}
					case(-4):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 60) % 90;
						break;
					}
					case(-5):
					{
						gameBall.setDirectionX(-1);
						directionAngle = (directionAngle + 75) % 90;
						break;
					}
					default:
						break;

					}
				}
				
			}

		}
		if (GetAsyncKeyState('W') & 0x8000) {
			player1.upAction(myMap.getGrid());
			myMap.updatePlatforms(position, hconsole);
			platform1Position = player1.gedMidPosition();

		}
		if (GetAsyncKeyState('S') & 0x8000) {
			player1.downAction(myMap.getGrid());
			myMap.updatePlatforms(position, hconsole);
			platform1Position = player1.gedMidPosition();
		}

		if (GetAsyncKeyState('I') & 0x8000) {
			player2.upAction(myMap.getGrid());
			myMap.updatePlatforms(position, hconsole);
			platform2Position = player2.gedMidPosition();
		}
		if (GetAsyncKeyState('K') & 0x8000) {
			player2.downAction(myMap.getGrid());
			myMap.updatePlatforms(position, hconsole);
			platform2Position = player2.gedMidPosition();
		}
		
		Sleep(20);
		if (myMap.checkGameOver())
		{
			game_over = false; // Check if the game is over
			system("cls");
			cout << "Game Over!" << endl; 
		}
	}
	t.detach();
	return 0;
}