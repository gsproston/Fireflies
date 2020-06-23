#include "Grid.h"

#include <array>

#include "Constants.h"
#include "Firefly.h"


namespace Grid
{
	namespace
	{
		std::array<std::array<Firefly, Constants::NUM_FIREFLIES>, Constants::NUM_FIREFLIES> aFireflies;
	}

	void Init()
	{
		for (int x = 0; x < aFireflies.size(); ++x)
		{
			for (int y = 0; y < aFireflies[x].size(); ++y)
			{
				aFireflies[x][y] = Firefly();
			}
		}
	}

	void Draw(sf::RenderWindow& window)
	{
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
	}

	void Tick(const sf::Time& elapsedTime)
	{
		for (int x = 0; x < aFireflies.size(); ++x)
		{
			for (int y = 0; y < aFireflies[x].size(); ++y)
			{
				aFireflies[x][y].Tick(elapsedTime);
			}
		}
	}
}