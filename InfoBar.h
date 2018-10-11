// InfoBar keeps track of the clock, bomb count, and number of user mistakes

#pragma once

#ifndef InfoBar_H
#define InfoBar_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream> 

class InfoBar : public sf::Drawable 
{
public:
	// initialize clock time, number of bombs, number of mistakes, the height of the
	//  top left corner of each RectangleShape (they all have the same vertical orientation),
	//  and the horizontal locations of the top of each (unique to each RectangleShape)
	//  right corners (different for each); the string is the font file name for font
	InfoBar(int, int, int, float, float, std::string);		
						
	void update_location();

	sf::Font font;	// must load a font to draw Text objects

	// Text objects will be placed inside the RectangleShapes
	sf::Text clock_text;
	sf::Text bomb_text;
	sf::Text mistake_text;

	// data
	int time;
	int bombs;
	int mistakes;
	float screen_width;
	float y_offset;

	// override sf::Drawable's pure virtual function
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

};

#endif //!InfoBar_H