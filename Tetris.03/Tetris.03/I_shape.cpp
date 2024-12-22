#include "I_shape.h"

I_shape::I_shape(playing_field& field)
{
	for (int i = 0; i < 8; i++)
		row_position[i] = 0;
	for (int i = 0; i < 8; i++)
		column_position[i] = i + 10;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
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
		for (int i = 0; i < 6; i += 2)
		{
			row_flags[0][i / 2] = row_position[i] - 1;
			column_flags[0][i / 2] = column_position[i];
		}
		for (int i = 4; i < 8; i += 2)
		{
			row_flags[2][i / 2] = row_position[i] + 1;
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
			column_flags[i / 2][3] = column_position[i] + 2;
		}
		for (int i = 4; i < 8; i += 2)
		{
			row_flags[2][i % 4 / 2] = row_position[4];
			column_flags[2][i % 4 / 2] = column_position[4] - (2 * (i / 2 - i % 4));
		}
		row_flags[3][1] = row_position[6];
		column_flags[3][1] = column_position[4] - 2;

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
			row_flags[1][i / 2] = row_position[2];
			column_flags[1][i / 2] = column_position[2] - 4 + i;
		}
		row_flags[0][1] = row_position[0];
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
			rotate_Vertically = false;
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
			rotate_Horizontally = false;
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
		row_flags[3][1] = row_position[6];
		column_flags[3][1] = column_position[6] + 2;

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
void I_shape::reserve(playing_field& field)
{
	int first_row, first_column;
	if ((rotate_Horizontally && rotate_Vertically) || (!rotate_Horizontally && !rotate_Vertically))
		first_row = 2, first_column = 5;
	else if ((!rotate_Horizontally && rotate_Vertically) || (rotate_Horizontally && !rotate_Vertically))
		first_row = 1, first_column = 8;
	field.change_reserve(row_position, column_position, first_row, first_column);
}
I_shape::~I_shape() {}
