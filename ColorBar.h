// The ColorBar class is able to draw a row of evenly spaced, colored boxes,
//  each with a label.  It is used to display the color mappings of the 
//  Minesweeper squares to the player.

#pragma once

#ifndef ColorBar_H
#define ColorBar_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class ColorBar : public sf::Drawable 
{
public:
	ColorBar(float, float, float,  std::string);

	// override sf::Drawable's pure virtual function to provide drawing capability
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
	float width;		// width of the screen
	float height;		// vertical space allocated for ColorBarr
	float border;		// OutlineThickness for the boxes
	float box_dim;		// width and height for the boxes
	float box_count;	// number of boxes to load

	// boxes colored in according to number of bombs touching color
	//  scheme (i = 0 : 8), bomb color (i = 9), and mark color (i = 10)
	std::vector<sf::RectangleShape> boxes;
	std::vector<sf::Color> colors;	// colors to fill the RectangleShape objects
	void load_boxes();				// function to initialize boxes objects

	// Text objects to describe what the colors mean
	std::vector<sf::Text> labels;			// corresponding alpha-numeric descriptions
	std::vector<std::string> label_text;	// strings to fill the Text objects
	sf::Font font;							// font required to draw sf::Text objects
	void load_labels();						// function to initialize labels objects
};

#endif // !ColorBar_H