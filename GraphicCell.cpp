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
		setFillColor(sf::Color(128, 128, 128));
	if (marked == true)
		setFillColor(sf::Color(255, 255, 0));
}