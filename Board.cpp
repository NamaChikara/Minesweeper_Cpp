#include "Board.h"

Board::Board(int dimension, int bombs, int c_width,
	int c_buffer, int y_off)
	: bombs{ bombs }, dim{ dimension }, width{ c_width },
	buffer{ c_buffer }, y_offset{ y_off }
{
	num_cells = dim * dim;
	bomb_locations = load_bombs(bombs);
	bomb_count = load_count();
	load_cells();
}

std::vector<bool> Board::load_bombs(int bombs)
{
	std::vector<int> locations = random_subset(bombs, 0, num_cells - 1);
	std::vector<bool> bomb_loc;
	bool bomb_found = false;
	for (int i = 0; i < num_cells; ++i)
	{
		for (int j = 0; j < locations.size(); ++j)
		{
			// coordinates are 0-indexed
			if (i == locations[j])
			{
				bomb_found = true;
			}
		}
		bomb_loc.push_back(bomb_found);
		bomb_found = false;
	}
	return bomb_loc;
}

std::vector<int> Board::load_count()
{
	std::vector<std::vector<int>> adjacent;	// {x,y} coordinates of ajacent cells
	std::vector<int> bomb_count(num_cells);

	// top left corner
	adjacent = { {0,1},{1,0},{1,1} };
	bomb_count[0] = count_bombs(adjacent);
	// bottom left corner
	adjacent = { {dim - 2, 0},{dim - 2,1},{dim - 1,1} };
	bomb_count[dim*(dim - 1)] = count_bombs(adjacent);
	// bottom right corner
	adjacent = { {dim - 1,dim - 2},{dim - 2,dim - 2},{dim - 2,dim - 1} };
	bomb_count[dim*(dim - 1) + dim - 1] = count_bombs(adjacent);
	// top right corner
	adjacent = { {0, dim - 2},{1,dim - 2},{1,dim - 1} };
	bomb_count[dim - 1] = count_bombs(adjacent);

	// left-most column
	for (int i = 1; i < dim - 1; ++i)
	{
		adjacent = { {i - 1,0},{i - 1,1},{i,1},{i + 1,1},{i + 1,0} };
		bomb_count[i*dim] = count_bombs(adjacent);
	}
	// bottom-most row
	for (int i = 1; i < dim - 1; ++i)
	{
		adjacent = { {dim - 1,i - 1},{dim - 2,i - 1},{dim - 2,i},{dim - 2,i + 1},{dim - 1, i + 1} };
		bomb_count[dim*(dim - 1) + i] = count_bombs(adjacent);
	}
	// right-most column
	for (int i = 1; i < dim - 1; ++i)
	{
		adjacent = { {i - 1,dim - 1},{i - 1,dim - 2},{i,dim - 2},{i + 1,dim - 2},{i + 1,dim - 1} };
		bomb_count[i*dim + dim - 1] = count_bombs(adjacent);
	}
	// top-most row
	for (int i = 1; i < dim - 1; ++i)
	{
		adjacent = { {0,i - 1},{1,i - 1},{1,i},{1,i + 1},{0,i + 1} };
		bomb_count[i] = count_bombs(adjacent);
	}

	// center of the board
	for (int i = 1; i < dim - 1; ++i)
	{
		for (int j = 1; j < dim - 1; ++j)
		{
			adjacent = { {i - 1,j - 1},{i,j - 1},{i + 1,j - 1},{i + 1,j},
							{i + 1,j + 1},{i,j + 1},{i - 1,j + 1},{i - 1,j} };
			bomb_count[i*dim + j] = count_bombs(adjacent);
		}
	}

	return bomb_count;
}

int Board::count_bombs(const std::vector<std::vector<int>>& locations)
{
	int local_bomb_count = 0;
	// note that a true boolean value implicitly converts to 1, and
	//  false implicitly to 0
	for (size_t i = 0; i < locations.size(); ++i)
	{
		local_bomb_count += bomb_locations[locations[i][0] * dim + locations[i][1]];
	}
	return local_bomb_count;
}

void Board::load_cells()
{
	for (int i = 0; i < num_cells; ++i)
	{
		int xcell = i % dim;
		int ycell = i / dim;
		// calculate where the top left corner of the GraphicCell should be
		int x_winloc = xcell * (width + 2 * buffer) + buffer;
		// !! need to make sure float and int are used consistently
		int y_winloc = ycell * (width + 2 * buffer) + buffer + y_offset;
		float f_width = (float)width;
		cells.push_back(GraphicCell{ sf::Vector2f{f_width,f_width},
			x_winloc, y_winloc, bomb_locations[i], bomb_count[i],
			buffer });
	}
}

int Board::get_cell(int x, int y)
{
	int cell_size = width + 2 * buffer;
	// check to see that the click is on the board
	if (x > dim * cell_size || y < y_offset || y > dim * cell_size + y_offset)
	{
		return -1;
	}
	// check to see the click is not on an x buffer
	int xcell = x / cell_size;
	bool xinside = false;
	if (x % cell_size > buffer && x % cell_size < width + buffer)
	{
		xinside = true;
	}
	// check to see the click is not an a y buffer (must subtract y_offset)
	int ycell = (y - y_offset) / cell_size;
	bool yinside = false;
	if ((y - y_offset) % cell_size > buffer && (y - y_offset) % cell_size < width + buffer)
	{
		yinside = true;
	}
	// return the GraphicCell number if the click is not on any buffer (-1 for error)
	return (xinside && yinside) ? ycell * dim + xcell : -1;
}

void Board::action(Click input)
{
	int loc = get_cell(input.x, input.y);
	if (loc >= 0 && loc < num_cells)
	{
		cells[loc].action(input.type);
	}
}

int Board::num_marked() const
{
	int marked = 0;
	for (size_t i = 0; i < cells.size(); ++i)
	{
		if (cells[i].marked)
		{
			++marked;
		}
	}
	return marked;
}

int Board::num_mistakes() const
{
	int mistakes = 0;
	for (size_t i = 0; i < cells.size(); ++i)
	{
		if (cells[i].mistake)
		{
			++mistakes;
		}
	}
	return mistakes;
}

int Board::num_bombs() const
{
	return bombs;
}

bool Board::all_marked() const
{
	int bombs_determined = 0;
	for (size_t i = 0; i < cells.size(); ++i)
	{
		if (cells[i].marked && cells[i].bomb)
		{
			++bombs_determined;
		}
		else if (cells[i].mistake)
		{
			++bombs_determined;
		}
	}
	return (bombs_determined == bombs) ? true : false;
}

void Board::move_colors()
{
	sf::Color first_cell;
	for (size_t i = 0; i < cells.size(); ++i)
	{
		if (i == 1)
		{
			first_cell = cells[i].square.getFillColor();
		}
		if (i == cells.size() - 1)
		{
			cells[i].square.setFillColor(first_cell);
		}
		else
		{
			cells[i].square.setFillColor(cells[i + 1].square.getFillColor());
		}
	}
}

void Board::draw(sf::RenderTarget& target)
{
	for (size_t i = 0; i < cells.size(); ++i)
	{
		cells[i].draw(target, sf::RenderStates());
	}
}

// text-based version of the GraphicCell data (for debugging)
void Board::print_board()
{
	for (int i = 0; i < num_cells; ++i)
	{
		std::string b = (cells[i].bomb) ? "b" : "";
		std::cout << cells[i].touching << b << '\t';
		if (i % dim == dim - 1)
		{
			std::cout << std::endl;
		}
	}
}