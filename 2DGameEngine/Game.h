#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Game
{
public:
	Game();
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void HandleInput(); // handle input
	void Update(); // update the physic
	void ComposeFrame(); // prepare the frame to be drawn and draw it after that
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
	
	sf::CircleShape shape;
};