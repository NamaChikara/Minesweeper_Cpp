// !! No longer needed for Minesweeper_Cpp --- the Cascade effect 
//  has been included as a member function of the Board class.

// Cascade effect on the cell colors if the user wins

#pragma once

#ifndef Cascade_H
#define Cascade_H

#include <SFML/Graphics.hpp>
#include "GraphicCell.h"
#include <vector>


struct Cascade
{
	Cascade(std::vector<GraphicCell>&);
	void move_colors();
	std::vector<GraphicCell> cells;
};


#endif // !Cascade_H