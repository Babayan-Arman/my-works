#include <iostream>
#include <vector>
#include "blocks.h"
#include <windows.h>
using namespace std;


playing_field::playing_field() : height(20), width(28), player_points(0), reserve_empty(true)
{
	for (int i = 0; i < 8; i++)
	{
		reserve_column[i] = reserve_row[i] = 0;
	}
	field = new char* [height];
	/*if (field == nullptr) this->~playing_field();*/
	for (int i = 0; i < height; i++)
	{
		field[i] = new char[width];
		/*if (field[i] == nullptr)
		{
			for (int j = 0; j < i; j++)
			{
				delete[]field[j];
			}
			this->~playing_field();
		}*/
	}
	queue = new char* [height - 14];
	/*if (queue == nullptr)
	{
		for (int j = 0; j < height; j++)
		{
			delete[]field[j];
		}
		this->~playing_field();
	}*/
	for (int i = 0; i < height - 14; i++)
	{
		queue[i] = new char[width + 16];
		/*if (queue[i] == nullptr)
		{

		}*/
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			field[i][j] = '#';
		}
		for (int j = 4; j < 24; j++)
		{
			field[i][j] = '.';
		}
		for (int j = 24; j < width; j++)
		{
			field[i][j] = '#';
		}
	}

	for (int i = 0; i < height-14; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			queue[i][j] =  '#';
		}
		for (int j = 3; j < 13; j++)
		{
			queue[i][j] = '.';
		}
		for (int j = 13; j < 15; j++)
		{
			queue[i][j] = '#';
		}
		for (int j = 15; j < width - 3; j++)
		{
			queue[i][j] = '.';
		}
		for (int j = width - 3; j < width; j++)
		{
			queue[i][j] = '#';
		}
		for (int j = width; j < width + 2; j++)
		{
			queue[i][j] = ' ';
		}
		for (int j = width + 2; j < width + 4; j++)
		{
			queue[i][j] = '#';
		}
		for (int j = width+4; j < width + 14; j++)
		{
			queue[i][j] = '.';
		}
		for (int j = width + 14; j < width + 16; j++)
		{
			queue[i][j] = '#';
		}
		
	}
}
playing_field::~playing_field()
{
	for (int i = 0; i < height; i++)
	{
		delete[]field[i];
	}
		delete[]field;
	for (int i = 0; i < height-14; i++)
	{
		delete[]queue[i];
	}
	delete[]queue;
}
void playing_field::print_field()
{
	//system("cls");
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 0,0 };
	SetConsoleCursorPosition(hconsole,position);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << field[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << " Points : " << player_points << endl;
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}
	for (int i = width; i < width+2; i++)
	{
		cout << " ";
	}
	for (int i = width+2; i < width + 16; i++)
	{
		cout << "#";
	}

	cout  << endl;
	/*for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << '#';
		}
		for (int j = 3; j < 13; j++)
		{
			cout << '.';
		}
		for (int j = 13; j < 15; j++)
		{
			cout << '#';
		}
		for (int j = 15; j < width-3; j++)
		{
			cout << '.';
		}
		for (int j = width-3; j < width; j++)
		{
			cout << '#';
		}
		for (int j = width ; j < width+2 ; j++)
		{
			cout << " ";
		}
		for (int j = width+2; j < width+4; j++)
		{
			cout << '#';
		}
		for (int j = 3; j < 13; j++)
		{
			cout << '.';
		}
		for (int j = 13; j < 15; j++)
		{
			cout << '#';
		}
		cout << endl;
	}*/
	for (int i = 0; i < height-14; i++)
	{
		for (int j = 0; j < width+16; j++)
		{
			cout << queue[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}
	for (int i = width; i < width + 2; i++)
	{
		cout << " ";
	}
	for (int i = width + 2; i < width + 16; i++)
	{
		cout << "#";
	}
	//SetConsoleCursorPosition(hconsole, position);
}
void playing_field::change_field(int row[], int column[])
{
	for (int i = 0; i < 8; i+=2)
	{
		field[row[i]][column[i]] = '[';
		field[row[i+1]][column[i+1]] = ']';
	}
}
void playing_field::delete_space(int row[], int column[])
{
	for (int i = 0; i < 8; i += 2)
	{
		field[row[i]][column[i]] = '.';
		field[row[i + 1]][column[i + 1]] = '.';
	}
}
bool playing_field::valid_down(int row[], int column[])
{
//	{0,0,0,0,1,1,1,1}		   {0,0,1,1,1,1,2,2}
 // {4,5,6,7,6,7,8,9}		   {6,7,4,5,6,7,4,5}
//	 [ ] [ ]					   [ ]
//		 [ ] [ ]				[ ][ ]
//								[ ]
//	height = 2 = 1-0+1
//  width = 3 = (9-4+1)/2

	int row_check[8] = {0,0,0,0,0,0,0,0};
	int column_check[8] = { 0,0,0,0,0,0,0,0 };
	bool copy = false;
	int count=0;
	column_check[count++] = column[0];
	for (int i = 1; i < 8; i++)
	{
		copy = false;
		for (int j = 0; j < count; j++)
		{
			if (column[i] == column_check[j])
			{
				copy = true;
				break;
			}
		}
		if (!copy) column_check[count++] = column[i];
	}
	//for (int i = 0; i < count; i++)
	//{
	//	cout << " " << column_check[i];
	//}
	//cout << endl;
	
	for (int i = 0; i < count; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			if (column_check[i] == column[j])
				if (row[j] > row_check[i]) row_check[i] = row[j];
		}
	}
	//for (int i = 0; i < count; i++)
	//{
	//	cout << " " << row_check[i];
	//}
	copy = true;
	for (int i = 0; i < count; i += 2)
	{
		if (row_check[i] + 1 > 19 || field[row_check[i]+1][column_check[i]] == '[' ) copy = false;
	}
	//cout << endl << endl << endl << endl << endl << endl;

	if (copy) return true;
	else return false;
}
int  playing_field::hard_drop_step(int row[], int column[])
{
	int row_check[8] = { 0,0,0,0,0,0,0,0 };
	int column_check[8] = { 0,0,0,0,0,0,0,0 };
	bool copy = false;
	int count = 0;
	column_check[count++] = column[0];
	for (int i = 1; i < 8; i++)
	{
		copy = false;
		for (int j = 0; j < count; j++)
		{
			if (column[i] == column_check[j])
			{
				copy = true;
				break;
			}
		}
		if (!copy) column_check[count++] = column[i];
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (column_check[i] == column[j])
				if (row[j] > row_check[i]) row_check[i] = row[j];
		}
	}
	int steps = 0;
	copy = true;
	while (copy)
	{
		copy = true;
		for (int i = 0; i < count; i += 2)
		{
			if (row_check[i] + steps > 19 || field[row_check[i] + steps][column_check[i]] == '[') copy = false;
			
		}
		steps++;
	}
	return steps-2;
}
bool playing_field::valid_left(int row[], int column[])
{
//	{0,0,0,0,1,1,1,1}		   {0,0,1,1,1,1,2,2}	   {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}
 // {4,5,6,7,6,7,8,9}		   {6,7,4,5,6,7,4,5}       {10,11,12,13,14,15,16,17}
//	 [ ] [ ]					   [ ]					[   ] [   ] [   ] [   ]
//		 [ ] [ ]				[ ][ ]
//								[ ]
//	height = 2 = 1-0+1			{0,1,2,0}				
//  width = 3 = (9-4+1)/2		{6,4,4,0}

	int row_check[4] = { 0,0,0,0};
	int column_check[4] = { 24,24,24,24};
	bool copy = false;
	int count = 0;
	row_check[count++] = row[0];
	for (int i = 1; i < 8; i++)
	{
		copy = false;
		for (int j = 0; j < count; j++)
		{
			if (row[i] == row_check[j])
			{
				copy = true;
				break;
			}
		}
		if (!copy) row_check[count++] = row[i];
	}
	//for (int i = 0; i < count; i++)
	//{
	//	cout << " " << row_check[i];
	//}
	
	//cout << endl;
	for (int i = 0; i < count; i++)  
	{
		
		for (int j = 0; j < 8; j++)
		{
			if (row_check[i] == row[j])
				if (column[j] < column_check[i]) column_check[i] = column[j];
		}
	}

	/*for (int i = 0; i < count; i++)
	{
		cout << " " << column_check[i];
	}*/
	copy = true;
	for (int i = 0; i < count; i += 1)
	{
		if (column_check[i] - 2 < 4 || field[row_check[i]][column_check[i] - 1] == ']') copy = false;
	}
	//cout << endl << endl << endl << endl << endl << endl;
	if (copy) return true;
	else return false;
}
bool playing_field::valid_right(int row[], int column[])
{
	//	{0,0,0,0,1,1,1,1}		   {0,0,1,1,1,1,2,2}	   {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}
	 // {4,5,6,7,6,7,8,9}		   {6,7,4,5,6,7,4,5}       {10,11,12,13,14,15,16,17}
	//	 [ ] [ ]					   [ ]					[   ] [   ] [   ] [   ]
	//		 [ ] [ ]				[ ][ ]
	//								[ ]
	//	height = 2 = 1-0+1			{0,1,2,0}				
	//  width = 3 = (9-4+1)/2		{6,4,4,0}

	int row_check[4] = { 0,0,0,0 };
	int column_check[4] = { 0,0,0,0 };
	bool copy = false;
	int count = 0;
	row_check[count++] = row[0];
	for (int i = 1; i < 8; i++)
	{
		copy = false;
		for (int j = 0; j < count; j++)
		{
			if (row[i] == row_check[j])
			{
				copy = true;
				break;
			}
		}
		if (!copy) row_check[count++] = row[i];
	}
	/*for (int i = 0; i < count; i++)
	{
		cout << " " << row_check[i];
	}*/

	cout << endl;
	for (int i = 0; i < count; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			if (row_check[i] == row[j])
				if (column[j] > column_check[i]) column_check[i] = column[j];
		}
	}
	/*for (int i = 0; i < count; i++)
	{
		cout << " " << column_check[i];
	}*/
	copy = true;
	for (int i = 0; i < count; i += 1)
	{
		if (column_check[i] + 2 > 24 || field[row_check[i]][column_check[i] + 1] == '[') copy = false;
	}
	//cout << endl << endl << endl << endl << endl << endl;
	if (copy) return true;
	else return false;
}
bool playing_field::valid_rotate(vector<vector<int>>& row_flags, vector<vector<int>>& column_flags,\
	bool& rotate_horizontally,bool& rotate_vertically)
{
	/*for (int i = 0; i < row_flags.capacity(); i++)
	{
		for (int j = 0; j < column_flags.capacity(); j++)
		{
			cout << row_flags[i][j] << "  "  ;
		}

		cout << endl;
	}
	cout << endl << "**************************** " << endl;
	for (int i = 0; i < row_flags.capacity(); i++)
	{
		for (int j = 0; j < column_flags.capacity(); j++)
		{
			cout << column_flags[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;*/
	if (!rotate_horizontally && !rotate_vertically || rotate_horizontally && rotate_vertically)
	{

		for (int i = 0; i < row_flags.capacity(); i++)
		{
			for (int j = 0; j < column_flags.capacity(); j++)
			{
				if (row_flags[i][j] == 30)continue;
				if (i == 0)
				{
					if (row_flags[i][j] < 0 || field[row_flags[i][j]][column_flags[i][j]] == '[')
					{
						/*for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << row_flags[i][j] << "  ";
							}

							cout << endl;
						}
						cout << endl << "**************************** " << endl;
						for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << column_flags[i][j] << "  ";
							}
							cout << endl;

						}
						cout << endl << "i = " << 0;*/

						return false;
					}
						
				}
				else if (i == row_flags.capacity() - 1)
				{
					if (row_flags[i][j] > 19 || field[row_flags[i][j]][column_flags[i][j]] == '[')
					{
						/*for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << row_flags[i][j] << "  ";
							}

							cout << endl;
						}
						cout << endl << "**************************** " << endl;
						for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << column_flags[i][j] << "  ";
							}
							cout << endl;
						}
						cout << endl << "i = " << row_flags.capacity() - 1;*/

						return false;
					}
				}
				
				else
					if (field[row_flags[i][j]][column_flags[i][j]] == '[') 
					{
						/*for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << row_flags[i][j] << "  ";
							}

							cout << endl;
						}
						cout << endl << "**************************** " << endl;
						for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << column_flags[i][j] << "  ";
							}
							cout << endl ;
						}
						cout << endl << "i = else" << endl;*/

						return false;
					}
			}
		}
	}

	if (!rotate_horizontally && rotate_vertically || rotate_horizontally && !rotate_vertically)
	{
		for (int j = 0; j < column_flags.capacity(); j++)
		{
			for (int i = 0; i < row_flags.capacity(); i++)
			{
				if (row_flags[i][j] == 30)continue;
				if (j == 0)
				{
					if (column_flags[i][j] < 4 || field[row_flags[i][j]][column_flags[i][j]] == '[')
					{
						/*for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << row_flags[i][j] << "  ";
							}

							cout << endl;
						}
						cout << endl << "**************************** " << endl;
						for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << column_flags[i][j] << "  ";
							}
							cout << endl;

						}
						cout << endl << "i = " << 0 << endl;*/

						return false;
					}

				}
				else if (j == column_flags.capacity() - 1)
				{
					if (column_flags[i][j] > 23 || field[row_flags[i][j]][column_flags[i][j]] == '[')
					{
						/*for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << row_flags[i][j] << "  ";
							}

							cout << endl;
						}
						cout << endl << "**************************** " << endl;
						for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << column_flags[i][j] << "  ";
							}
							cout << endl;
						}
						cout << endl << "i = " << row_flags.capacity() - 1;*/

						return false;
					}
				}

				else
					if (field[row_flags[i][j]][column_flags[i][j]] == '[')
					{
						/*for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << row_flags[i][j] << "  ";
							}

							cout << endl;
						}
						cout << endl << "**************************** " << endl;
						for (int i = 0; i < row_flags.capacity(); i++)
						{
							for (int j = 0; j < column_flags.capacity(); j++)
							{
								cout << column_flags[i][j] << "  ";
							}
							cout << endl;

						}
						cout << endl << "i = else" << endl;*/
						return false;
					}
			}
		}
	}
	return true;
}
//
	//:rotate_horizontaly-rotate_verticaly			
	//:0-0				  :0-1				:1-1				:1-0  
	//---------------------------------------------------------------------------
	//:1-2   O	O	O	  :2-3	    [ ]	 O	:3-4	  O			:4-1	  [ ] O
	//      [ ][->][V][ ]		 xx [V]	 O 		   O  Ox xx  			O [->]Ox O					
	//			xx  Ox O	   O Ox [<-] O		  [ ][^][<-][ ]			O [^] xx											
	//				O			 O  [ ]				  O	  O  O 			O [ ]		
	//                      |                   |                     |                   |
	//	{11/11/11/11/11/11/11/11}	| {10/10/11/11/12/12/13/13} | {2/2/2/2/2/2/ 2/ 2} | {0/0/1/1/2/2/3/3} |
	//  {4 /5 /6 /7 /8 /9 /10/11}	| {8 /9 /8 /9 /8 /9 /8 / 9} | {4/5/6/7/8/9/10/11} | {6/7/6/7/6/7/6/7} |
	//                      |                   |                     |                   |
	//
	//
	//		O-flagner te vortex blok linelu depqum chi pttvi		
//
	//:rotate_horizontaly-rotate_verticaly			
	//:0-0				  :0-1				:1-1				:1-0  
	//---------------------------------------------------------------------------
	//:1-2   O	O	O	  :2-3	    [ ]	 O	:3-4	  O			:4-1	  [ ] O
	//      [ ][->][V][ ]		 xx [V]	 O 		   O  Ox xx  			O [->]Ox O					
	//			xx  Ox O	   O Ox [<-] O		  [ ][^][<-][ ]			O [^] xx											
	//				O			 O  [ ]				  O	  O  O 			O [ ]		
	//                      |                   |                     |                   |
	//	{11/11/11/11/11/11/11/11}	| {10/10/11/11/12/12/13/13} | {2/2/2/2/2/2/ 2/ 2} | {0/0/1/1/2/2/3/3} |
	//  {4 /5 /6 /7 /8 /9 /10/11}	| {8 /9 /8 /9 /8 /9 /8 / 9} | {4/5/6/7/8/9/10/11} | {6/7/6/7/6/7/6/7} |
	//                      |                   |                     |                   |
	//
	//
	//		O-flagner te vortex blok linelu depqum chi pttvi		

void playing_field::points()
{
	int lines = 0;                  // 1 line - 100 points /  1/100
	bool its_line;					// 2 line - 300 points /  1/150
	for (int i = 0; i < 20; i++)	// 3 line - 600 points /  1/200
	{								// 4 line - 1000 points/  1/250	
		its_line = true;
		for (int j = 4; j < 24; j+=2)
		{
			
			if (!(field[i][j] == '['))
			{
				its_line = false;
			}
		}
		if (its_line)
		{
		/*	for (int m = 4; m < 24; m++)
			{
				field[i][m] = '.';
			}*/
			lines++;
			for (int m = 4; m < 24; m++)
			{
				for (int n = i; n > 0; n--)
				{
					field[n][m] = field[n - 1][m];
				}
				field[0][m] = '.';
			}
		}
	}
	player_points += lines * (50 * lines + 50);
}
int playing_field::get_player_points()
{
	return player_points;
}
bool playing_field::game_over()
{
	if (field[1][width / 2] == '[' || field[1][(width / 2)+1] == '[' || \
		field[0][width / 2] == '[' || field[0][(width / 2) + 1] == '[')
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl;
		cout << "        ###########        ##########         #########       #########   ############         " << endl;
		cout << "     ####                 ####    ###        ####  ####      ####  ####   ############         " << endl;
		cout << "   ###                   ####     ###       ####   ####     ####   ####   ####                 " << endl;
		cout << "  ##       ########     ####      ###      ####    ####    ####    ####   ############         " << endl;
		cout << "   ###          ##    ###############     ####     ####   ####     ####   ############         " << endl;
		cout << "    ####      ####   ####         ###    ####      ####  ####      ####   ####                 " << endl;
		cout << "     ####    ####   ####          ###   ####       #### ####       ####   ############         " << endl;
		cout << "      ##########   ####           ###  ####        ########        ####   ############         " << endl<<endl;
		cout << "\t        ######     ####              ####  ############   ############       " << endl;
		cout << "\t      ###    ###    ####            ####   ############   ####     ####      " << endl;
		cout << "\t     ###      ###    ####          ####    ####           ####     ####      " << endl;
		cout << "\t    ###        ###    ####        ####     ############   ####   ####        " << endl;
		cout << "\t     ###      ###      ####      ####      ############   ########           " << endl;
		cout << "\t      ###    ###        ####    ####       ####           ####  ####         " << endl;
		cout << "\t       ###  ###          ####  ####        ############   ####    ####       " << endl;
		cout << "\t        ######            ########         ############   ####      ####     " << endl;
		cout << "\n\n\t\t\t\t\tYour Points : " << player_points << endl;
		return true;
	}
	return false;
}

void playing_field::delete_queue()
{
	for (int i = 1; i < height - 15; i++)
	{
		for (int j = 4; j < 12; j++)
		{
			queue[i][j] = '.';
		}
	}
	for (int i = 1; i < height - 15; i++)
	{
		for (int j = 16; j < 24; j++)
		{
			queue[i][j] = '.';
		}
	}
}
void playing_field::change_queue(int& n2,int& n3)
{
	delete_queue();
	switch (n2)
	{
	case 0:
	{
		for (int i = 0; i < 8; i += 2)					//{2/2/2/2/2/2/ 2/ 2}
		{												//{4/5/6/7/8/9/10/11}
			queue[2][i + 4] = '['; 
			queue[2][i + 5] = ']';
		}
		break;
	}
	case 1:
	{
		queue[2][7] = '[';			//{1,1,1,1,1,1,0,0 }
		queue[2][7 + 1] = ']';		//{4,5,6,7,8,9,6,7 }
		for (int i = 0; i < 6; i += 2)
		{
			queue[3][i + 5] = '[';
			queue[3][i + 6] = ']';
		}
		break;
	}
	case 2:
	{		
		queue[2][5] = '[';			//{ 0,0,1,1,1,1,1,1 }
		queue[2][6] = ']';			//{ 4,5,4,5,6,7,8,9 }
		for (int i = 0; i < 6; i += 2)
		{
			queue[3][i + 5] = '[';
			queue[3][i + 6] = ']';
		}

		break;
	}
	case 3:
	{
		queue[2][9] = '[';			//{ 0,0,1,1,1,1,1,1}
		queue[2][10] = ']';			//{ 8,9,4,5,6,7,8,9}
		for (int i = 0; i < 6; i += 2)
		{
			queue[3][i + 5] = '[';
			queue[3][i + 6] = ']';
		}
		break;
	}
	case 4:
	{
		for (int i = 0; i < 4; i += 2)	//{0,0,0,0,1,1,1,1}
		{								//{4,5,6,7,4,5,6,7}
			queue[2][i + 6] = '[';
			queue[2][i + 7] = ']';
			queue[3][i + 6] = '[';
			queue[3][i + 7] = ']';
		}
		
		break;
	}
	case 5:
	{
		for (int i = 0; i < 4; i += 2)	//{0,0,0,0,1,1,1,1}
		{								//{4,5,6,7,6,7,8,9}
			queue[2][i + 5] = '[';
			queue[2][i + 6] = ']';
			queue[3][i + 7] = '[';
			queue[3][i + 8] = ']';
		}
		break;
	}
	case 6:
	{
		for (int i = 0; i < 4; i += 2)	//{0,0,0,0,1,1,1,1}
		{								//{6,7,8,9,4,5,6,7}
			queue[3][i + 5] = '[';
			queue[3][i + 6] = ']';
			queue[2][i + 7] = '[';
			queue[2][i + 8] = ']';
		}
		break;
	}
	default:
		break;
	}
	switch (n3)
	{
	case 0:
	{
		for (int i = 0; i < 8; i += 2)					//{2/2/2/2/2/2/ 2/ 2}
		{												//{4/5/6/7/8/9/10/11}
			queue[2][i + 4 + 12] = '[';
			queue[2][i + 5 + 12] = ']';
		}
		break;
	}
	case 1:
	{
		queue[2][7 + 12] = '[';			//{1,1,1,1,1,1,0,0 }
		queue[2][7 + 1 + 12] = ']';		//{4,5,6,7,8,9,6,7 }
		for (int i = 0; i < 6; i += 2)
		{
			queue[3][i + 5 + 12] = '[';
			queue[3][i + 6 + 12] = ']';
		}
		break;
	}
	case 2:
	{
		queue[2][5 + 12] = '[';			//{ 0,0,1,1,1,1,1,1 }
		queue[2][6 + 12] = ']';			//{ 4,5,4,5,6,7,8,9 }
		for (int i = 0; i < 6; i += 2)
		{
			queue[3][i + 5 + 12] = '[';
			queue[3][i + 6 + 12] = ']';
		}

		break;
	}
	case 3:
	{
		queue[2][9 + 12] = '[';			//{ 0,0,1,1,1,1,1,1}
		queue[2][10 + 12] = ']';			//{ 8,9,4,5,6,7,8,9}
		for (int i = 0; i < 6; i += 2)
		{
			queue[3][i + 5 + 12] = '[';
			queue[3][i + 6 + 12] = ']';
		}
		break;
	}
	case 4:
	{
		for (int i = 0; i < 4; i += 2)	//{0,0,0,0,1,1,1,1}
		{								//{4,5,6,7,4,5,6,7}
			queue[2][i + 6 + 12] = '[';
			queue[2][i + 7 + 12] = ']';
			queue[3][i + 6 + 12] = '[';
			queue[3][i + 7 + 12] = ']';
		}

		break;
	}
	case 5:
	{
		for (int i = 0; i < 4; i += 2)	//{0,0,0,0,1,1,1,1}
		{								//{4,5,6,7,6,7,8,9}
			queue[2][i + 5 + 12] = '[';
			queue[2][i + 6 + 12] = ']';
			queue[3][i + 7 + 12] = '[';
			queue[3][i + 8 + 12] = ']';
		}
		break;
	}
	case 6:
	{
		for (int i = 0; i < 4; i += 2)	//{0,0,0,0,1,1,1,1}
		{								//{6,7,8,9,4,5,6,7}
			queue[3][i + 5 + 12] = '[';
			queue[3][i + 6 + 12] = ']';
			queue[2][i + 7 + 12] = '[';
			queue[2][i + 8 + 12] = ']';
		}
		break;
	}
	default:
		break;
	}
}
void playing_field::delete_reserve()
{
	for (int i = 0; i < height - 14; i++)
	{
		for (int j = width +4; j < width+14; j++)
		{
			queue[i][j] = '.';
		}
	}
}
void playing_field::change_reserve(int row[], int column[])  //stex avelanem amen figuri tvery zapasi hamar
{
				//{1,1,1,1,1,1,0,0 }
				//{4,5,6,7,8,9,6,7 }
	
	int high, lenght;
	if (reserve_empty)
	{
		for (int i = 0; i < 8; i += 1)
		{
			reserve_row[i] = row[i];
			reserve_column[i] = column[i];
		}
		high = reserve_row[0] - 2;
		lenght = 28 - reserve_column[0] + 5; //tver@ amen figur irany kunena vor sirun lini
		for (int i = 0; i < 8; i += 1)
		{
			row[i] -= high;  
			column[i] += lenght;
		}
		cout << endl;
		cout << "{";
		for (int i = 0; i < 8; i += 1)
		{
			cout << reserve_row[i] << ",";
		}
		cout << "}" << endl << "{";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << reserve_column[i] << ",";
		}
		cout << "}" << endl << "{";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row[i] << ",";
		}
		cout << "}" << endl << "{";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << column[i] << ",";
		}
		cout << "}" << endl;
		delete_space(reserve_row, reserve_column);
		for (int i = 0; i < 8; i+=2)
		{
			queue[row[i]][column[i]] = '[';
			queue[row[i+1]][column[i+1]] = ']';
		}
		reserve_empty = false;
	}
	else
	{
		delete_space(row, column);
		delete_reserve(); 
		int k;
		for (int i = 0; i < 8; i += 1)
		{
			k = reserve_row[i];
			reserve_row[i] = row[i];
			row[i] = k;
			k = reserve_column[i];
			reserve_column[i] = column[i];
			column[i] = k;
		}
		high = reserve_row[0] - 1;
		lenght = 28 - reserve_column[0] + 8;
		
		cout << endl;
		cout << "[";
		for (int i = 0; i < 8; i += 1)
		{
			cout << reserve_row[i] << ",";
		}
		cout << "]" << endl << "[";
		for (int i = 0; i < 8; i += 1)
		{
			cout << reserve_column[i] << ",";
		}
		cout << "]" << endl << "[";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row[i] << ",";
		}
		cout << "]" << endl << "[";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column[i] << ",";
		}
		cout << "]" << endl;

		/*for (int i = 0; i < 8; i += 1)
		{
			row[i] -= high;
			column[i] += lenght;
		}*/
		for (int i = 0; i < 8; i += 2)
		{
			queue[reserve_row[i]- high][reserve_column[i]+lenght] = '[';
			queue[reserve_row[i + 1]-high][reserve_column[i + 1]+lenght] = ']';
		}
		cout  << endl << "[";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row[i] << ",";
		}
		cout << "]" << endl << "[";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column[i] << ",";
		}
		cout << "]" << endl;
	
	}
	for (int i = 0; i < 8; i++)
	{
		
	}
}

//blocks::blocks() {}
//blocks::~blocks() {}
//blocks* blocks::start(blocks* ptr, playing_field& x)

//bool blocks::action_down(playing_field& field) { return true; }
//bool blocks::action_left(playing_field& field) { return true; }
//bool blocks::action_right(playing_field& field) { return true; }
//bool blocks::rotate_right(playing_field& field) { return true; }
//bool blocks::rotate_left(playing_field& field) { return true; }

I_shape::I_shape(playing_field& field)
{
	for (int i = 0; i < 8; i++)
		row_position[i] = 0;
	for (int i = 0; i < 8; i++)
		column_position[i] = i+10;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool I_shape::action_down(playing_field& field)
{
	if (!field.valid_down(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i]++;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool I_shape::action_left(playing_field& field)
{
	if (!field.valid_left(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i]-=2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool I_shape::action_right(playing_field& field)
{
	if (!field.valid_right(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] += 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool I_shape::rotate_right(playing_field& field)
{
	//
	//:rotate_horizontaly-rotate_verticaly			
	//:0-0						 :0-1					:1-1						:1-0  
	//-----------------------------------------------------------------------------------------------------
	//:1-2   O	O	O			:2-3	    [ ] O		:3-4	O				   :4-1   [ ] O
	//      [ ][->][V][ ]				 xx [V]	O 			 O  Ox xx  					O [->]Ox O					
	//			xx  Ox O			  O Ox [<-] O			[ ][^][<-][ ]				O [^] xx											
	//				O					 O  [ ]			     	 O	O  O 				O [ ]		
	//							|						|							|                      |
	//	{0/0/0/0/0/0/ 0/ 0}		| {0/0/1/1/2/2/3/3}		| {2/2/2/2/2/2/ 2/ 2}		| {0/0/1/1/2/2/3/3}    |
	//  {4/5/6/7/8/9/10/11}		| {8/9/8/9/8/9/8/9}		| {4/5/6/7/8/9/10/11}		| {6/7/6/7/6/7/6/7}    |
	//							|						|							|					   |
	//  {-1,-1,-1,1,1 ,2}		| { 0, 1,2,2, 2,3}		|	{-2,-1,-1,1,1, 1}		| {0,1,1, 1,2,3}	   |
	//	{ 4, 6, 8,8,10,8}		| {10,10,4,6,10,6}		|	{ 6, 4, 6,6,8,10}		| {8,4,8,10,4,4}	   |
	//							|						|							|					   |
	//  [-1 -1 -1 0  [4 6 8 0   |  [0 0 0 O  [0 0 0 10  |  [ 0 -2 0 0  [0 6 0 0		|  [0 0 O 0  [0 0 8 0  |                         
	//    0  0  0 0   0 0 0 0   |   0 0 0 1   0 0 0 10  |   -1 -1 0 0   4 6 0 0	  	|  1 0 1 1   4 0 8 10  |                
	//    0  0  1 1   0 0 8 10  |   2 2 0 2   4 6 0 10  |    0  0 0 0   0 0 0 0		|  2 0 0 0   4 0 0 0   |           
	//    0  0  2 0]  0 0 8 0]  |   0 3 0 0]  0 6 0 0]  |    0  1 1 1]  0 6 8 10]	|  3 0 0 0]  4 0 0 0]  |               
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//               
	vector<vector<int>> row_flags(4, vector<int>(4, 30)), column_flags(4, vector<int>(4, 30));

	if (!rotate_Horizontally && !rotate_Vertically )
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 0; i < 6; i += 2)
		{
			row_flags[0][i/2] = row_position[i] - 1;
			column_flags[0][i/2] = column_position[i];
		}
		for (int i = 4; i < 8; i += 2)
		{
			row_flags[2][i/2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i];
		}
		row_flags[3][2] = row_position[4] + 2;
		column_flags[3][2] = column_position[4];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 8; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + (i - 2) / 2;
				column_position[i] = column_position[4];
				column_position[i + 1] = column_position[4 + 1];
			}
		/*	cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
	/*	cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 6; i += 2)
		{
			row_flags[i / 2][3] = row_position[i];
			column_flags[i / 2][3] = column_position[i]+2;
		}
		for (int i = 4; i < 8; i += 2)
		{
			row_flags[2][i%4 / 2] = row_position[4];
			column_flags[2][i%4 / 2] = column_position[4]-(2*(i/2-i%4));
		}
		row_flags[3][1] = row_position[6];
		column_flags[3][1] = column_position[4]-2;

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			int column_first = column_position[0]-4;

			field.delete_space(row_position, column_position);
		
			for (int i = 0; i < 8; i += 1)
			{
				row_position[i] = row_position[4];
			}
			for (int i = 0; i < 8; i++)
			{
				column_position[i] = column_first + i;
			}
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	

	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 8; i += 2)
		{
			row_flags[3][i / 2] = row_position[i] + 1;
			column_flags[3][i / 2] = column_position[i];
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[1][i / 2] = row_position[i] - 1;
			column_flags[1][i / 2] = column_position[i];
		}
		row_flags[0][2] = row_position[2] - 2;
		column_flags[0][2] = column_position[2];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 8; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] - 1 + (i - 2) / 2;
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}
	

	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 8; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[i] - 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[i] + 2;
		}
		row_flags[1][3] = row_position[4];
		column_flags[1][3] = column_position[4] + 4;

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);
			for (int i = 0; i < 8; i += 1)
			{
				row_position[i] = row_position[2];

			}
			for (int i = 0; i < 8; i++)
			{
				column_position[i] = column_first + i;
			}
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}

	return false;
}
bool I_shape::rotate_left(playing_field& field)
{
	//
	//:rotate_horizontaly-rotate_verticaly			
	//:0-0						 :0-1					:1-1						:1-0  
	//-----------------------------------------------------------------------------------------------------
	//:1-2   O	O	O			:2-3	    [ ] O		:3-4	O				   :4-1   [ ] O
	//      [ ][->][V][ ]				 xx [V]	O 			 O  Ox xx  					O [->]Ox O					
	//			xx  Ox O			  O Ox [<-] O			[ ][^][<-][ ]				O [^] xx											
	//				O					 O  [ ]			     	 O	O  O 				O [ ]		
	//
	//:0-0                         :1-0                   :1-1                       :0-1                                     
	// ----------------------------------------------------------------------------------------------------                                                                                                           
	//          O   O  O              O [ ]                          O                  O  [ ]                                    
	//      [ ][V][<-][ ]             O [V] xx                  xx  xO  O            O xO [<-] O                                               
	//       O  Ox  xx                O [->]Ox O            [ ][->][ ^][ ]             xx  [^] O                                             
	//          O                       [ ] O                O   O   O                     [ ] O                                
	//				
	//	{1/1/1/1/1/1/ 1/ 1}		| {0/0/1/1/2/2/3/3}		| {2/2/2/2/2/2/ 2/ 2}		| {0/0/1/1/2/2/3/3}    |
	//  {4/5/6/7/8/9/10/11}		| {6/7/6/7/6/7/6/7}		| {4/5/6/7/8/9/10/11}		| {8/9/8/9/8/9/8/9}    |
	//							|						|							|					   |
	//  {0,0,0, 2,2,3}			| {0,1,2,2, 2,3}		|	{0,1, 1,3,3,3}			| {0,1,1, 1, 2, 3}	   |
	//	{6,8,10,4,6,6}			| {4,4,4,8,10,8}		|	{8,8,10,4,6,8}			| {6,4,6,10,10,10}	   |
	//							|						|							|					   |
	//  [ 0  O  O  O  [0 6 8 10 |   [O 0 0 0  [4 0 0 0  |  [ 0 0 O 0  [0 0 8 0		|  [0 O 0 0  [0 6 0 0  |                         
	//    0  0  0  0   0 0 0 0  |    1 0 0 0   4 0 0 0  |    0 0 1 1   0 0 8 10	  	|   1 1 0 1   4 6 0 10 |                
	//    2  2  0  0   4 6 0 0  |    2 0 2 2   4 0 8 10 |    0 0 0 0   0 0 0 0		|   0 0 0 2   0 0 0 10 |           
	//    0  3  0  0]  0 6 0 0] |    0 0 3 0]  0 0 8 0] |    3 3 3 0]  4 6 8 0]		|   0 0 0 3]  0 0 0 10]|               
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//               
	vector<vector<int>> row_flags(4, vector<int>(4, 30)), column_flags(4, vector<int>(4, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 8; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}
		for (int i = 4; i < 8; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i];
		}
		row_flags[3][2] = row_position[2] + 2;
		column_flags[3][2] = column_position[2];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 8; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + (i - 2) / 2;
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 8; i += 2)
		{
			row_flags[i / 2][3] = row_position[i];
			column_flags[i / 2][3] = column_position[i] + 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[1][i/2] = row_position[2];
			column_flags[1][i / 2] = column_position[2] - 4 + i;
		}
		row_flags[0][1] = row_position[0] ;
		column_flags[0][1] = column_position[0] - 2;

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/


			int column_first = column_position[0] - 4;

			field.delete_space(row_position, column_position);

			for (int i = 0; i < 8; i += 1)
			{
				row_position[i] = row_position[2];
			}
			for (int i = 0; i < 8; i++)
			{
				column_position[i] = column_first + i;
			}
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically  = false;
		}
	}


	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/


		for (int i = 0; i < 6; i += 2)
		{
			row_flags[3][i / 2] = row_position[i] + 1;
			column_flags[3][i / 2] = column_position[i];
		}
		for (int i = 4; i < 8; i += 2)
		{
			row_flags[1][i / 2] = row_position[i] - 1;
			column_flags[1][i / 2] = column_position[i];
		}
		row_flags[0][2] = row_position[4] - 2;
		column_flags[0][2] = column_position[4];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/

			field.delete_space(row_position, column_position);
			for (int i = 0; i < 8; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] - 1 + (i - 2) / 2;
				column_position[i] = column_position[4];
				column_position[i + 1] = column_position[4 + 1];
			}
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally= false;
		}
	}


	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 0; i < 6; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[i] - 2;
		}
		for (int i = 4; i < 8; i += 2)
		{
			row_flags[2][i / 2] = row_position[i];
			column_flags[2][i / 2] = column_position[i] - 2 + i;
		}
		row_flags[3][1]= row_position[6];
		column_flags[3][1]= column_position[6] + 2;

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);
			for (int i = 0; i < 8; i += 1)
			{
				row_position[i] = row_position[4];

			}
			for (int i = 0; i < 8; i++)
			{
				column_position[i] = column_first + i;
			}
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}

	return false;
}
void I_shape::hard_drop(playing_field& field)
{
	field.delete_space(row_position, column_position);
	int step = field.hard_drop_step(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i] += step;
	}
	field.change_field(row_position, column_position);
	field.print_field();
}
void I_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position);
}
I_shape::~I_shape() { /*cout << "\n\n I des\n\n";*/ }

T_shape::T_shape(playing_field& field)
{
	for (int i = 0; i < 6; i++)  //{1,1,1,1,1,1,0,0 }
		row_position[i] = 1;	 //{4,5,6,7,8,9,6,7 }
	row_position[6] = row_position[7] = 0;
	for (int i = 0; i < 6; i++)
		column_position[i] = i + 10;
	column_position[6] = 12;
	column_position[7] = 13;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool T_shape::action_down(playing_field& field)
{
	if (!field.valid_down(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i]++;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool T_shape::action_left(playing_field& field)
{
	if (!field.valid_left(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] -= 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool T_shape::action_right(playing_field& field)
{
	if (!field.valid_right(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] += 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool T_shape::rotate_right(playing_field& field) 
{
	//
	//        O [ ] O                   O [ ]					    O  O               O [ ] O                                                   
	//       [ ][X][ ]                 [ ][X] O					[ ][X][ ]              O [X][ ]                                                         
	//		  O  O                      O [ ] O					 O [ ] O                 [ ] O                                                 
	//
	//:0-0                         :1-0                   :1-1                       :0-1                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//        O [ ] O                     [ ] O 				     O  O                  O [ ] O                                                  
	//       [ ][X][ ]                  O [X][ ]					[ ][X][ ]             [ ][X] O                                                       
	//		     O  O                   O [ ] O					     O [ ] O               O [ ]                                                  
	//
	//:0-0                         :0-1                   :1-1                       :1-0                                     
	//------------------------------------------------------------------------------------------------------
	//	{1/1/1/1/1/1/0/0}		| {0/0/1/1/2/2/1/1}    |{1/1/1/1/1/1/2/2}		| {0/0/1/1/2/2/1/1}		| 
	//  {4/5/6/7/8/9/6/7}		| {6/7/6/7/6/7/8/9}    |{4/5/6/7/8/9/6/7}		| {6/7/6/7/6/7/4/5}		| 
	//							|					   |						|					    |
	//  {0,0,2,2}				| {0,1,2,2}			   |{0,0,2,2}				| {0,0,1,2}				|	
	//	{4,8,4,6}				| {4,8,4,8}			   |{6,8,4,8}				| {4,8,4,8}				|	
	//							|					   |						|					    |
	//  [O 0 O   [4 0 8 		|   [0 0 O   [0 0 8    |[ O  O  0    [4 6 0     |   [O 0 O   [4 0 8     |                            
	//   0 0 0    0 0 0 	  	|    1 0 0    4 0 0    |  0  0  0     0 0 0     |    0 0 1    0 0 8     |                    
	//   0 2 2 ]  0 4 6  ]    	|    2 0 2 ]  4 0 8 ]  |  2  0  2 ]   4 0 8]    |    2 0 0 ]  4 0 0 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      

	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i]-2;
		}
		for (int i = 0; i < 8; i += 4)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + (i - 2) / 2;
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			row_position[6] = row_position[7] = row_position[2];
			column_position[6] = column_position[2] + 2;
			column_position[6 + 1] = column_position[2 + 1] + 2;
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
	/*	cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 0; i < 8; i += 4)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[i] + 2;
		}
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[i] - 2;
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[2];
			}
			row_position[6] = row_position[7] = row_position[2] + 1;
			for (int i = 0; i < 6; i++)
			{
				column_position[i] = column_first + i;
			}
			column_position[6] = column_first + 2;
			column_position[7] = column_first + 2 + 1;

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
	/*	cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 0; i < 4; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}
		for (int i = 0; i < 8; i += 4)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i];
		}


		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + (i - 2) / 2;
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			row_position[6] = row_position[7] = row_position[2];
			column_position[6] = column_position[2] - 2;
			column_position[6 + 1] = column_position[2 + 1] - 2;

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}

	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 0; i < 8; i += 4)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[i] - 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[i] + 2;
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/


			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);

			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[2];
			}
			row_position[6] = row_position[7] = row_position[2] - 1;
			for (int i = 0; i < 6; i++)
			{
				column_position[i] = column_first + i;
			}
			column_position[6] = column_first + 2;
			column_position[7] = column_first + 2 + 1;

			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}


	return false;
}
bool T_shape::rotate_left(playing_field& field) 
{
	//
	//:rotate_horizontaly-rotate_verticaly			
	//
	//        O [ ] O                   O [ ]					    O  O               O [ ] O                                                   
	//       [ ][X][ ]                 [ ][X] O					[ ][X][ ]              O [X][ ]                                                         
	//		  O  O                      O [ ] O					 O [ ] O                 [ ] O                                                 
	//
	//:0-0                         :1-0                   :1-1                       :0-1                                     
	//------------------------------------------------------------------------------------------------------
	//	{1/1/1/1/1/1/0/0}		| {0/0/1/1/2/2/1/1}    |{1/1/1/1/1/1/2/2}		| {0/0/1/1/2/2/1/1}		| 
	//  {4/5/6/7/8/9/6/7}		| {6/7/6/7/6/7/4/5}    |{4/5/6/7/8/9/6/7}		| {6/7/6/7/6/7/8/9}		| 
	//							|					   |						|					    |
	//  {0,0,2,2}				| {0,1,2,2}			   |{0,0,2,2}				| {0,0,1,2}				|	
	//	{4,8,4,6}				| {4,8,4,8}			   |{6,8,4,8}				| {4,8,4,8}				|	
	//							|					   |						|					    |
	//  [O 0 O   [4 0 8 		|  [O 0 0   [4 0 0     |[ 0  O  O    [0 6 8     |   [O 0 O   [4 0 8     |                            
	//   0 0 0    0 0 0 	  	|   0 0 1    0 0 8     | 0  0  0     0 0 0      |    1 0 0    4 0 0     |                    
	//   2 2 0 ]  4 6 0 ]    	|   2 0 2 ]  4 0 8 ]   | 2  0  2 ]   4 0 8]     |    0 0 2 ]  0 0 8 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      

	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i];
		}
		for (int i = 0; i < 8; i += 4)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + (i - 2) / 2;
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			row_position[6] = row_position[7] = row_position[2];
			column_position[6] = column_position[2] - 2;
			column_position[6 + 1] = column_position[2 + 1] - 2;
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[i] + 2;
		}
		for (int i = 0; i < 8; i += 4)
		{
			row_flags[0][i / 2] = row_position[i];
			column_flags[0][i / 2] = column_position[i] - 2;
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

				/*cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[2];
			}
			row_position[6] = row_position[7] = row_position[2] + 1;
			for (int i = 0; i < 6; i++)
			{
				column_position[i] = column_first + i;
			}
			column_position[6] = column_first + 2;
			column_position[7] = column_first + 2 + 1;
				
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 2; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}
		for (int i = 0; i < 8; i += 4)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i];
		}
			

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/

			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + (i - 2) / 2;
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			row_position[6] = row_position[7] = row_position[2];
			column_position[6] = column_position[2] + 2;
			column_position[6 + 1] = column_position[2 + 1] + 2;
				
		/*	cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}

	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[i] - 2;
		}
		for (int i = 0; i < 8; i += 4)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[i] + 2;
		}
			
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/


			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);

			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[2];
			}
			row_position[6] = row_position[7] = row_position[2] - 1;
			for (int i = 0; i < 6; i++)
			{
				column_position[i] = column_first + i;
			}
			column_position[6] = column_first + 2;
			column_position[7] = column_first + 2 + 1;

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}


	return false;
}
void T_shape::hard_drop(playing_field& field)
{
	field.delete_space(row_position, column_position);
	int step = field.hard_drop_step(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i] += step;
	}
	field.change_field(row_position, column_position);
	field.print_field();
}
void T_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position);
}
T_shape::~T_shape() { /*cout << "\n\n T des\n\n";*/ }

L_shape::L_shape(playing_field& field)
{
	for (int i = 0; i < 2; i++) //{ 0,0,1,1,1,1,1,1 }
		row_position[i] = 0;	//{ 4,5,4,5,6,7,8,9 }
	for (int i = 2; i < 8; i++) 
		row_position[i] = 1;
	column_position[0] = 12;
	column_position[1] = 13;
	for (int i = 2; i < 8; i++)
		column_position[i] = i + 10;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool L_shape::action_down(playing_field& field)
{
	if (!field.valid_down(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i]++;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool L_shape::action_left(playing_field& field)
{
	if (!field.valid_left(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] -= 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool L_shape::action_right(playing_field& field)
{
	if (!field.valid_right(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] += 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool L_shape::rotate_right(playing_field& field) 

{
	//
	//       [ ] O  O                     [ ][ ]				 O  O                  O [ ] O                                                   
	//       [ ][X][ ]					O [X] O					[ ][X][ ]              O [X] O                                                       
	//		     O  O                   O [ ] O					 O  O [ ]             [ ][ ]                                                  
	//
	//:0-0                         :0-1                   :1-1                       :1-0                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//       [ ] O  O                   O [ ]						O  O               O [ ][ ]                                                    
	//       [ ][X][ ]					O [X] O					[ ][X][ ]              O [X] O                                                       
	//		  O  O                     [ ][ ] O					 O  O [ ]                [ ] O                                                
	//
	//:0-0                         :1-0                   :1-1                       :0-1                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/1/1/1/1/1/1}		| {0/0/0/0/1/1/2/2}    |{1/1/1/1/1/1/2/2}		| {0/0/1/1/2/2/2/2}		| 
	//  {4/5/4/5/6/7/8/9}		| {6/7/8/9/6/7/6/7}    |{4/5/6/7/8/9/8/9}		| {6/7/6/7/4/5/6/7}		| 
	//							|					   |						|					    |
	//  {0,0,2,2}				| {0,1,2,2}			   |{0,0,2,2}				| {0,0,1,2}				|	
	//	{4,8,4,6}				| {4,8,4,8}			   |{6,8,4,8}				| {4,8,4,8}				|	
	//							|					   |						|					    |
	//  [0 O O   [0 6 8 		|   [0 0 0   [0 0 0    |[ O  O  0    [4 6 0     |   [O 0 O   [4 0 8     |                            
	//   0 0 0    0 0 0 	  	|    1 0 1    4 0 8    |  0  0  0     0 0 0     |    1 0 1    4 0 8     |                    
	//   0 2 2 ]  0 6 8  ]    	|    2 0 2 ]  4 0 8 ]  |  2  2  0 ]   4 6 0]    |    0 0 0 ]  0 0 0 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      

	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[2][i / 2] = column_flags[0][i / 2] = column_position[i] + 2;
		}
		

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i-4] =  row_position[i] - 1;
				column_position[i-4] = column_position[i];
			}
			row_position[6] = row_position[7] = row_position[6] + 1;
			column_position[6] = column_position[6] - 2;
			column_position[6 + 1] = column_position[6 + 1] - 2;

			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][2] = row_position[i] + 1;
			column_flags[i / 2][2] = column_position[0] + 2;
			row_flags[i / 2][0] = row_position[i] + 1;
			column_flags[i / 2][0] = column_position[0] - 2;
		}
		

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[4];
				column_position[i] = column_first + i;

			}
			row_position[6] = row_position[7] = row_position[4] + 1;
			column_position[6] = column_position[4];
			column_position[7] = column_position[5];

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			for (int i = 0; i < 4; i += 2)
			{
				row_flags[2][i / 2] = row_position[i] + 1;
				row_flags[0][i / 2] = row_position[i] - 1;
				column_flags[2][i / 2] = column_flags[0][i / 2] = column_position[i];
			}
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 4; i += 1)
			{
				row_position[i+4] =row_position[i] + 1;
				column_position[i+4] = column_position[i];
			}
			row_position[0] = row_position[1] = row_position[2]-1;
			column_position[0] = column_position[2];
			column_position[0 + 1] = column_position[2 + 1];

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}

	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[0] + 2;
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[0] - 2;
		}
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/


			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);

			for (int i = 2; i < 8; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i - 2;
			}
			
			column_position[0] = column_position[2];
			column_position[1] = column_position[3];

			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}

	return false;
}
bool L_shape::rotate_left(playing_field& field) 
{
	//
	//       [ ] O  O                     [ ][ ]				 O  O                  O [ ] O                                                   
	//       [ ][X][ ]					O [X] O					[ ][X][ ]              O [X] O                                                       
	//		     O  O                   O [ ] O					 O  O [ ]             [ ][ ]                                                  
	//
	//:0-0                         :0-1                   :1-1                       :1-0                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//       [ ] O  O                   O [ ]						O  O               O [ ][ ]                                                    
	//       [ ][X][ ]					O [X] O					[ ][X][ ]              O [X] O                                                       
	//		  O  O                     [ ][ ] O					 O  O [ ]                [ ] O                                                
	//
	//:0-0                         :1-0                   :1-1                       :0-1                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/1/1/1/1/1/1}		| {0/0/1/1/2/2/2/2}    |{1/1/1/1/1/1/2/2}		| {0/0/0/0/1/1/2/2}		| 
	//  {4/5/4/5/6/7/8/9}		| {6/7/6/7/4/5/6/7}    |{4/5/6/7/8/9/8/9}		| {6/7/8/9/6/7/6/7}		| 
	//							|					   |						|					    |
	//  {0,0,2,2}				| {0,1,2,2}			   |{0,0,2,2}				| {0,0,1,2}				|	
	//	{4,8,4,6}				| {4,8,4,8}			   |{6,8,4,8}				| {4,8,4,8}				|	
	//							|					   |						|					    |
	//  [0 O O   [0 6 8 		|   [0 0 0   [4 0 0    |[ 0  O  O    [0 6 8     |   [O 0 0   [4 0 0     |                            
	//   0 0 0    0 0 0 	  	|    1 0 1    4 0 8    |  0  0  0     0 0 0     |    1 0 1    4 0 8     |                    
	//   2 2 0]   4 6 0  ]    	|    0 0 2 ]  0 0 8 ]  |  2  2  0 ]   4 6 0]    |    0 0 2 ]  0 0 8 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      

	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] =  column_position[i] + 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[2][i / 2] = row_position[2] + 1;
			column_flags[2][i / 2] = column_position[i];
		}


		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[i] + 1;
				column_position[i] = column_position[i] - 2;
			}
			for (int i = 0; i < 4; i += 1)
			{
				column_position[i] = column_position[i] + 2;
			}

			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[0] + 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[0] - 2;
		}
		
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/


			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i;

			}
			column_position[6] = column_position[4];
			column_position[7] = column_position[5];

			

			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}

	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] =column_position[i];
		}
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 4; i += 1)
			{
				row_position[i ] = row_position[i] - 1;
				column_position[i] = column_position[i] + 2;
			}
			for (int i = 4; i < 8; i += 1)
			{
				column_position[i] = column_position[i] - 2;
			}
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;

		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
	/*	cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][2] = row_position[i] + 1;
			column_flags[i / 2][2] = column_position[0] + 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][0] = row_position[i] - i / 2;
			column_flags[i / 2][0] = column_position[0] - 2;
		}


		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);
			for (int i = 2; i < 8; i += 1)
			{
				row_position[i] = row_position[4];
				column_position[i] = column_first + i - 2;
			}

			column_position[0] = column_position[2];
			column_position[1] = column_position[3];

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;

		}
	}


	return false;
}
void L_shape::hard_drop(playing_field& field)
{
	field.delete_space(row_position, column_position);
	int step = field.hard_drop_step(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i] += step;
	}
	field.change_field(row_position, column_position);
	field.print_field();
}
void L_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position);
}
L_shape::~L_shape() { /*cout << "\n\n L des\n\n";*/ }

J_shape::J_shape(playing_field& field)
{
	for (int i = 2; i < 8; i++) //{ 0,0,1,1,1,1,1,1}
		row_position[i] = 1;	//{ 8,9,4,5,6,7,8,9}
	for (int i = 0; i < 2; i++)
		row_position[i] = 0;
	column_position[0] = 14;
	column_position[1] = 15;
	for (int i = 2; i < 8; i++)
		column_position[i] = i + 8;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool J_shape::action_down(playing_field& field)
{
	if (!field.valid_down(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i]++;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool J_shape::action_left(playing_field& field)
{
	if (!field.valid_left(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] -= 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool J_shape::action_right(playing_field& field)
{
	if (!field.valid_right(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] += 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool J_shape::rotate_right(playing_field& field)

{
	//
	//        O  O [ ]                 [ ][ ]						O  O               O [ ] O                                                   
	//       [ ][X][ ]					O [X] O					[ ][X][ ]              O [X] O                                                       
	//		  O  O                      O [ ] O					[ ] O  O				 [ ][ ]                                                  
	//
	//:0-0                         :1-0                   :1-1                       :0-1                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//        O  O [ ]                 [ ] O					O  O			      [ ][ ] O                                                  
	//       [ ][X][ ]				 O [X] O					[ ][X][ ]              O [X] O                                                       
	//		     O  O                O [ ][ ]   				[ ] O  O               O [ ]                                                
	//
	//:0-0                         :0-1                   :1-1                       :1-0                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/1/1/1/1/1/1}		| {0/0/1/1/2/2/2/2}    |{1/1/1/1/1/1/2/2}		| {0/0/0/0/1/1/2/2}		| 
	//  {8/9/4/5/6/7/8/9}		| {6/7/6/7/6/7/8/9}    |{4/5/6/7/8/9/4/5}		| {4/5/6/7/6/7/6/7}		| 
	//							|					   |						|					    |
	//  {0,0,2,2}				| {0,1,2,2}			   |{0,0,2,2}				| {0,0,1,2}				|	
	//	{4,8,4,6}				| {4,8,4,8}			   |{6,8,4,8}				| {4,8,4,8}				|	
	//							|					   |						|					    |
	//  [O O 0   [4 6 0 		|   [0 0 O   [0 0 8    |[ O  O  0    [4 6 0     |   [0 0 O   [0 0 8     |                            
	//   0 0 0    0 0 0 	  	|    1 0 1    4 0 8    |  0  0  0     0 0 0     |    1 0 1    4 0 8     |                    
	//   0 2 2 ]  0 6 8  ]    	|    2 0 0 ]  4 0 0 ]  |  0  2  2 ]   0 6 8]    |    2 0 0 ]  4 0 0 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      

	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] =  column_position[i] + 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[0][i / 2] = row_position[0];
			column_flags[0][i / 2] = column_position[i + 2];
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i ] = row_position[i] + 1;
			}
			for (int i = 0; i < 4; i += 2)
			{
				column_position[i] = column_position[4];
				column_position[i + 1] = column_position[4 + 1];
			}
	
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[0] - 2;
		}
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[0] + 2;
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i;

			}
			column_position[6] = column_position[0];
			column_position[7] = column_position[1];

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i];
		}
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 4; i += 1)
			{
				row_position[i] = row_position[i] - 1;
				column_position[i + 4] = column_position[2 + i];
			}
			

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}

	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][2] = row_position[i + 2];
			column_flags[i / 2][2] = column_position[2] + 2;
		}
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][0] = row_position[i] + 1;
			column_flags[i / 2][0] = column_position[0];
		}
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/


			int column_first = column_position[0];

			field.delete_space(row_position, column_position);

			for (int i = 2; i < 8; i += 1)
			{
				row_position[i] = row_position[4];
				column_position[i] = column_first + i - 2;
			}

			column_position[0] = column_position[6];
			column_position[1] = column_position[7];

			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}

	return false;
}
bool J_shape::rotate_left(playing_field& field)
{
	//
	//        O  O [ ]                 [ ][ ]						O  O               O [ ] O                                                   
	//       [ ][X][ ]					O [X] O					[ ][X][ ]              O [X] O                                                       
	//		  O  O                      O [ ] O					[ ] O  O				 [ ][ ]                                                  
	//
	//:0-0                         :1-0                   :1-1                       :0-1                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//        O  O [ ]                 [ ] O					O  O			      [ ][ ] O                                                  
	//       [ ][X][ ]				 O [X] O					[ ][X][ ]              O [X] O                                                       
	//		     O  O                O [ ][ ]   				[ ] O  O               O [ ]                                                
	//
	//:0-0                         :0-1                   :1-1                       :1-0                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/1/1/1/1/1/1}		| {0/0/0/0/1/1/2/2}    |{1/1/1/1/1/1/2/2}		| {0/0/1/1/2/2/2/2}		| 
	//  {8/9/4/5/6/7/8/9}		| {4/5/6/7/6/7/6/7}    |{4/5/6/7/8/9/4/5}		| {6/7/6/7/6/7/8/9}		| 
	//							|					   |						|					    |
	//  [O O 0   [4 6 0 		|   [0 0 0   [0 0 0    |[ 0  O  O    [0 6 8     |   [O 0 O   [4 0 8     |                            
	//   0 0 0    0 0 0 	  	|    1 0 1    4 0 8    |  0  0  0     0 0 0     |    1 0 1    4 0 8     |                    
	//   2 2 0]   4 6 0  ]    	|    2 0 2 ]  4 0 8 ]  |  0  2  2 ]   0 6 8]    |    0 0 0 ]  0 0 0 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      


	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	
	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[2][i / 2] = row_position[2] + 1;
			column_flags[2][i / 2] = column_position[i + 2];
			row_flags[0][i / 2] = row_position[0];
			column_flags[0][i / 2] = column_position[i + 2];
		}


		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);

			for (int i = 2; i < 8; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[0] + (i - 2) / 2;
				column_position[i] = column_position[4];
				column_position[i + 1] = column_position[5];
			}
			column_position[0] = column_position[4] - 2;
			column_position[0 + 1] = column_position[5] - 2;
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;

		}
	}
	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][2] = row_position[i] + 1;
			column_flags[i / 2][2] = column_position[i] + 2;
			row_flags[i / 2][0] = row_position[i] + 1;
			column_flags[i / 2][0] = column_position[i] - 2;
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/


			int column_first = column_position[0] ;

			field.delete_space(row_position, column_position);
		

			for (int i = 0; i < 6; i += 1)
			{
				row_position[i] = row_position[4];
				column_position[i] = column_first + i;
			}

			column_position[6] = column_position[0];
			column_position[7] = column_position[1];


			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
			row_flags[2][i / 2] = row_position[i] + 1;
			column_flags[2][i / 2] = column_position[i];
		}
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 2)
			{
				row_position[i] = row_position[i + 1] = row_position[2] - 1 + i / 2;
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			column_position[6] = column_position[2] + 2;
			column_position[6 + 1] = column_position[2 + 1] + 2;
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
	/*	cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[0] - 2;
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[0] + 2;
		}

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] -2;

			field.delete_space(row_position, column_position);
			for (int i = 2; i < 8; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i - 2;

			}
			column_position[0] = column_position[6];
			column_position[1] = column_position[7];


			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}


	return false;
}
void J_shape::hard_drop(playing_field& field)
{
	field.delete_space(row_position, column_position);
	int step = field.hard_drop_step(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i] += step;
	}
	field.change_field(row_position, column_position);
	field.print_field();
}
void J_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position);
}
J_shape::~J_shape() { /*cout << "\n\n J des\n\n";*/ }

O_shape::O_shape(playing_field& field)
{
	for (int i = 0; i < 4; i++) //{0,0,0,0,1,1,1,1}
		row_position[i] = 0;	//{4,5,6,7,4,5,6,7}
	for (int i = 4; i < 8; i++)
		row_position[i] = 1;
	for (int i = 0; i < 4; i++)
		column_position[i] = i + 12;
	for (int i = 0; i < 4; i++)
		column_position[i+4] = i + 12;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool O_shape::action_down(playing_field& field)
{
	if (!field.valid_down(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i]++;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool O_shape::action_left(playing_field& field)
{
	if (!field.valid_left(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] -= 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool O_shape::action_right(playing_field& field)
{
	if (!field.valid_right(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] += 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool O_shape::rotate_right(playing_field& field) { return true; }
bool O_shape::rotate_left(playing_field& field){ return true; }
void O_shape::hard_drop(playing_field& field)
{
	field.delete_space(row_position, column_position);
	int step = field.hard_drop_step(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i] += step;
	}
	field.change_field(row_position, column_position);
	field.print_field();
}
void O_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position);
}
O_shape::~O_shape() {/* cout << "\n\n O des\n\n";*/ }

Z_shape::Z_shape(playing_field& field)
{
	for (int i = 0; i < 4; i++) //{0,0,0,0,1,1,1,1}
		row_position[i] = 0;	//{4,5,6,7,6,7,8,9}
	for (int i = 4; i < 8; i++)
		row_position[i] = 1;
	for (int i = 0; i < 4; i++)
		column_position[i] = i + 10;
	for (int i = 0; i < 4; i++)
		column_position[i + 4] = i + 12;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool Z_shape::action_down(playing_field& field)
{
	if (!field.valid_down(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i]++;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool Z_shape::action_left(playing_field& field)
{
	if (!field.valid_left(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] -= 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool Z_shape::action_right(playing_field& field)
{
	if (!field.valid_right(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] += 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool Z_shape::rotate_right(playing_field& field)

{ 
	//                                                                                                   
	//      [ ][ ] O                     O [ ]                         O                 O  O [ ]                               
	//       O [X][ ]                   [ ][X]                  [ ][X] O                   [X][ ]                              
	//       O                          [ ] O  O                 O [ ][ ]                  [ ] O                    
	//                                                                                                   
	//:0-0                         :1-0                   :1-1                       :0-1                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//      [ ][ ] O                      [ ]                 O  O                     O [ ] O                                
	//         [X][ ]                O [X][ ]                [ ][X]                   [ ][X] O                               
	//          O  O                 O [ ] O                  O [ ][ ]                [ ]                             
	//
	//:0-0                         :0-1                   :1-1                       :1-0                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/0/0/1/1/1/1}		| {0/0/1/1/1/1/2/2}    |{1/1/1/1/2/2/2/2}		| {0/0/1/1/1/1/2/2}		| 
	//  {4/5/6/7/6/7/8/9}		| {8/9/6/7/8/9/6/7}    |{4/5/6/7/6/7/8/9}		| {6/7/4/5/6/7/4/5}		|
	//							|					   |						|					    |
	//  [0 0 O   [0 0 8 		|   [0 0 0   [0 0 0    |[ O  O  0    [4 6 0     |   [O 0 O   [4 0 8     |                            
	//   0 0 0    0 0 0 	  	|    1 0 0    4 0 0    |  0  0  0     0 0 0     |    0 0 1    0 0 8     |                    
	//   0 2 2 ]  0 6 8  ]    	|    2 0 2 ]  4 0 8 ]  |  2  0  0 ]   4 0 0]    |    0 0 0 ]  0 0 0 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      

	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[2][i / 2] = row_position[4] + 1;
			column_flags[2][i / 2] = column_position[i] + i - 2;
		}
		row_flags[0][2] = row_position[0];
		column_flags[0][2] = column_position[6];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 2; i < 8; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + 1;
			}
			for (int i = 0; i < 6; i += 4)
			{
				column_position[i] = column_position[6];
				column_position[i + 1] = column_position[6 + 1];
			}
			column_position[6] -= 2;
			column_position[6 + 1] -= 2;
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/

		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][0] = row_position[i + 2];
			column_flags[i / 2][0] = column_position[2] - 2;
		}
		row_flags[2][2] = row_position[6];
		column_flags[2][2] = column_position[0];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{

			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[2] - 2;

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 4; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i;

			}
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[0] + 1;
				column_position[i] = column_first + i - 2;

			}

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}
		row_flags[2][0] = row_position[4] ;
		column_flags[2][0] = column_position[0];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] - 1;
			}
			for (int i = 2; i < 8; i += 4)
			{
				column_position[i] = column_position[0];
				column_position[i + 1] = column_position[0 + 1];
			}
			column_position[0] += 2;
			column_position[0 + 1] += 2;
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}
	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][2] = row_position[i];
			column_flags[i / 2][2] = column_position[0] + 2;
		}
		
		row_flags[0][0] = row_position[0];
		column_flags[0][0] = column_position[2];
		
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/


			int column_first = column_position[0]-2;

			field.delete_space(row_position, column_position);

			for (int i =0; i < 4; i += 1)
			{
				row_position[i] = row_position[0];
				column_position[i] = column_first + i;
			}

			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[0]+1;
				column_position[i] = column_first + i - 2;
			}
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}

	return false;
}
bool Z_shape::rotate_left(playing_field& field)
{
	//                                                                                                   
	//      [ ][ ] O                     O [ ]                         O                 O  O [ ]                               
	//       O [X][ ]                   [ ][X]                  [ ][X] O                   [X][ ]                              
	//       O                          [ ] O  O                 O [ ][ ]                  [ ] O                    
	//                                                                                                   
	//:0-0                         :1-0                   :1-1                       :0-1                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//      [ ][ ] O                      [ ]                 O  O                     O [ ] O                                
	//         [X][ ]                O [X][ ]                [ ][X]                   [ ][X] O                               
	//          O  O                 O [ ] O                  O [ ][ ]                [ ]                             
	//
	//:0-0                         :0-1                   :1-1                       :1-0                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/0/0/1/1/1/1}		| {0/0/1/1/1/1/2/2}    |{1/1/1/1/2/2/2/2}		| {0/0/1/1/1/1/2/2}		| 
	//  {4/5/6/7/6/7/8/9}		| {6/7/4/5/6/7/4/5}    |{4/5/6/7/6/7/8/9}		| {8/9/6/7/8/9/6/7}		|
	//							|					   |						|					    |
	//  [0 0 O   [0 0 8 		|   [O 0 0   [4 0 0    |[ 0  0  O    [0 0 8     |   [O O 0   [4 6 0     |                            
	//   1 0 0    4 0 0 	  	|    0 0 0    0 0 0    |  0  0  1     0 0 8     |    0 0 0    0 0 0     |                    
	//   2 0 0 ]  4 0 0  ]    	|    0 2 2 ]  0 6 8 ]  |  2  0  0 ]   4 0 0]    |    0 0 2 ]  0 0 8 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      



	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));


	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][0] = row_position[i]+1;
			column_flags[i / 2][0] = column_position[i] - 2;
		}
		row_flags[0][2] = row_position[0];
		column_flags[0][2] = column_position[6];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);

			for (int i = 2; i < 8; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + 1;
				column_position[i] = column_position[0];
				column_position[i + 1] = column_position[0 + 1];
			}
			column_position[0] += 2;
			column_position[1] += 2;
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;

		}
	}
	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] + 1;
			column_flags[0][i / 2] = column_position[i] + 2;
		}
		row_flags[0][0] = row_position[0];
		column_flags[0][0] = column_position[2];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/


			int column_first = column_position[0]-2;

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 4; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i;
			}
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[2] + 1;
				column_position[i] = column_first + i - 2;
			}
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][2] = row_position[i + 2] - 1; 
			column_flags[i / 2][2] = column_position[6]; 
		}
		row_flags[2][0] = row_position[4];
		column_flags[2][0] = column_position[0];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] - 1;
				column_position[i] = column_position[6];
				column_position[i + 1] = column_position[6 + 1];
			}
			column_position[6] -= 2;
			column_position[6 + 1] -= 2;
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[0][i / 2] = row_position[0];
			column_flags[0][i / 2] = column_position[2] - 2 + i;
		}
		row_flags[ 2][2] = row_position[6];
		column_flags[ 2][2] = column_position[0];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[2] - 2;

			field.delete_space(row_position, column_position);
			for (int i = 0; i < 4; i += 1)
			{
				row_position[i] = row_position[0];
				column_position[i] = column_first + i;
			}
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[0] + 1;
				column_position[i] = column_first + i - 2;;
			}

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}


	return false;
}
void Z_shape::hard_drop(playing_field& field)
{
	field.delete_space(row_position, column_position);
	int step = field.hard_drop_step(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i] += step;
	}
	field.change_field(row_position, column_position);
	field.print_field();
}
void Z_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position);
}
Z_shape::~Z_shape() { /*cout << "\n\n Z des\n\n";*/ }

S_shape::S_shape(playing_field& field)
{
	for (int i = 4; i < 8; i++) //{0,0,0,0,1,1,1,1}
		row_position[i] = 1;	//{6,7,8,9,4,5,6,7}
	for (int i = 0; i < 4; i++)
		row_position[i] = 0;
	for (int i = 0; i < 4; i++)
		column_position[i + 4] = i + 10;
	for (int i = 0; i < 4; i++)
		column_position[i] = i + 12;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool S_shape::action_down(playing_field& field)
{
	if (!field.valid_down(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i]++;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool S_shape::action_left(playing_field& field)
{
	if (!field.valid_left(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] -= 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool S_shape::action_right(playing_field& field)
{
	if (!field.valid_right(row_position, column_position)) return false;
	field.delete_space(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		column_position[i] += 2;
	}
	field.change_field(row_position, column_position);
	field.print_field();
	return true;
}
bool S_shape::rotate_right(playing_field& field)

{
	//                                                                                                   
	//          O [ ][ ]                   [ ]                         O  O                 O [ ] O                             
	//         [ ][X]                      [ ][X] O                   [X][ ]                O [X][ ]                              
	//          O  O                        O [ ] O                [ ][ ] O                      [ ]                     
	//                                                                                                   
	//:0-0                         :1-0                   :1-1                       :0-1                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//          O [ ][ ]                    [ ] O                   O                         [ ] O  O                         
	//         [ ][X] O                     [X][ ]                  O [X][ ]                  [ ][X]                              
	//                O                   O  O [ ]                 [ ][ ] O                    O [ ]                     
	//
	//:0-0                         :0-1                   :1-1                       :1-0                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/0/0/1/1/1/1}		| {0/0/1/1/1/1/2/2}    |{1/1/1/1/2/2/2/2}		| {0/0/1/1/1/1/2/2}		| 
	//  {6/7/8/9/4/5/6/7}		| {6/7/6/7/8/9/8/9}    |{6/7/8/9/4/5/6/7}		| {4/5/4/5/6/7/6/7}		|
	//							|					   |						|					    |
	//  [O 0 0   [4 0 0 		|   [0 0 O   [0 0 8    |[ O  0  0    [4 0 0     |   [0 O O   [0 6 8     |                            
	//   0 0 1    0 0 8 	  	|    0 0 0    0 0 0    |  1  0  0     4 0 0     |    0 0 0    0 0 0     |                    
	//   0 0 2 ]  0 0 8  ]    	|    2 2 0 ]  4 6 0 ]  |  0  0  2 ]   0 0 8]    |    2 0 0 ]  4 0 0 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      

	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));

	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][2] = row_position[i] + 1;
			column_flags[i / 2][2] = column_position[2];
		}
		row_flags[0][0] = row_position[0];
		column_flags[0][0] = column_position[4];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);
			for (int i = 2; i < 8; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + 1;
			}
			for (int i = 4; i < 8; i += 2)
			{
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			column_position[2] -= 2;
			column_position[2 + 1] -= 2;
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[2][i / 2] = row_position[6];
			column_flags[2][i / 2] = column_position[i + 2] - 2;
		}
		row_flags[0][2] = row_position[0];
		column_flags[0][2] = column_position[4];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] - 2;

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 4; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i + 2;

			}
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[2] + 1;
				column_position[i] = column_first + i - 4;

			}

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][0] = row_position[i + 2] - 1;
			column_flags[i / 2][0] = column_position[4];
		}
		row_flags[2][2] = row_position[4];
		column_flags[2][2] = column_position[2];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] - 1;
			}
			for (int i = 0; i < 4; i += 2)
			{
				column_position[i] = column_position[4];
				column_position[i + 1] = column_position[4 + 1];
			}
			column_position[4] += 2;
			column_position[4 + 1] += 2;
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}
	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i] + 2;
		}

		row_flags[0][2] = row_position[6];
		column_flags[0][2] = column_position[0];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/

			int column_first = column_position[0] + 2;

			field.delete_space(row_position, column_position);

			for (int i = 2; i < 8; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] - 1;
			}
			for (int i = 0; i < 4; i += 1)
			{
				column_position[i] = column_first + i;
			}
			column_position[4] -= 2;
			column_position[5] -= 2;

			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}

	return false;
}
bool S_shape::rotate_left(playing_field& field)
{
	//                                                                                                   
	//          O [ ][ ]                [ ]                            O  O					  O [ ] O                             
	//         [ ][X]                   [ ][X] O                      [X][ ]		   		  O [X][ ]                              
	//          O  O                     O [ ] O                   [ ][ ] O					       [ ]                     
	//                                                                                                   
	//:0-0                         :1-0                   :1-1                       :0-1                       
	//:rotate_horizontaly-rotate_verticaly			
	//
	//          O [ ][ ]                    [ ] O                   O                         [ ] O  O                         
	//         [ ][X] O                     [X][ ]                  O [X][ ]                  [ ][X]                              
	//                O                   O  O [ ]                 [ ][ ] O                    O [ ]                     
	//
	//:0-0                         :0-1                   :1-1                       :1-0                                     
	//------------------------------------------------------------------------------------------------------
	//	{0/0/0/0/1/1/1/1}		| {0/0/1/1/1/1/2/2}    |{1/1/1/1/2/2/2/2}		| {0/0/1/1/1/1/2/2}		| 
	//  {6/7/8/9/4/5/6/7}		| {4/5/4/5/6/7/6/7}    |{6/7/8/9/4/5/6/7}		| {6/7/6/7/8/9/8/9}		|
	//							|					   |						|					    |
	//  [O 0 0   [4 0 0 		|   [0 0 0   [0 0 0    |[ 0  O  O    [0 6 8     |   [O 0 O   [4 0 8     |                            
	//   0 0 0    0 0 0 	  	|    0 0 1    0 0 8    |  0  0  0     0 0 0     |    1 0 0    4 0 0     |                    
	//   2 2 0 ]  4 6 0  ]    	|    2 0 2 ]  4 0 8 ]  |  0  0  2 ]   0 0 8]    |    0 0 0 ]  0 0 0 ]   |                   
	//		O-flagner te vortex blok linelu depqum chi pttvi		
	//      



	vector<vector<int>> row_flags(3, vector<int>(3, 30)), column_flags(3, vector<int>(3, 30));


	if (!rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout  << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl<<endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[2][i / 2] = row_position[4] + 1;
			column_flags[2][i / 2] = column_position[i + 4] - 2;
		}
		row_flags[0][0] = row_position[0];
		column_flags[0][0] = column_position[4];

		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;*/
			field.delete_space(row_position, column_position);

			for (int i = 2; i < 8; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] + 1;
			}
			for (int i = 0; i < 4; i += 2)
			{
				column_position[i] = column_position[4];
				column_position[i + 1] = column_position[4 + 1];
			}
			column_position[4] += 2;
			column_position[5] += 2;
			/*	cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "*#*";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = true;

		}
	}
	else if (rotate_Horizontally && !rotate_Vertically)
	{
		/*cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << row_position[i] << ' ';
		}
		cout << endl;
		cout << "#*#";
		for (int i = 0; i < 8; i += 1)
		{
			cout << column_position[i] << ' ';
		}
		cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[i / 2][2] = row_position[i + 2];
			column_flags[i / 2][2] = column_position[4] + 2;
		}
		row_flags[2][0] = row_position[6];
		column_flags[2][0] = column_position[0] - 2;
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*	cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << row_position[i] << ' ';
				}
				cout << endl;
				cout << "#*#";
				for (int i = 0; i < 8; i += 1)
				{
					cout << column_position[i] << ' ';
				}
				cout << endl << endl;*/


			int column_first = column_position[0];

			field.delete_space(row_position, column_position);


			for (int i = 0; i < 4; i += 1)
			{
				row_position[i] = row_position[2];
				column_position[i] = column_first + i + 2;
			}
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[2] + 1;
				column_position[i] = column_first + i - 4;
			}
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << row_position[i] << ' ';
			//}
			//cout << endl;
			//cout << "*#*";
			//for (int i = 0; i < 8; i += 1)
			//{
			//	cout << column_position[i] << ' ';
			//}
			//cout << endl;
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = true;
		}
	}
	else if (rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 2; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[0] - 1;
			column_flags[0][i / 2] = column_position[i - 2];
		}
		row_flags[2][2] = row_position[4];
		column_flags[2][2] = column_position[2];
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl;
			*/
			field.delete_space(row_position, column_position);
			for (int i = 0; i < 6; i += 4)
			{
				row_position[i] = row_position[i + 1] = row_position[i] - 1;
			}
			for (int i = 4; i < 8; i += 2)
			{
				column_position[i] = column_position[2];
				column_position[i + 1] = column_position[2 + 1];
			}
			column_position[2] -= 2;
			column_position[2 + 1] -= 2;
			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Horizontally = false;
		}
	}
	else if (!rotate_Horizontally && rotate_Vertically)
	{
		/*	cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
		for (int i = 0; i < 4; i += 2)
		{
			row_flags[i / 2][0] = row_position[i];
			column_flags[i / 2][0] = column_position[i] - 2;
		}
		row_flags[0][2] = row_position[0];
		column_flags[0][2] = column_position[0] +4;
		if (field.valid_rotate(row_flags, column_flags, rotate_Horizontally, rotate_Vertically))
		{
			/*cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "#*#";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl << endl << rotate_Horizontally << " ^^ " << rotate_Vertically << endl << endl;*/
			int column_first = column_position[0] -2;

			field.delete_space(row_position, column_position);
			for (int i = 0; i < 4; i += 1)
			{
				row_position[i] = row_position[0];
				column_position[i] = column_first + i + 2;
			}
			for (int i = 4; i < 8; i += 1)
			{
				row_position[i] = row_position[0] + 1;
				column_position[i] = column_first + i - 4;;
			}

			/*cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << row_position[i] << ' ';
			}
			cout << endl;
			cout << "*#*";
			for (int i = 0; i < 8; i += 1)
			{
				cout << column_position[i] << ' ';
			}
			cout << endl;*/
			field.change_field(row_position, column_position);
			field.print_field();
			rotate_Vertically = false;
		}
	}


	return false;
}
void S_shape::hard_drop(playing_field& field)
{
	field.delete_space(row_position, column_position);
	int step = field.hard_drop_step(row_position, column_position);
	for (int i = 0; i < 8; i++)
	{
		row_position[i] += step;
	}
	field.change_field(row_position, column_position);
	field.print_field();
}
void S_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position);
}
S_shape::~S_shape() { /*cout << "\n\n S des\n\n";*/ }

