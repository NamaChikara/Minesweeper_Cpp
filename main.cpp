// This file uses Probability.h, Cell.h, and Board.h to generate a
//  Minesweeper game and keep track of user progress.  It requires
//  the SFML graphics library to run.

#include <SFML/Graphics.hpp>
#include "Probability.h"
#include "Board.h"
#include "GraphicCell.h"
#include "User_Input.h"


int main()
{	
	int dim = 6;
	int bomb = 10;
	int c_width = 90;
	int b_width = 5;
	int win_width = dim * (c_width + 2 * b_width);
	int win_height = dim * (c_width + 2 * b_width);
	
	
	Board b1{ dim,bomb,c_width,b_width };
	b1.print_board();	// compare graphic output with console map

	sf::RenderWindow window(sf::VideoMode(win_width,win_height), "Minesweeper");
	Click user_action;

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
				user_action = Click{ localPosition.x, localPosition.y, 'l' };
			}
			// turn off color via right button click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				user_action = Click{ localPosition.x,localPosition.y,'r' };
			}

		}

		window.clear();

		if (user_action.type == 'l' || user_action.type == 'r')
		{
			b1.action(user_action);
		}

		for (int i = 0; i < b1.cells.size(); ++i)
		{
			window.draw(b1.cells[i]);
		}

		user_action = Click{};

		window.display();
	}
	return 0;
}