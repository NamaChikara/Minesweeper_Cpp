#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

	bool squareClick = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// check to see if the user clicked on the first square in the grid
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			if (60 < localPosition.x && localPosition.x < 120)
				if (60 < localPosition.y && localPosition.y < 120)
					squareClick = true;
		}

		// turn off color via right button click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			if (60 < localPosition.x && localPosition.x < 120)
				if (60 < localPosition.y && localPosition.y < 120)
					squareClick = false;
		}

		// draw the grid
		for (int i = 1; i < 5; ++i) {
			for (int j = 1; j < 5; ++j) {
				sf::RectangleShape rect(sf::Vector2f(50, 50));
				rect.setFillColor(sf::Color());
				rect.setOutlineThickness(10);
				rect.setOutlineColor(sf::Color(250, 150, 100));
				rect.setPosition(sf::Vector2f(60 * i, 60 * j));
				// solid fill the first square if clicked on
				if (squareClick == true && i*j == 1)
					rect.setFillColor(sf::Color(250, 150, 100));
				window.draw(rect);
			}
		}

		window.display();
	}

	return 0;
}