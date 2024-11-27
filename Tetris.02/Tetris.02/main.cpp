#include <iostream>
#include "blocks.h"
#include <conio.h>
//#include <cstdlib>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

void periodic(int &new_time,int & levels_point)
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
			else if (milliseconds >=20)
			{
				milliseconds -= 10;
				multiplier++;
			}
		}
		new_time += 1;
		this_thread::sleep_for(chrono::milliseconds(milliseconds));
	}
}

int main()
{
	system("color a");
	playing_field x;
	int next_time = 0, prev_time = 0;
	int levels_point;
	blocks* p = nullptr;
	bool game_over = false;
	bool new_block;
	bool input = false;
	char go = NULL;
	int n1, n2 = (rand() % 14)%7 , n3 = (rand() % 14) % 7, n_reserve=-1;
	thread t(periodic, ref(next_time),ref(levels_point));
	
	
	while (!game_over)
	{
		
		x.points();
		new_block = true;
		srand(time(NULL));
		n1 = n2;
		n2 = n3;
		n3 = rand() % 7;
	
		switch (n1)
		{
		case 0:
		{
			I_shape I(x);
			p = &I;
			break;
		}
		case 1:
		{
			T_shape T(x);
			p = &T;
			break;
		}
		case 2:
		{
			L_shape L(x);
			p = &L;
			break;
		}
		case 3:
		{
			J_shape J(x);
			p = &J;
			break;
		}
		case 4:
		{
			O_shape O(x);
			p = &O;
			break;
		}
		case 5:
		{
			Z_shape Z(x);
			p = &Z;
			break;
		}
		case 6:
		{
			S_shape S(x);
			p = &S;
			break;
		}
		default:
			break;
		}
	
		x.change_queue(n2, n3);
		x.print_field(); 
		//n_reserve = -1;
		while (new_block)
		{
			
			levels_point = x.get_player_points();
			if (next_time / 2 > prev_time)
			{
				prev_time = next_time / 2;
				if (!(p->action_down(x))) new_block = false;
			}
			if (_kbhit())
			{
				go = _getch();
			}
			switch (tolower(go))
			{
			case 's':
			{
				if (!(p->action_down(x))) new_block = false;
					break;
			}
			case 'a':
			{
				p->action_left(x);
				break;
			}
			case 'd':
			{
				p->action_right(x);
				break;
			}
			case 'l':
			{
				p->rotate_right(x);
				break;
			}
			case 'k':
			{
				p->rotate_left(x);
				break;
			}
			case 'w':
			{
				p->hard_drop(x);
				new_block = false;
				break;
			}
			case 'o':
			{
				if (n_reserve == -1)
				{
					p->reserve(x);
					new_block = false;
				}
				else
				{
					p->reserve(x);
					switch (n_reserve)
					{
					case 0:
					{
						I_shape I(x);
						p = &I;
						break;
					}
					case 1:
					{
						T_shape T(x);
						p = &T;
						break;
					}
					case 2:
					{
						L_shape L(x);
						p = &L;
						break;
					}
					case 3:
					{
						J_shape J(x);
						p = &J;
						break;
					}
					case 4:
					{
						O_shape O(x);
						p = &O;
						break;
					}
					case 5:
					{
						Z_shape Z(x);
						p = &Z;
						break;
					}
					case 6:
					{
						S_shape S(x);
						p = &S;
						break;
					}
					default:
						break;
					}

					while (new_block)
					{

						levels_point = x.get_player_points();
						if (next_time / 2 > prev_time)
						{
							prev_time = next_time / 2;
							if (!(p->action_down(x))) new_block = false;
						}
						if (_kbhit())
						{
							go = _getch();
						}
						switch (tolower(go))
						{
						case 's':
						{
							if (!(p->action_down(x))) new_block = false;
							break;
						}
						case 'a':
						{
							p->action_left(x);
							break;
						}
						case 'd':
						{
							p->action_right(x);
							break;
						}
						case 'l':
						{
							p->rotate_right(x);
							break;
						}
						case 'k':
						{
							p->rotate_left(x);
							break;
						}
						case 'w':
						{
							p->hard_drop(x);
							new_block = false;
							break;
						}
						default:
							break;
						}
						go = NULL;
					}
				}
				n_reserve = n1;
				break;
			}
			default:
				break;
			}
			go = NULL;

		}
		game_over = x.game_over();
	}
	t.detach();

	return 0;
}