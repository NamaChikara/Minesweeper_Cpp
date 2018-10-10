#include "GraphicCell.h"

GraphicCell::GraphicCell(sf::Vector2f vv, int c_xloc, int c_yloc,
	bool c_bomb, int c_touch, int c_border)
	: RectangleShape(vv), xloc{ c_xloc }, yloc{ c_yloc }, 
	bomb{ c_bomb }, touching{ c_touch }
{
	covered = true;
	marked = false;
	mistake = false;
	setFillColor(sf::Color(128, 128, 128));
	setOutlineThickness(c_border);
	move(sf::Vector2f(xloc, yloc));
	setOutlineColor(sf::Color());	// default constructor is black
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
		switch (touching)
		{
		case 0:
			setFillColor(sf::Color(255, 255, 255));
			break;
		case 1:
			setFillColor(sf::Color(0, 0, 255));
			break;
		case 2:
			setFillColor(sf::Color(0, 255, 0));
			break;
		case 3:
			setFillColor(sf::Color(255, 0, 0));
			break;
		case 4:
			setFillColor(sf::Color(128, 0, 128));
			break;
		default:
			setFillColor(sf::Color(255, 255, 255));
			break;
		}
		if (bomb)
			setFillColor(sf::Color());
	}
	else
		setFillColor(sf::Color(128, 128, 128));	// standard fill color
	if (marked == true)
		setFillColor(sf::Color(255, 255, 0));	// marked as possible bomb
}