#include "Firefly.h"

#include <cstdlib>

#include "Constants.h"
#include "Utils.h"


Firefly::Firefly()
{
	freq = Utils::GetRandFloat(Constants::MIN_FREQ, Constants::MAX_FREQ);
	// rad between 0 and fireflyRadius
	rad = Utils::GetRandFloat(0, Constants::FIREFLY_RADIUS);
	glowing = rand() % 2;
}

void Firefly::Sync(const sf::Time& elapsedTime, 
	const std::vector<Firefly*>& vNeighbours)
{
	float avgFreq = 0.f;
	float avgRad = 0.f;

	for (uint8_t i = 0; i < vNeighbours.size(); ++i)
	{
		avgFreq += vNeighbours[i]->freq;
		avgRad += vNeighbours[i]->rad;
	}
	avgFreq /= vNeighbours.size();
	avgRad /= vNeighbours.size();

	{
		const float c = 5.f;
		const float y = abs(avgFreq - freq);
		const float x = 1.f / c * y;
		const float x2 = x + elapsedTime.asSeconds();
		const float y2 = 1 / c * x2;
		freq = freq > avgFreq ? freq - y2 : freq + y2;
	}

	{
		const float c = 10.f;
		const float y = abs(avgRad - rad);
		const float x = 1.f / c * y;
		const float x2 = x + elapsedTime.asSeconds();
		const float y2 = 1 / c * x2;
		rad = rad > avgRad ? rad - y2 : rad + y2;
	}

	// range check values
	if (rad < 0)
		rad = 0;
	else if (rad > Constants::FIREFLY_RADIUS)
		rad = Constants::FIREFLY_RADIUS;

	if (freq < Constants::MIN_FREQ)
		freq = Constants::MIN_FREQ;
	else if (freq > Constants::MAX_FREQ)
		freq = Constants::MAX_FREQ;
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