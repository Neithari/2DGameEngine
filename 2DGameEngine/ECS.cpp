#include "ECS.h"
#include <algorithm>
#include <utility>

// create an Entity

void ECS::Update( const sf::Time& dt )
{
	for( auto& e : entities )
	{
		e->Update( dt );
	}
	Refresh();
}

void ECS::Draw( sf::RenderWindow& window ) const
{
	for( auto& e : entities )
	{
		e->Draw( window );
	}
}

void ECS::Refresh()
{
	entities.erase( std::remove_if( entities.begin(), entities.end(),
		[]( const std::unique_ptr<Entity>& mEntity )
		{
			return !mEntity->IsAlive();
		} ),
		entities.end() );
}
