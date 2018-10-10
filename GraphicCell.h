// this cell inherits graphics from SFML

#pragma once

#ifndef GraphicCell_H
#define GraphicCell_H

#include <SFML/Graphics.hpp>

class GraphicCell : public sf::RectangleShape {
public:
	// construct RectangleShape, set covered to true, marked and mistake
	//  to false;  move to the appropriate board location.
	//  the last int specifies outline thickness of the RectangleShape
	GraphicCell(sf::Vector2f, int, int, bool, int, int);
	int xloc;		// x coordinate within the window
	int yloc;		// y coordinate within the window
	bool bomb;		// true if the Cell holds a bomb
	int touching;	// number of bombs a Cell touches
	bool covered;	// true if Cell has never been clicked on
	bool marked;	// true if the user right clicks the Cell
	bool mistake;	// true if user left clicks a bomb
	void action(char);	// change values based on left or right click
	void update();	// update cell color after action
};

#endif // !GraphicCell_H