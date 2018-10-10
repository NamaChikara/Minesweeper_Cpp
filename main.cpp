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
	int dim = 10;		// number of GraphicCells per row/column (square game board)
	int bomb = 20;		// number of bombs the board should have
	int c_width = 90;	// width of the interior of a GraphicCell
	int b_width = 5;	// width of the border of a GraphicCell
	int win_width = dim * (c_width + 2 * b_width);
	int win_height = dim * (c_width + 2 * b_width);
	
	Board m_board{ dim,bomb,c_width,b_width };
	m_board.print_board();		// compare graphic output with text-based version

	sf::RenderWindow window(sf::VideoMode(win_width,win_height), "Minesweeper");
	Click user_action;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			// left click on a covered GraphicCell will uncover it
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				user_action = Click{ localPosition.x, localPosition.y, 'l' };
			}
			// right click on a marked/unmarked GraphicCell will unmark/mark it
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				user_action = Click{ localPosition.x,localPosition.y,'r' };
			}

		}

		window.clear();	

		if (user_action.type == 'l' || user_action.type == 'r')
		{
			m_board.action(user_action);	// pass the action to the Board to update
		}

		for (int i = 0; i < m_board.cells.size(); ++i)
		{
			window.draw(m_board.cells[i]);
		}

		user_action = Click{};  // reset the value of user_action for the next loop

		window.display();
	}
	return 0;
}