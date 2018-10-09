// This file uses Probability.h, Cell.h, and Board.h to generate a
//  Minesweeper game and keep track of user progress.  It requires
//  the SFML graphics library to run.

#include <SFML/Graphics.hpp>
#include "Probability.h"
#include "Board.h"

class MM : public sf::RectangleShape {

};

struct Click {
	int x;
	int y;
	char type;
	Click();
	Click(int, int, char);
};

Click::Click() 
	: x{ 0 }, y{ 0 }, type{ 'e' } {}

Click::Click(int xx, int yy, char which)
	: x{ xx }, y{ yy }, type{ which } {}

int main()
{
	int dim = 6;
	int bomb = 10;
	int c_width = 90;
	int b_width = 5;
	Board b1{ dim,bomb,c_width,b_width };
	b1.print_board();
	sf::RenderWindow window(sf::VideoMode(605, 605), "SFML works!");
	Click action;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			// check to see if the user clicked in the grid
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				action = Click{ localPosition.x, localPosition.y, 'l' };
			}
			// turn off color via right button click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				action = Click{ localPosition.x,localPosition.y,'r' };
			}
		}
		window.clear();
		// update clicked cell
		if (action.type == 'l' || action.type == 'r') 
		{
			int cell_loc = b1.get_cell(action.x, action.y);
			std::cout << cell_loc;
			if (cell_loc != -1)
				b1.cell_action(cell_loc, action.type);
		}
		// draw the grid
		for (int i = 0; i < b1.get_num_cells(); ++i)
		{
			sf::RectangleShape rect(sf::Vector2f(c_width,c_width));
			if (b1.cells[i].covered == false)
			{
				if (b1.cells[i].touching == 0)
					rect.setFillColor(sf::Color(255, 255, 255));
				if (b1.cells[i].touching == 1)
					rect.setFillColor(sf::Color(0, 0, 255));
				if (b1.cells[i].touching == 2)
					rect.setFillColor(sf::Color(0, 255, 0));
				if (b1.cells[i].touching == 3)
					rect.setFillColor(sf::Color(255, 0, 0));
				if (b1.cells[i].touching == 4)
					rect.setFillColor(sf::Color(128, 0, 128));
				if (b1.cells[i].bomb == true)
					rect.setFillColor(sf::Color());
			}
			else
				rect.setFillColor(sf::Color(128, 128, 128));
			if (b1.cells[i].marked == true)
				rect.setFillColor(sf::Color(255, 255, 0));
			rect.setOutlineThickness(b_width);
			rect.setOutlineColor(sf::Color());
			int yloc = i / dim;
			int xloc = i % dim;
			int t_width = c_width + 2 * b_width;
			float xpos = xloc * t_width;
			float ypos = yloc * t_width;
			rect.setPosition(sf::Vector2f(xpos + b_width, ypos + b_width));
			window.draw(rect);

			action = Click{};
		}
		window.display();
	}
	return 0;
}


/*
int main()
{
	// test the Board constructor
	Board board1{ 6,10 };
	board1.print_board();
	std::cin.get();
}
*/