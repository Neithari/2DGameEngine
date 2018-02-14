#include "Game.h"

Game::Game()
	:
	gameLoop( false ),
	window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), GAME_NAME ),
	tick( 1.f / 60.f ),
	shape( 100.f ),
	dir( RIGHT )
{
	shape.setFillColor( sf::Color::Green );
	shape.setPosition( 250.f, 100.f );
}

void Game::Go()
{
	gameLoop = true;

	float newTime, frameTime, interpolation;
	float accumulator = 0.0f;
	float currentTime = clock.getElapsedTime().asSeconds();

	// create entities
	ecs.CreateEntities();

	while( gameLoop )
	{
		// handle events
		HandleInput();
		// setup timers and update using them
		newTime = clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;

		while( accumulator >= tick )
		{
			Update( tick );
			accumulator -= tick;
		}
		interpolation = accumulator / tick;
		// clear the window to prep it for next frame
		window.clear();
		// compose the frame with all drawing code
		ComposeFrame( interpolation );
		// show render on the screen
		window.display();
	}
}

void Game::Update( const float tick )
{
	// update the ECS
	ecs.Update( tick );

	float speedPerSec = 200.0f;
	sf::Rect<float> bounds = sf::Rect<float>{ 100.0f, 50.0f, 500.0f, 350.0f };

	float y = speedPerSec * tick;
	float x = speedPerSec * tick;
	auto pos = shape.getPosition();

	if( pos.x > bounds.width )
	{
		shape.setPosition( bounds.width, pos.y );
		dir = DOWN;
	}
	if( pos.x < bounds.left )
	{
		shape.setPosition( bounds.left, pos.y );
		dir = UP;
	}
	if( pos.y < bounds.top )
	{
		shape.setPosition( pos.x, bounds.top );
		dir = RIGHT;
	}
	if( pos.y > bounds.height )
	{
		shape.setPosition( pos.x, bounds.height );
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

void Game::ComposeFrame( const float interpolation )
{
	window.draw( shape );
	ecs.Draw( window, interpolation );
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