#include "Cell.h"

Cell::Cell()
{
	x = y = 0;
	bomb = false;
	marked = false;
	touching = 0;
	covered = true;
}

Cell::Cell(int xcord, int ycord, bool has_bomb)
	: x{ xcord }, y{ ycord }, bomb{ has_bomb }
{
	marked = false;
	touching = 0;
	covered = true;
	mistake = false;
}

void Cell::action(char type)
{
	if (type == 'l')
	{
		if (covered == true)
		{
			covered == false;
			if (bomb == true)
			{
				mistake = true;
			}
		}
	}
	if (type == 'r')
	{
		if (covered == true)
		{
			marked = !marked;
		}
	}
}