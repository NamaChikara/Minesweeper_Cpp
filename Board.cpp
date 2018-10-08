#include "Board.h"
#include "Cell.h"
#include "Probability.h"

#include <iostream>
#include <string>

Board::Board(int dimension, int bombs)
	: bombs{ bombs }, dim{ dimension }
{
	num_cells = dim * dim;
	cells.resize(num_cells);
	load_bombs(bombs);
	load_count();
}

void Board::load_bombs(int bombs)
{
	std::vector<int> locations = random_subset(bombs, 0, num_cells - 1);
	int xcord = 0;
	int ycord = 0;
	for (int i = 0; i < bombs; ++i)
	{	
		// coordinates are 0-indexed
		cells[locations[i]].x = locations[i] % dim;
		cells[locations[i]].y = locations[i] / dim;
		cells[locations[i]].bomb = true;
	}
}

int Board::count_bombs(const std::vector<std::vector<int>>& locations)
{
	int bomb_count = 0;
	// note that a true boolean value implicitly converts to 1, and
	//  false implicitly to 0
	for (size_t i = 0; i < locations.size(); ++i)
	{
		bomb_count += cells[locations[i][0] * dim + locations[i][1]].bomb;
	}
	return bomb_count;
}

void Board::load_count()
{
	std::vector<std::vector<int>> adjacent;	// {x,y} coordinates of ajacent cells

	// top left corner
	adjacent = { {0,1},{1,0},{1,1} };
	cells[0].touching = count_bombs(adjacent);
	// bottom left corner
	adjacent = { {dim - 2, 0},{dim - 2,1},{dim - 1,1} };
	cells[dim*(dim - 1)].touching = count_bombs(adjacent);
	// bottom right corner
	adjacent = { {dim - 1,dim - 2},{dim - 2,dim - 2},{dim - 2,dim - 1} };
	cells[dim*(dim - 1) + dim - 1].touching = count_bombs(adjacent);
	// top right corner
	adjacent = { {0, dim - 2},{1,dim - 2},{1,dim - 1} };
	cells[dim - 1].touching = count_bombs(adjacent);

	// left-most column
	for (int i = 1; i < dim - 1; ++i)
	{
			adjacent = { {i - 1,0},{i - 1,1},{i,1},{i + 1,1},{i + 1,0} };
			cells[i*dim].touching = count_bombs(adjacent);
	}
	// bottom-most row
	for (int i = 1; i < dim - 1; ++i)
	{
		adjacent = { {dim - 1,i - 1},{dim - 2,i - 1},{dim - 2,i},{dim - 2,i + 1},{dim - 1, i + 1} };
		cells[dim*(dim - 1) + i].touching = count_bombs(adjacent);
	}
	// right-most column
	for (int i = 1; i < dim - 1; ++i)
	{
			adjacent = { {i - 1,dim - 1},{i - 1,dim - 2},{i,dim - 2},{i + 1,dim - 2},{i + 1,dim - 1} };
			cells[i*dim + dim - 1].touching = count_bombs(adjacent);
	}
	// top-most row
	for (int i = 1; i < dim - 1; ++i)
	{
		adjacent = { {0,i - 1},{1,i - 1},{1,i},{1,i + 1},{0,i + 1} };
		cells[i].touching = count_bombs(adjacent);
	}
	
	// center of the board
	for (int i = 1; i < dim - 1; ++i)
	{
		for (int j = 1; j < dim - 1; ++j)
		{
			adjacent = { {i - 1,j - 1},{i,j - 1},{i + 1,j - 1},{i + 1,j},
							{i + 1,j + 1},{i,j + 1},{i - 1,j + 1},{i - 1,j} };
			cells[i*dim + j].touching = count_bombs(adjacent);
		}
	}
}

void Board::print_board()
{
	for (int i = 0; i < num_cells; ++i)
	{
		std::string b = (cells[i].bomb) ? "b" : "";
		std::cout << cells[i].touching << b << '\t';
		if (i % dim == dim - 1)
			std::cout << std::endl;
	}
}