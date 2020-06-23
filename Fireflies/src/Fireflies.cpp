#include <SFML/Graphics.hpp>

#include <array>
#include "Constants.h"
#include "Grid.h"


int main()
{
	srand(time(0));

	sf::Clock clock;
	sf::Time elapsedTime = clock.restart();

	const int LEN = Constants::FIREFLY_RADIUS * 2 * Constants::NUM_FIREFLIES;
	sf::RenderWindow window(sf::VideoMode(LEN, LEN), "Fireflies");

	window.setFramerateLimit(60);

	Grid::Init();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		window.clear();

		// draw the array of fireflies
		Grid::Draw(window);

		window.display();
		elapsedTime = clock.restart();

		// tick the array of fireflies
		Grid::Tick(elapsedTime);
	}

	return 0;
}