#include "Game.h"

Game::Game( sf::RenderWindow& window )
	:
	window( window ),
	shape( 100.f )
{
	shape.setFillColor( sf::Color::Green );
}

void Game::Go()
{
	// clear the window to prep it for next frame
	window.clear(); 

	// update everything
	UpdateModel();
	// compose the frame with all drawing code
	ComposeFrame();

	// show render on the screen
	window.display();
}

void Game::UpdateModel()
{
	sf::Event event;
	while( window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
			window.close();
	}

	while( window.isOpen() )
	{
		sf::Event event;
		while( window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
				window.close();
		}

		window.clear();
		window.draw( shape );
		window.display();
	}
}

void Game::ComposeFrame()
{
	window.draw( shape );
}