#include "O_shape.h"

O_shape::O_shape(playing_field& field)
{
	for (int i = 0; i < 4; i++) //{0,0,0,0,1,1,1,1}
		row_position[i] = 0;	//{4,5,6,7,4,5,6,7}
	for (int i = 4; i < 8; i++)
		row_position[i] = 1;
	for (int i = 0; i < 4; i++)
		column_position[i] = i + 12;
	for (int i = 0; i < 4; i++)
		column_position[i + 4] = i + 12;
	rotate_Horizontally = false;
	rotate_Vertically = false;
	field.change_field(row_position, column_position);
}
bool O_shape::rotate_right(playing_field& field) { return true; }
bool O_shape::rotate_left(playing_field& field) { return true; }
void O_shape::reserve(playing_field& field)
{
	field.change_reserve(row_position, column_position, 2, 7);
}
O_shape::~O_shape() {}
