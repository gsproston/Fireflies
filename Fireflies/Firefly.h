#pragma once

#include <SFML/System/Time.hpp>


class Firefly
{
public:
	Firefly();

	void Tick(sf::Time elapsedTime);

	float rad;
private:
	float freq;
	bool glowing;
};
