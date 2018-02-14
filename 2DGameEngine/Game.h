#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Definitions.h"
#include "ECS.h"

class Game
{
public:
	Game();
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	// handle input
	void HandleInput();
	// update the game
	void Update( const float dt );
	// prepare the frame to be drawn and draw it after that
	void ComposeFrame( const float interpolation );
private:
	// after Game.Go() it is running till gameLoop is false
	bool gameLoop;
	// main window
	sf::RenderWindow window;
	// event is to process input
	sf::Event event;
	// keep track of the time to update at a fixed rate
	sf::Clock clock;
	// game tick
	const float tick;
	// entity component system
	ECS ecs;
	// used for the direction of the shape
	enum Direction
	{
		UP, DOWN, LEFT, RIGHT
	}dir;
	sf::CircleShape shape;
};