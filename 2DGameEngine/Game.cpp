#include "Game.h"

Game::Game( )
	:
	gameLoop(false),
	gameName( "2D Game Engine" ),
	window( sf::VideoMode( screenWidth, screenHeight ), gameName ),
	shape( 100.f )
{
	shape.setFillColor( sf::Color::Green );
}

void Game::Go()
{
	gameLoop = true;
	while( gameLoop )
	{
		// handle events
		HandleInput();
		// update everything
		Update();
		// clear the window to prep it for next frame
		window.clear();
		// compose the frame with all drawing code
		ComposeFrame();
		// show render on the screen
		window.display();
	}
}

void Game::Update()
{
	shape.move( { .5f,.5f } );
}

void Game::ComposeFrame()
{
	window.draw( shape );
}

void Game::HandleInput()
{
	while( window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
		{
			window.close();
			gameLoop = false;
		}
	}
}