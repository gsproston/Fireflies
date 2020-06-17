#include <SFML/Graphics.hpp>

#include <array>

int main()
{
	sf::Clock clock;
	sf::Time elapsedTime = clock.restart();

	const int fireflyRadius = 10;
	const int numFireflies = 30;

	sf::RenderWindow window(sf::VideoMode(fireflyRadius * 2 * numFireflies, 
		fireflyRadius * 2 * numFireflies), "Fireflies");

	window.setFramerateLimit(60);

	struct tFirefly
	{
		tFirefly()
		{
			freq = rand() % 2 + 0.5;
			// rad between 0 and fireflyRadius
			rad = (rand() % (fireflyRadius * 10 + 1)) / 10.f;
			glowing = rand() % 2;
		}

		void Tick(sf::Time elapsedTime)
		{
			// calculate amount of movement
			const float diff = elapsedTime.asSeconds() * freq * fireflyRadius;
			if (glowing)
			{
				rad += diff;
				if (rad > fireflyRadius)
				{
					rad = rad - (fireflyRadius - rad) * 2;
					glowing = false;
				}
			}
			else
			{
				rad -= diff;
				if (rad < 0)
				{
					rad = -rad;
					glowing = true;
				}
			}
		}

		float freq;
		bool glowing;
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

		window.clear();

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