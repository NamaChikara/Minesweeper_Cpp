#include "GraphicCell.h"

GraphicCell::GraphicCell(sf::Vector2f vv, int c_xloc, int c_yloc, 
	bool c_bomb, int c_touch, int c_border)
	: square{ vv }, xloc{ c_xloc }, yloc{ c_yloc },
	bomb{ c_bomb }, touching{ c_touch }
{
	covered = true;
	marked = false;
	mistake = false;
	square.setFillColor(sf::Color(128, 128, 128));
	square.setOutlineThickness(c_border);
	square.move(sf::Vector2f(xloc, yloc));
	square.setOutlineColor(sf::Color());	// default constructor is black
	// color for 0 touching through 8 touching
	colors = { sf::Color(255,255,255), sf::Color(0,0,255), sf::Color(0,100,0),
		sf::Color(255,0,0), sf::Color(128,0,128), sf::Color(0,191,255),
		sf::Color(50,205,50), sf::Color(240,128,128), sf::Color(255,140,0) };
}

void GraphicCell::action(char type)
{	
	// left click uncovers the cell; its color changes based on 
	//	the value of bomb and covered (see update())
	if (type == 'l')
	{
		if (covered == true)
		{
			covered = false;
			marked = false;
			if (bomb == true)
			{
				mistake = true;
			}
		}
	}
	// right click "marks" a cell if it is uncovered
	//	color change is handled in update()
	if (type == 'r')
	{
		if (covered == true)
		{
			marked = !marked;
		}
	}
	update();
}

void GraphicCell::update()
{	
	if (!covered)
	{
		// fillColor based on number touching, then override with
		//  black if there is a bomb
		square.setFillColor(colors[touching]);
		if (bomb)
			square.setFillColor(sf::Color());
	}
	else
		square.setFillColor(sf::Color(128, 128, 128));	// standard fill color
	if (marked == true)
		square.setFillColor(sf::Color(255, 255, 0));	// marked as possible bomb
}

void GraphicCell::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(square);
}
