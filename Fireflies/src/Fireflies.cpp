#include <SFML/Graphics.hpp>

#include <array>
#include "Constants.h"
#include "Firefly.h"


int main()
{
	srand(time(0));

	sf::Clock clock;
	sf::Time elapsedTime = clock.restart();

	const int LEN = Constants::FIREFLY_RADIUS * 2 * Constants::NUM_FIREFLIES;
	sf::RenderWindow window(sf::VideoMode(LEN, LEN), "Fireflies");

	window.setFramerateLimit(60);

	// create 2D array of fireflies
	// int represent luminosity
	std::array<std::array<Firefly, Constants::NUM_FIREFLIES>, Constants::NUM_FIREFLIES> aFireflies;

	// init array to random values
	for (int x = 0; x < aFireflies.size(); ++x)
	{
		for (int y = 0; y < aFireflies[x].size(); ++y)
		{
			aFireflies[x][y] = Firefly();
		}
	}

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
		for (int x = 0; x < aFireflies.size(); ++x)
		{
			for (int y = 0; y < aFireflies[x].size(); ++y)
			{
				sf::CircleShape circleShape = aFireflies[x][y].GetCircle();
				circleShape.move(x * Constants::FIREFLY_RADIUS * 2.f,
					y * Constants::FIREFLY_RADIUS * 2.f);
				window.draw(circleShape);
			}
		}

		window.display();
		elapsedTime = clock.restart();

		// tick the array of fireflies
		for (int x = 0; x < aFireflies.size(); ++x)
		{
			for (int y = 0; y < aFireflies[x].size(); ++y)
			{
				aFireflies[x][y].Tick(elapsedTime);
			}
		}
	}

	return 0;
}