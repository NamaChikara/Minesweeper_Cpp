// InfoBar keeps track of the clock, bomb count, and number of user mistakes

#pragma once

#ifndef InfoBar_H
#define InfoBar_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream> 
#include "Board.h"

class InfoBar : public sf::Drawable 
{
public:
	// initialize clock time, number of bombs, number of mistakes, the height of the
	//  top left corner of each RectangleShape (they all have the same vertical orientation),
	//  and the horizontal locations of the top of each (unique to each RectangleShape)
	//  right corners (different for each); the string is the font file name for font
	InfoBar(float, float, float, std::string);		
						
	// update calls update_text, update_location, and draw
	void update(sf::Clock, const Board&, sf::RenderTarget&);

private:
	void update_text(sf::Clock, const Board& );
	void update_location();
	// override sf::Drawable's pure virtual function
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::Font font;	// must load a font to draw Text objects

	// Text objects will be placed inside the RectangleShapes
	sf::Text clock_text;
	sf::Text bomb_text;
	sf::Text mistake_text;

	// data
	float screen_width;
	float y_offset;		// distance from the top of the RenderWindow to InfoBar
	float info_height;	// vertical space allocated for InfoBar
};

#endif //!InfoBar_H