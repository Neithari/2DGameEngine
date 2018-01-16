#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game( sf::RenderWindow& window );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void UpdateModel();
	void ComposeFrame();
private:
	sf::RenderWindow& window;
	sf::CircleShape shape;
};