#include <SFML/Graphics.hpp>

#include <array>

float GetRandFloat(const float lower, const float upper)
{
	return lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (upper - lower)));
}

int main()
{
	srand(time(0));

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
			freq = GetRandFloat(0.5, 1.5);
			// rad between 0 and fireflyRadius
			rad = GetRandFloat(0, fireflyRadius);
			glowing = rand() % 2;
		}

		void Tick(sf::Time elapsedTime)
		{
			// calculate amount of movement
			float diff = elapsedTime.asSeconds() * freq * fireflyRadius;

			while (diff > 0)
			{
				const float currdiff = diff > fireflyRadius ? fireflyRadius : diff;
				if (glowing)
				{
					rad += currdiff;
					if (rad > fireflyRadius)
					{
						rad = rad - (rad - fireflyRadius) * 2;
						glowing = false;
					}
				}
				else
				{
					rad -= currdiff;
					if (rad < 0)
					{
						rad = -rad;
						glowing = true;
					}
				}

				diff -= currdiff;
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