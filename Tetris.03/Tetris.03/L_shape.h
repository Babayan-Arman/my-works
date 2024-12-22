#pragma once
#include "blocks.h"

class L_shape : public blocks
{
public:
	bool rotate_right(playing_field& field);
	bool rotate_left(playing_field& field);
	void reserve(playing_field& field);
	L_shape(playing_field& field);
	~L_shape();
};