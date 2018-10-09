// the Board class keeps track of all the Minesweeper cells; its constructor
//  initializes the cells

#pragma once

#ifndef Board_H
#define Board_H

#include "GraphicCell.h"
#include "Probability.h"
#include "User_Input.h"

#include <vector>

// a Board keeps track of Cells
class Board {
public:
	Board(int, int, int, int);	// initialize the board with bombs and size
	int get_cell(int, int);	// returns cell number; if click is not in a cell, -1
	int get_num_cells();
	void print_board();  // print board data for debugging
	std::vector<GraphicCell> cells; // need to make some updates to move to private
	void action(Click);		// handle a user click on the window
private:
	std::vector<bool> load_bombs(int);	// randomly assign bombs to the cells
	int count_bombs(const std::vector<std::vector<int>>&);
	std::vector<int> load_count();  // load the number of bombs a Cell touches
	void load_cells();
    // data	
	int bombs;			// total bombs
	int num_cells;		// total cells
	int dim;
	std::vector<bool> bomb_locations;
	std::vector<int> bomb_count;
	// graphics info (for get_cell function)
	int width;
	int buffer;
	// unfinished
	// int num_marked();	// number of bombs marked by the user
	// int bombs_left();	// total bombs - number marked by user
	// std::vector<int> get_cell(int, int); // use click data to determine cell coordinate
};

#endif // !Board_H