#include "Game.h"

Game::Game()
	:
	gameLoop( false ),
	gameName( "2D Game Engine" ),
	window( sf::VideoMode( screenWidth, screenHeight ), gameName ),
	tick( sf::seconds( 1.f / 25.f ) ),
	shape( 100.f ),
	dir( RIGHT )
{
	shape.setFillColor( sf::Color::Green );
	shape.setPosition( 250.f, 100.f );
}

void Game::Go()
{
	gameLoop = true;
	// leftover time at the end of each frame
	sf::Time accumulator;

	while( gameLoop )
	{
		// handle events
		HandleInput();
		// update everything
		accumulator += time.restart();

		while( accumulator >= tick )
		{
			Update( tick );
			accumulator -= tick;
		}
		// clear the window to prep it for next frame
		window.clear();
		// compose the frame with all drawing code
		ComposeFrame();
		// show render on the screen
		window.display();
	}
}

void Game::Update( const sf::Time& dt )
{
	
	float x = 1.0f * dt.asMilliseconds();
	float y = 1.0f * dt.asMilliseconds();
	auto pos = shape.getPosition();
	if( pos.x > 500.f )
	{
		shape.setPosition( 500.f, pos.y );
		dir = DOWN;
	}
	if( pos.x < 100.f )
	{
		shape.setPosition( 100.f, pos.y );
		dir = UP;
	}
	if( pos.y < 50.f )
	{
		shape.setPosition( pos.x, 50.f );
		dir = RIGHT;
	}
	if( pos.y > 350.f )
	{
		shape.setPosition( pos.x, 350.f );
		dir = LEFT;
	}
		
	if( dir == RIGHT )
	{
		y = 0.f;
	}
	if( dir == LEFT )
	{
		x = -x;
		y = 0.f;
	}
	if( dir == UP )
	{
		x = 0.f;
		y = -y;
	}
	if( dir == DOWN )
	{
		x = 0.f;
	}
	
	shape.move( { x,y } );
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