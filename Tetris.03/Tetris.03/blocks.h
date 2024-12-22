#pragma once
#include <iostream>
#include<vector>
#include <windows.h>

using namespace std;

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
	void change_reserve(int row[], int column[], int first_row, int first_column);
	void delete_reserve();
	int get_player_points();
	bool valid_rotate(vector<vector<int>>& row_flags, vector<vector<int>>& column_flags, bool& rotate_horizontaly, bool& rotate_verticaly);
	bool game_over();
	~playing_field();
};

class blocks
{
protected:
	int row_position[8];
	int column_position[8];
	bool rotate_Horizontally;
	bool rotate_Vertically;
public:
	bool action_down(playing_field& field);
	bool action_left(playing_field& field);
	bool action_right(playing_field& field);
	virtual bool rotate_right(playing_field& field) = 0;
	virtual bool rotate_left(playing_field& field) = 0;
	void hard_drop(playing_field& field);
	virtual void reserve(playing_field& field) = 0;
};