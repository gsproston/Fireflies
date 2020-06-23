#pragma once

#include <SFML/Graphics/RenderWindow.hpp>


namespace Grid
{
	void Init();

	void Draw(sf::RenderWindow& window);
	void Tick(const sf::Time& elapsedTime);
};
