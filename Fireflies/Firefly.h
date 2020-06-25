#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>


class Firefly
{
public:
	Firefly();

	sf::CircleShape GetCircle() const;
	void Sync(const std::vector<Firefly>& vNeighbours);
	void Tick(const sf::Time& elapsedTime);

private:
	float freq;
	bool glowing;
	float rad;
};
