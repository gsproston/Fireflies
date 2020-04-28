#include <SFML/Graphics.hpp>

#include <array>

int main()
{
	const int fireflyRadius = 10;
	const int numFireflies = 30;

	sf::RenderWindow window(sf::VideoMode(fireflyRadius * 2 * numFireflies, 
		fireflyRadius * 2 * numFireflies), "Fireflies");

	window.setFramerateLimit(60);

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

		window.display();

		// create 2D array of fireflies
		// int represent luminosity
		std::array<std::array<int, numFireflies>, numFireflies> fireflies;

		// draw the array of fireflies
		for (int x = 0; x < fireflies.size(); ++x)
		{
			for (int y = 0; y < fireflies[x].size(); ++y)
			{
				sf::CircleShape firefly(fireflyRadius);
				firefly.setFillColor(sf::Color::White);
				firefly.setPosition(x * fireflyRadius * 2, y * fireflyRadius * 2);
				window.draw(firefly);
			}
		}
	}

	return 0;
}