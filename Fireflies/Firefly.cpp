#include "Firefly.h"

#include <cstdlib>

#include "Constants.h"
#include "Utils.h"


Firefly::Firefly()
{
	freq = Utils::GetRandFloat(0.5, 1.5);
	// rad between 0 and fireflyRadius
	rad = Utils::GetRandFloat(0, Constants::FIREFLY_RADIUS);
	glowing = rand() % 2;
}

void Firefly::Sync(const std::vector<Firefly>& vNeighbours)
{
	float avgFreq = 0.f;
	float avgRad = 0.f;

	for (uint8_t i = 0; i < vNeighbours.size(); ++i)
	{
		avgFreq += vNeighbours[i].freq;
		avgRad += vNeighbours[i].rad;
	}
	avgFreq /= vNeighbours.size();
	avgRad /= vNeighbours.size();

	freq += (avgFreq - freq) / 10;
	rad += (avgRad - rad) / 10;
}

void Firefly::Tick(const sf::Time& elapsedTime)
{
	// calculate amount of movement
	float diff = elapsedTime.asSeconds() * freq * Constants::FIREFLY_RADIUS;

	while (diff > 0)
	{
		const float currdiff = diff > Constants::FIREFLY_RADIUS ? Constants::FIREFLY_RADIUS : diff;
		if (glowing)
		{
			rad += currdiff;
			if (rad > Constants::FIREFLY_RADIUS)
			{
				rad = rad - (rad - Constants::FIREFLY_RADIUS) * 2;
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