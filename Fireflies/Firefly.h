#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>


class Firefly
{
public:
	Firefly();

	float GetRad() const { return this->rad; };

	void Sync(const std::vector<Firefly>& vNeighbours);
	void Tick(const sf::Time& elapsedTime);

private:
	float freq;
	bool glowing;
	float rad;
};
