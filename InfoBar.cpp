#include "InfoBar.h"

InfoBar::InfoBar(int tt, int bb, int mm,
	float yloc, float swidth,
	std::string font_file)
	: time{ tt }, bombs{ bb }, mistakes{ mm },
	screen_width{ swidth }, y_offset{ yloc }
{
	if (!font.loadFromFile(font_file))
	{
		std::cerr << "Could not load " << font_file << " font file." << std::endl;
	}

	// note: the string values of these text boxes is set in main.cpp
	//  the locations are also set in main.cpp via InfoBar::update_location();
	clock_text.setFont(font);
	clock_text.setCharacterSize(24);
	clock_text.setFillColor(sf::Color::Blue);

	bomb_text.setFont(font);
	bomb_text.setCharacterSize(24);
	bomb_text.setFillColor(sf::Color::Blue);

	mistake_text.setFont(font);
	mistake_text.setCharacterSize(24);
	mistake_text.setFillColor(sf::Color::Blue);
}

void InfoBar::update_location()
{
	float clock_width = clock_text.getGlobalBounds().width;
	float bomb_width = bomb_text.getGlobalBounds().width;
	float mistake_width = mistake_text.getGlobalBounds().width;

	float spacing = (screen_width - clock_width - bomb_width - mistake_width) / 4;

	float clock_x = spacing;
	clock_text.setPosition(sf::Vector2f(clock_x, y_offset));

	float bomb_x = 2 * spacing + clock_width;
	bomb_text.setPosition(sf::Vector2f(bomb_x, y_offset));

	float mistake_x = 3 * spacing + clock_width + bomb_width;
	mistake_text.setPosition(sf::Vector2f(mistake_x, y_offset));
}