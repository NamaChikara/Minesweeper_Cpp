// the Board class keeps track of all the Minesweeper cells; its constructor
//  initializes the cells

#pragma once

#ifndef Board_H
#define Board_H

#include <vector>
#include "Cell.h"

// a Board keeps track of Cells
class Board {
public:
	Board(int, int, int, int);	// initialize the board with bombs and size
	void print_board();  // print board data for debugging
	int get_cell(int, int);	// returns cell number; if click is not in a cell, -1
	void cell_action(int, char);
	int get_num_cells();
private:
	void load_bombs(int);	// randomly assign bombs to the cells
	int count_bombs(const std::vector<std::vector<int>>&);
	void load_count();		// load the number of bombs a Cell touches
	// data
	std::vector<Cell> cells;	
	int bombs;			// total bombs
	int num_cells;		// total cells
	int dim;
	// graphics info (for get_cell function)
	int width;
	int buffer;
	// unfinished
	// int num_marked();	// number of bombs marked by the user
	// int bombs_left();	// total bombs - number marked by user
	// std::vector<int> get_cell(int, int); // use click data to determine cell coordinate
};

#endif // !Board_H