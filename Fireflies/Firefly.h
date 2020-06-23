#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>


class Firefly
{
public:
	Firefly();

	sf::CircleShape GetCircle() const;
	void Tick(sf::Time elapsedTime);

private:
	float freq;
	bool glowing;
	float rad;
};
