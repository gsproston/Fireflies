#include <SFML/Graphics.hpp>

#include <array>

int main()
{
	const int fireflyRadius = 10;
	const int numFireflies = 30;

	sf::RenderWindow window(sf::VideoMode(fireflyRadius * 2 * numFireflies, 
		fireflyRadius * 2 * numFireflies), "Fireflies");

	window.setFramerateLimit(60);

	struct tFirefly
	{
		tFirefly()
		{
			freq = 1.0f;
			rad = (rand() % 101) / 10.0f;
		}

		float freq;
		float rad;
	};

	// create 2D array of fireflies
	// int represent luminosity
	std::array<std::array<tFirefly, numFireflies>, numFireflies> aFireflies;

	// init array to random values
	for (int x = 0; x < aFireflies.size(); ++x)
	{
		for (int y = 0; y < aFireflies[x].size(); ++y)
		{
			aFireflies[x][y] = tFirefly();
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

		window.display();

		// draw the array of fireflies
		for (int x = 0; x < aFireflies.size(); ++x)
		{
			for (int y = 0; y < aFireflies[x].size(); ++y)
			{
				sf::CircleShape firefly(aFireflies[x][y].rad);
				firefly.setFillColor(sf::Color::Yellow);
				firefly.setPosition(x * fireflyRadius * 2, y * fireflyRadius * 2);
				window.draw(firefly);
			}
		}
	}

	return 0;
}