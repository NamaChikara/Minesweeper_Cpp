// Cascade effect on the cell colors if the user wins

#pragma once

#ifndef Cascade_H
#define Cascade_H

#include <SFML/Graphics.hpp>
#include "GraphicCell.h"
#include <vector>


class Cascade
{
	Cascade(std::vector<GraphicCell>&);
public:
	void move_colors();
	std::vector<GraphicCell> cells;
};


#endif // !Cascade_H