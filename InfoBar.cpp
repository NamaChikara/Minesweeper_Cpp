#include "InfoBar.h"

InfoBar::InfoBar(float swidth, float yloc, float height,
	 std::string font_file)
	: screen_width{ swidth }, y_offset{ yloc }, info_height{ height }
{
	if (!font.loadFromFile(font_file))
	{
		std::cerr << "Could not load " << font_file << " font file." << std::endl;
	}

	// note: the string values of these text boxes is set in main.cpp
	//  the locations are also set in main.cpp via InfoBar::update_location();
	clock_text.setFont(font);
	clock_text.setCharacterSize(30);
	clock_text.setFillColor(sf::Color(255,255,255));

	bomb_text.setFont(font);
	bomb_text.setCharacterSize(30);
	bomb_text.setFillColor(sf::Color(255,255,255));

	mistake_text.setFont(font);
	mistake_text.setCharacterSize(30);
	mistake_text.setFillColor(sf::Color(255,255,255));
}

void InfoBar::update_text(sf::Clock clock, const Board& m_board)
{
	int mistakes_made = m_board.num_mistakes();
	std::string m_text = "Mistakes: " + std::to_string(mistakes_made);
	mistake_text.setString(m_text);

	int bombs_unmarked = m_board.num_bombs() - m_board.num_marked() - mistakes_made;
	std::string b_text = "Unmarked: " + std::to_string(bombs_unmarked);
	bomb_text.setString(b_text);

	sf::Time elapsed = clock.getElapsedTime();
	int time = (int)elapsed.asSeconds();
	clock_text.setString(std::to_string(time));
}

void InfoBar::update_location()
{
	// x spacing first
	float clock_width = clock_text.getGlobalBounds().width;
	float bomb_width = bomb_text.getGlobalBounds().width;
	float mistake_width = mistake_text.getGlobalBounds().width;

	float spacing = (screen_width - clock_width - bomb_width - mistake_width) / 4;

	// y spacing
	float y_set = y_offset + (info_height - bomb_text.getGlobalBounds().height) / 2;

	float clock_x = spacing;
	clock_text.setPosition(sf::Vector2f(clock_x, y_set));

	float bomb_x = 2 * spacing + clock_width;
	bomb_text.setPosition(sf::Vector2f(bomb_x, y_set));

	float mistake_x = 3 * spacing + clock_width + bomb_width;
	mistake_text.setPosition(sf::Vector2f(mistake_x, y_set));
}

void InfoBar::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(clock_text);
	target.draw(bomb_text);
	target.draw(mistake_text);
}

void InfoBar::update(sf::Clock clock, const Board& m_board,
	sf::RenderTarget& target)
{
	update_text(clock, m_board);
	update_location();
	draw(target, sf::RenderStates());
}