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
	auto& skeleton( ecs.CreateEntity() );
	skeleton.AddComponent<Position>( sf::Vector2f{ 10.f, 10.f } );
	skeleton.AddComponent<NPC>();
	skeleton.AddComponent<Hitpoints>( 10 );
	skeleton.AddComponent<Sprite>( "Sprite\\Skeleton.png" );

	while( gameLoop )
	{
		// handle events
		HandleInput();
		// update everything
		accumulator += time.restart();

		while( accumulator >= tick )
		{
			Update( tick );
			ecs.Update( tick );
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
	float speedPerSec = 200.0f;
	sf::Rect<float> bounds = sf::Rect<float>{ 100.0f, 50.0f, 500.0f, 350.0f };

	float x = speedPerSec * dt.asSeconds();
	float y = speedPerSec * dt.asSeconds();
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

void Game::ComposeFrame()
{
	window.draw( shape );
	ecs.Draw( window );
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