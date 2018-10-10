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
	// data for Board construction
	int dim = 15;		// number of GraphicCells per row/column (square game board)
	int bomb = 20;		// number of bombs the board should have
	int b_width = 5;	// width of the border of a GraphicCell
	int c_width = 800/dim - b_width*2;	// width of the interior of a GraphicCell
	// initialize Board
	Board m_board{ dim,bomb,c_width,b_width };
	m_board.print_board();		// compare graphic output with text-based version

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
	int win_width = dim * (c_width + 2 * b_width);
	int win_height = dim * (c_width + 2 * b_width);
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
			// move the cells down to accommodate the info bar, then back up so that
			//  Board's member function get_cell still works 
			//  !! (Need to make this more intuitive)
			m_board.cells[i].move(sf::Vector2f(float(0), info_text_yset));
			window.draw(m_board.cells[i]);
			m_board.cells[i].move(sf::Vector2f(float(0), -info_text_yset));
		}

		user_action = Click{};  // reset the value of user_action for the next loop

		window.display();
	}
	return 0;
}