#include "ColorBar.h"

ColorBar::ColorBar( float nn, float ww, float hh, std::string font_file)
	: box_count{ nn }, width{ ww }, height{ hh }
{
	// make sure there is enough room for all the boxes
	if (width / box_count < height)
	{
		box_dim = width / box_count;
	}
	else
	{
		box_dim = height;
	}
	// set padding accordingly
	border = (width - box_dim * box_count) / (2 * box_count);
	
	// set colors and initialize boxes
	colors = { sf::Color(255,255,255), sf::Color(0,0,255), sf::Color(0,100,0),
		sf::Color(255,0,0), sf::Color(128,0,128), sf::Color(0,191,255),
		sf::Color(50,205,50), sf::Color(240,128,128), sf::Color(255,140,0),
		sf::Color(0,0,0), sf::Color(255,255,0) };
	load_boxes();

	// load font
	if (!font.loadFromFile(font_file))
	{
		std::cerr << "Could not load " << font_file << " font file." << std::endl;
	}
	// set label_text strings and initialize labels
	label_text = { "0","1","2","3","4","5","6","7","8","B","M" };
	load_labels();
}

void ColorBar::load_boxes()
{
	for (int i = 0; i < (int) box_count; ++i)
	{
		float xoff = i * (box_dim + 2 * border) + border;
		boxes.push_back(sf::RectangleShape{sf::Vector2f(box_dim,box_dim)});
		boxes[i].move(sf::Vector2f(xoff, 0));
		boxes[i].setFillColor(colors[i]);
		boxes[i].setOutlineThickness(border);
		boxes[i].setOutlineColor(sf::Color());
	}
}

void ColorBar::load_labels()
{
	for (int i = 0; i < (int)box_count; ++i)
	{
		labels.push_back(sf::Text{ label_text[i], font, 30 });
		// calculate to center labels[i] within boxes[i]
		sf::Vector2f box_loc = boxes[i].getPosition();
		float box_center_x = box_loc.x + box_dim / 2;
		float box_center_y = box_loc.y + box_dim / 2;
		float xoff = box_center_x - labels[i].getGlobalBounds().width / 2;
		float yoff = box_center_y - labels[i].getGlobalBounds().height;
		labels[i].setPosition(sf::Vector2f(xoff, yoff));
	
		// the first and last boxes are too bright to have white font
		if (i == 0 || i == box_count - 1)
		{
			labels[i].setFillColor(sf::Color());
		}
		else
		{
			labels[i].setFillColor(sf::Color(255, 255, 255));
		}
	}
}

void ColorBar::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (size_t i = 0; i < boxes.size(); ++i)
	{
		target.draw(boxes[i]);
		target.draw(labels[i]);
	}
}