#pragma once
#include <iostream>
#include<vector>
using namespace std;
class playing_field;



class blocks
{
private:

public:

	//blocks* start(blocks* ptr, playing_field& x); 
	virtual bool action_down(playing_field& field) =0;
	virtual bool action_left(playing_field& field) = 0;
	virtual bool action_right(playing_field& field) = 0;
	virtual bool rotate_right(playing_field& field) = 0;
	virtual bool rotate_left(playing_field& field) = 0;		/*shapery jarangen blocks-ic unenan funkcianer iranc specifik vor nuyn kod@ 7 angam chgrem*/
	virtual void hard_drop(playing_field& field) = 0;
	virtual void reserve(playing_field& field) = 0;
};


class I_shape : public blocks
{
private:				//      [ ] [ ] [ ] [ ]
	int row_position[8]; //    {0,0,0,0,0,0,0,0}
	int column_position[8]; // {4,5,6,7,8,9,10,11}
	bool rotate_Horizontally; //false
	bool rotate_Vertically; //false
public:
	bool action_down(playing_field & field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void hard_drop(playing_field& field);
	void reserve(playing_field& field);
	I_shape(playing_field& field);
	~I_shape();
};

class T_shape : public blocks
{
private:				//      [ ] [ ] [ ] [ ]
	int row_position[8]; //    {1,1,1,1,1,1,0,0 }
	int column_position[8]; // {4,5,6,7,8,9,6,7 }
	bool rotate_Horizontally; //false
	bool rotate_Vertically; //false
public:
	bool action_down(playing_field& field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void hard_drop(playing_field& field);
	void reserve(playing_field& field);
	T_shape(playing_field& field);
	~T_shape();
};

class L_shape : public blocks
{
private:				//      [ ] [ ] [ ] [ ]
	int row_position[8]; //   { 1,1,1,1,1,1,0,0 }
	int column_position[8]; //{ 1,1,1,1,1,1,0,0 }
	bool rotate_Horizontally; //false
	bool rotate_Vertically; //false
public:
	bool action_down(playing_field& field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void hard_drop(playing_field& field);
	void reserve(playing_field& field);
	L_shape(playing_field& field);
	~L_shape();
};

class J_shape : public blocks
{
private:				//      [ ] [ ] [ ] [ ]
	int row_position[8]; //    {0,0,1,1,1,1,1,1}
	int column_position[8]; // {4,5,4,5,6,7,8,9}
	bool rotate_Horizontally; //false
	bool rotate_Vertically; //false
public:
	bool action_down(playing_field& field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void hard_drop(playing_field& field);
	void reserve(playing_field& field);
	J_shape(playing_field& field);
	~J_shape();
};

class O_shape : public blocks
{
private:				//      [ ] [ ] [ ] [ ]
	int row_position[8]; //    {0,0,0,0,1,1,1,1}
	int column_position[8]; // {4,5,6,7,4,5,6,7}
	bool rotate_Horizontally; //false
	bool rotate_Vertically; //false
public:
	bool action_down(playing_field& field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void hard_drop(playing_field& field);
	void reserve(playing_field& field);
	O_shape(playing_field& field);
	~O_shape();
};

class Z_shape : public blocks
{
private:				//      [ ] [ ] [ ] [ ]
	int row_position[8]; //    {0,0,0,0,1,1,1,1}
	int column_position[8]; // {4,5,6,7,6,7,8,9}
	bool rotate_Horizontally; //false
	bool rotate_Vertically; //false
public:
	bool action_down(playing_field& field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void hard_drop(playing_field& field);
	void reserve(playing_field& field);
	Z_shape(playing_field& field);
	~Z_shape();
};

class S_shape : public blocks
{
private:				//      [ ] [ ] [ ] [ ]
	int row_position[8]; //    {1,1,1,1,0,0,0,0}
	int column_position[8]; // {4,5,6,7,6,7,8,9}
	bool rotate_Horizontally; //false
	bool rotate_Vertically; //false
public:
	bool action_down(playing_field& field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void hard_drop(playing_field& field);
	void reserve(playing_field& field);
	S_shape(playing_field& field);
	~S_shape();
};


class playing_field
{
private:
	int height;
	int width;
	int player_points;
	char** field;
	char** queue;
	bool reserve_empty;	
	int reserve_row[8];
	int reserve_column[8];
public:

	playing_field();
	void print_field();
	void change_field(int row[], int column[]);
	void delete_space(int row[], int column[]);
	bool valid_down(int row[], int column[]);
	int hard_drop_step(int row[], int column[]);
	bool valid_left(int row[], int column[]);
	bool valid_right(int row[], int column[]);
	void points();
	void change_queue(int& n2, int& n3);
	void delete_queue();
	void change_reserve(int row[], int column[],int first_row, int first_column);
	void delete_reserve();
	int get_player_points();
	//void reserve(int row[], int column[]);
	bool valid_rotate(vector<vector<int>>& row_flags, vector<vector<int>>&  column_flags, bool& rotate_horizontaly, bool& rotate_verticaly);
	bool game_over();
	~playing_field();

};