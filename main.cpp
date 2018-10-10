// This file uses Probability.h, Cell.h, and Board.h to generate a
//  Minesweeper game and keep track of user progress.  It requires
//  the SFML graphics library to run.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Probability.h"
#include "Board.h"
#include "GraphicCell.h"
#include "User_Input.h"
#include "InfoBar.h"

int main()
{	
	// game specifications
	int dim = 15;		// number of GraphicCells per row/column (square game board)
	int bomb = 20;		// number of bombs the board should have

	// y offset for the info bar
	float info_text_yset = 25;
	float info_text_height = 75;
	// x locations for the InfoBar
	float bomb_text_x = 50;
	float clock_text_x = 300;
	float mistake_text_x = 550;
	// font for Text objects
	std::string font_file = "SourceSansPro.otf";
	// initialize InfoBar
	InfoBar m_info{ 0,bomb,0,info_text_yset,bomb_text_x,clock_text_x,
		mistake_text_x, font_file };

	// set RenderWindow dimensions and initialize;
	int win_height = 800;
	int win_width = win_height - info_text_height;
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Minesweeper");

	// set/calculate GraphicCell dimensions
	int b_width = 5;	// width of the border of a GraphicCell
	int c_width = (win_height - info_text_height)/dim - b_width*2;	// width of the interior of a GraphicCell
	// initialize Board
	Board m_board{ dim,bomb,c_width,b_width,(int)info_text_height };
	m_board.print_board();		// compare graphic output with text-based version

	// initialize for use in window.isOpen() loop
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

		// draw the InfoBar (pass RenderWindow to InfoBar so that it can do it
		//  on its own?)
		window.draw(m_info.clock);
		window.draw(m_info.bomb_count);
		window.draw(m_info.mistake_count);
		window.draw(m_info.clock_text);
		window.draw(m_info.bomb_text);
		window.draw(m_info.mistake_text);

		// reset the value of user_action for the next loop
		user_action = Click{};  

		window.display();
	}
	return 0;
}