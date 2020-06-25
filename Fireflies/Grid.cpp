#include "Grid.h"

#include <array>

#include "Constants.h"
#include "Firefly.h"


namespace Grid
{
	namespace
	{
		typedef std::array<std::array<Firefly, Constants::NUM_FIREFLIES>, Constants::NUM_FIREFLIES> fireflyArrayType;
		fireflyArrayType aFireflies;
		fireflyArrayType aFirefliesCopy;

		void GetNeighbours(const uint8_t x, const uint8_t y,
			std::vector<Firefly*>& vNeighbours)
		{
			vNeighbours.clear();
			for (int8_t i = -1; i <= 1; ++i)
			{
				const uint8_t xpos = x + i;
				if (xpos < 0 || xpos >= aFireflies.size())
					continue;

				for (int8_t j = -1; j <= 1; ++j)
				{
					if (i == 0 && j == 0)
						continue;

					const uint8_t ypos = y + j;
					if (ypos < 0 || ypos >= aFireflies[xpos].size())
						continue;

					vNeighbours.push_back(&aFireflies[xpos][ypos]);
				}
			}
		}
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
		aFirefliesCopy = aFireflies;
	}

	void Draw(sf::RenderWindow& window)
	{
		sf::CircleShape circleShape;
		circleShape.setFillColor(sf::Color::Yellow);

		for (uint8_t x = 0; x < aFireflies.size(); ++x)
		{
			for (uint8_t y = 0; y < aFireflies[x].size(); ++y)
			{
				const float rad = aFireflies[x][y].GetRad();
				circleShape.setRadius(rad);
				circleShape.setPosition(
					x * Constants::FIREFLY_RADIUS * 2.f + Constants::FIREFLY_RADIUS - rad, 
					y * Constants::FIREFLY_RADIUS * 2.f + Constants::FIREFLY_RADIUS - rad);
				window.draw(circleShape);
			}
		}
	}

	void Tick(const sf::Time& elapsedTime)
	{
		for (uint8_t x = 0; x < aFireflies.size(); ++x)
		{
			for (uint8_t y = 0; y < aFireflies[x].size(); ++y)
			{
				aFireflies[x][y].Tick(elapsedTime);
			}
		}
		aFirefliesCopy = aFireflies;

		std::vector<Firefly*> vNeighbours;
		for (uint8_t x = 0; x < aFireflies.size(); ++x)
		{
			for (uint8_t y = 0; y < aFireflies[x].size(); ++y)
			{
				GetNeighbours(x, y, vNeighbours);
				aFirefliesCopy[x][y].Sync(vNeighbours);
			}
		}
		aFireflies = aFirefliesCopy;
	}
}