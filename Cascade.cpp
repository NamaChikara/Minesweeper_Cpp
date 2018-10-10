#include "Cascade.h"

Cascade::Cascade(std::vector<GraphicCell>& m_cells)
	: cells{ m_cells } {}

void Cascade::move_colors()
{
	sf::Color first_cell;
	for (size_t i = 0; i < cells.size(); ++i)
	{
		if (i == 1)
		{
			first_cell = cells[i].getFillColor();
		}
		if (i == cells.size() - 1)
		{
			cells[i].setFillColor(first_cell);
		}
		else
		{
			cells[i].setFillColor(cells[i + 1].getFillColor());
		}
	}
}