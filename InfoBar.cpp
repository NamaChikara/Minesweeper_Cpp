#include "InfoBar.h"

InfoBar::InfoBar(int tt, int bb, int mm,
	float yloc, float xclock, float xbomb, float xmistakes,
	std::string font_file)
	: time{ tt }, bombs{ bb }, mistakes{ mm },
	clock{ sf::Vector2f{xclock,yloc} },
	bomb_count{ sf::Vector2f{xbomb,yloc} },
	mistake_count{ sf::Vector2f{xmistakes,yloc} }
{
	if (!font.loadFromFile(font_file))
	{
		std::cerr << "Could not load " << font_file << " font file." << std::endl;
	}

	time_text.setFont(font);
	time_text.setString(std::to_string(time));
	time_text.setCharacterSize(24);
	time_text.setFillColor(sf::Color::Blue);
	time_text.move(sf::Vector2f(xclock, yloc));

	bomb_text.setFont(font);
	bomb_text.setString(std::to_string(bombs));
	bomb_text.setCharacterSize(24);
	bomb_text.setFillColor(sf::Color::Blue);
	bomb_text.move(sf::Vector2f(xbomb, yloc));

	mistake_text.setFont(font);
	mistake_text.setString(std::to_string(mistakes));
	mistake_text.setCharacterSize(24);
	mistake_text.setFillColor(sf::Color::Blue);
	mistake_text.move(sf::Vector2f(xmistakes, yloc));
}
