#include "J_shape.h"

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
			column_flags[2][i / 2] = column_position[i] + 2;
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
				row_position[i] = row_position[i] + 1;
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


			int column_first = column_position[0];

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
			int column_first = column_position[0] - 2;

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
void J_shape::reserve(playing_field& field)
{
	int first_row, first_column;
	//	cout << endl << rotate_Horizontally << "\t" << rotate_Vertically << endl;
	if (rotate_Horizontally && rotate_Vertically)
		first_row = 2, first_column = 6;
	else if ((!rotate_Horizontally && rotate_Vertically) || (rotate_Horizontally && !rotate_Vertically))
		first_row = 2, first_column = 7;
	else if (!rotate_Horizontally && !rotate_Vertically)
		first_row = 2, first_column = 10;


	field.change_reserve(row_position, column_position, first_row, first_column);
}
J_shape::~J_shape() {}