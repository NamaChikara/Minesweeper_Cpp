// This file uses Probability.h, GraphicCell.h, Board.h, and InfoBar.h
// to generate a  Minesweeper game and keep track of user progress.  It 
// requires the SFML graphics library to run.

// Developed by Zachary Barry (zackbarry13@gmail.com)

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Probability.h"
#include "Board.h"
#include "GraphicCell.h"
#include "User_Input.h"
#include "InfoBar.h"
#include "ColorBar.h"

int main()
{	
	//////////////////////////////////////////////////////////////////
	// Initialize the sf::RenderWindow, Board, InfoBar, and ColorBar
	//////////////////////////////////////////////////////////////////

	// game specifications
	int dim = 15;		// number of GraphicCells per row/column (square game board)
	int bombs = 25;		// number of bombs the board should have
	std::string font_file = "SourceSansPro.otf";	// font for Text objects

	// initialize ColorBar and InfoBar heights since needed for RenderWindow dimension
	float color_bar_height = 50;
	float info_bar_height = 50;

	// set RenderWindow dimensions and initialize;
	float win_height = 800;
	float win_width = win_height - info_bar_height - color_bar_height;
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Minesweeper");

	// initialize ColorBar
	ColorBar m_color{ 11,win_width,color_bar_height,font_file };

	// y offset for the info bar
	float info_text_yset = 25;

	// initialize InfoBar
	InfoBar m_info{ 0,bombs,0,info_text_yset,win_width, font_file };

	// set/calculate GraphicCell dimensions
	int b_width = 5;							// width of the border of a GraphicCell
	int c_width = win_width/dim - b_width*2;	// width of the interior of a GraphicCell
	// initialize Board
	int y_board_offset = (int)(info_bar_height + color_bar_height);
	Board m_board{ dim,bombs,c_width,b_width,y_board_offset };

	// initialize for use in window.isOpen() loop
	Click user_action;

	// to keep track of user progress
	sf::Clock clock;
	bool won = false;
	
	// to apply color shift effect in case of win
	float elapsed = 0;			 // to keep track of time for color shift
	float visual_interval = 250; // milliseconds between color shift 

	//////////////////////////////////////////////////////////////////
	// Play the game
	//////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		// check to see if the user won the game
		won = m_board.all_marked();

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

		// apply cascade effect at intervals
		if (won)
		{
			if (elapsed < clock.getElapsedTime().asMilliseconds() - visual_interval)
			{
				elapsed = clock.getElapsedTime().asMilliseconds();
				m_board.move_colors();
			}
		}

		// redraw the Board and ColorBar
		m_board.draw(window);
		m_color.draw(window, sf::RenderStates());

		// update InfoBar if game is not yet won (update also draws to window)
		if (!won)
		{
			m_info.update(clock, m_board, window);
		}

		// reset the value of user_action for the next loop
		user_action = Click{};

		window.display();
	}
	return 0;
}