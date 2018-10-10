// InfoBar keeps track of the clock, bomb count, and number of user mistakes

#pragma once

#ifndef InfoBar_H
#define InfoBar_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream> 

struct InfoBar
{
	// initialize clock time, number of bombs, number of mistakes, the height of the
	//  top left corner of each RectangleShape (they all have the same vertical orientation),
	//  and the horizontal locations of the top of each (unique to each RectangleShape)
	//  right corners (different for each); the string is the font file name for font
	InfoBar(int, int, int, float, float, float, float, std::string);		
							
	// RectangleShapes will hold the Text objects
	sf::RectangleShape clock;
	sf::RectangleShape bomb_count;
	sf::RectangleShape mistake_count;

	sf::Font font;	// must load a font to draw Text objects

	// Text objects will be placed inside the RectangleShapes
	sf::Text time_text;
	sf::Text bomb_text;
	sf::Text mistake_text;

	// data
	int time;
	int bombs;
	int mistakes;
};

#endif //!InfoBar_H