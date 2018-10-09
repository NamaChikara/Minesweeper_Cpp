// this cell inherits graphics from SFML

#pragma once

#ifndef GraphicCell_H
#define GraphicCell_h

#include <SFML/Graphics.hpp>

class GraphicCell : public sf::RectangleShape {
public:
	GraphicCell(sf::Vector2f, int, int, bool, int, int);
	using RectangleShape::RectangleShape;
	int xloc;		// x coordinate within the window
	int yloc;		// y coordinate within the window
	bool bomb;		// true if the Cell holds a bomb
	int touching;	// number of bombs a Cell touches
	bool covered;	// true if Cell has never been clicked on
	bool marked;	// true if the user right clicks the Cell
	bool mistake;	// true if user left clicks a bomb
	void update();
	void action(char);	// respond to left or right click
};

#endif // !GraphicCell_H