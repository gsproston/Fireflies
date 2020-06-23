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

		std::vector<Firefly> GetNeighbours(const uint8_t x, const uint8_t y)
		{
			std::vector<Firefly> vNeighbours;

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

					vNeighbours.push_back(aFireflies[xpos][ypos]);
				}
			}

			return vNeighbours;
		}

		void Copy(fireflyArrayType& dest, const fireflyArrayType& source)
		{
			for (uint8_t x = 0; x < source.size(); ++x)
			{
				for (uint8_t y = 0; y < source[x].size(); ++y)
				{
					dest[x][y] = source[x][y];
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
		Copy(aFirefliesCopy, aFireflies);
	}

	void Draw(sf::RenderWindow& window)
	{
		for (uint8_t x = 0; x < aFireflies.size(); ++x)
		{
			for (uint8_t y = 0; y < aFireflies[x].size(); ++y)
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
		for (uint8_t x = 0; x < aFireflies.size(); ++x)
		{
			for (uint8_t y = 0; y < aFireflies[x].size(); ++y)
			{
				aFireflies[x][y].Tick(elapsedTime);
			}
		}
		Copy(aFirefliesCopy, aFireflies);

		for (uint8_t x = 0; x < aFireflies.size(); ++x)
		{
			for (uint8_t y = 0; y < aFireflies[x].size(); ++y)
			{
				aFirefliesCopy[x][y].Sync(GetNeighbours(x, y));
			}
		}
		Copy(aFireflies, aFirefliesCopy);
	}
}