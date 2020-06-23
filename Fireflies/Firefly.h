#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>


class Firefly
{
public:
	Firefly();

	Firefly& operator=(const Firefly& rhs)
	{
		this->freq = rhs.freq;
		this->glowing = rhs.glowing;
		this->rad = rhs.rad;
		return *this;
	}

	sf::CircleShape GetCircle() const;
	void Sync(const std::vector<Firefly>& vNeighbours);
	void Tick(const sf::Time& elapsedTime);

private:
	float freq;
	bool glowing;
	float rad;
};
