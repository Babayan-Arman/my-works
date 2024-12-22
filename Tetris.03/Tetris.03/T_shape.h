#pragma once
#include "blocks.h"

class T_shape : public blocks
{
public:
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void reserve(playing_field& field);
	T_shape(playing_field& field);
	~T_shape();
};