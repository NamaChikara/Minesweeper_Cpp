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
	int bombs = 25;		// number of bombs the board should have

	// initialize info_text_height before InfoBar since needed for RenderWindow dimension
	float info_text_height = 75;

	// set RenderWindow dimensions and initialize;
	int win_height = 800;
	int win_width = win_height - info_text_height;
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Minesweeper");

	// y offset for the info bar
	float info_text_yset = 25;
	// x locations for the InfoBar
	float bomb_text_x = 50;
	float clock_text_x = 300;
	float mistake_text_x = 550;
	// font for Text objects
	std::string font_file = "SourceSansPro.otf";
	// initialize InfoBar
	InfoBar m_info{ 0,bombs,0,info_text_yset,(float)win_width, font_file };

	// set/calculate GraphicCell dimensions
	int b_width = 5;	// width of the border of a GraphicCell
	int c_width = win_width/dim - b_width*2;	// width of the interior of a GraphicCell
	// initialize Board
	Board m_board{ dim,bombs,c_width,b_width,(int)info_text_height };
	m_board.print_board();		// compare graphic output with text-based version

	// initialize for use in window.isOpen() loop
	Click user_action;

	// to keep track of user progress
	sf::Clock clock;
	bool won = false;
	
	// to apply color shift effect in case of win
	float elapsed = 0;			 // to keep track of time for color shift
	float visual_interval = 250; // milliseconds between color shift 

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

		m_board.draw(window);

		// update InfoBar data
		if (!won)
		{
			int mistakes_made = m_board.num_mistakes();
			std::string m_text = "Mistakes: " + std::to_string(mistakes_made);
			m_info.mistake_text.setString(m_text);

			int bombs_unmarked = bombs - m_board.num_marked() - mistakes_made;
			std::string b_text = "Unmarked: " + std::to_string(bombs_unmarked);
			m_info.bomb_text.setString(b_text);

			sf::Time elapsed = clock.getElapsedTime();
			int time = (int)elapsed.asSeconds();
			m_info.clock_text.setString(std::to_string(time));
		}
		else
		{
			m_info.bomb_text.setString("Winner!");
		}

		m_info.update_location();

		// draw the InfoBar
		window.draw(m_info.clock_text);
		window.draw(m_info.bomb_text);
		window.draw(m_info.mistake_text);

		// reset the value of user_action for the next loop
		user_action = Click{};

		window.display();
	}
	return 0;
}