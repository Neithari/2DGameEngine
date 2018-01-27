#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "ECS.h"
#include "ECSFactory.h"

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
	void Update( const sf::Time& dt );
	// prepare the frame to be drawn and draw it after that
	void ComposeFrame();
private:
	// after Game.Go() it is running till gameLoop is false
	bool gameLoop;
	// main window width
	static constexpr unsigned int screenWidth = 800; 
	// main window height
	static constexpr unsigned int screenHeight = 600;
	// main window name
	const sf::String gameName;
	// main window
	sf::RenderWindow window;
	// event is to process input
	sf::Event event;
	// keep track of the time to update at a fixed rate
	sf::Clock time;
	// game tick
	const sf::Time tick;
	// entity component system
		// manager
	ECS ecs;
		// factory class
	ECSFactory ecsFactory;
	// used for the direction of the shape
	enum Direction
	{
		UP, DOWN, LEFT, RIGHT
	}dir;
	sf::CircleShape shape;
};