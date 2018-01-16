#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Gameloop works!" );
	sf::Event event;
	Game theGame( window );

	while( window.isOpen() )
	{
		// handle events
		while( window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
				window.close();
		}
		// game loop
		theGame.Go();
	}

	return 0;
}