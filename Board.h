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
	// initialize the board with dimension, number of bombs, GraphicCell width,
	//  GraphicCell border width, and how far to offset the Board from the top
	//  of the RenderWindow
	Board(int, int, int, int, int);	
	int get_cell(int, int);		// returns cell number; if click is not in a cell, -1
	int get_num_cells();		// return the value of num_cells
	void print_board();			// print board data for debugging
	std::vector<GraphicCell> cells; // make some updates to move to private?
	void action(Click);			// handle a user click on the window
	int num_marked() const;		// number of bombs marked by the user
	int num_mistakes() const;	// number of bombs left clicked by the user
	int num_bombs() const;		// return number of bombs on the Board
	bool all_marked() const;	// true if all bombs successfully marked/uncovered
	void move_colors();			// visual effect in case of user win
	void draw(sf::RenderTarget& );	// draw the GraphicCells in cells to RenderTarget
private:
	// board initialization functions
	std::vector<bool> load_bombs(int);	// output has length equal to num_cells, true/false
									    //  based on bomb status (uses functions in Probability.h)
	int count_bombs(const std::vector<std::vector<int>>&);	// count the number of bombs in the GraphicCells
															//  specified by the argument vector
	std::vector<int> load_count();		// load the number of bombs a GraphicCell touches (uses count_bombs())
	void load_cells();					// initialize cells vector by calling GraphicCell constructor
    // data	
	int bombs;			// total bombs
	int num_cells;		// total GraphicCells
	int dim;			// number of GraphicCells in a row/column (square board)
	int y_offset;		// vertical offset of the GraphicCell array
	std::vector<bool> bomb_locations;	// bomb_locations[x] == true if GraphicCell x has a bomb
	std::vector<int> bomb_count;		// bomb_count[x] = number bombs adjacent to GraphiCell x
	// GraphicCell info (for get_cell function)
	int width;
	int buffer;
};

#endif // !Board_H