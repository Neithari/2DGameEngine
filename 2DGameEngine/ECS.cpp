#include "ECS.h"
#include <algorithm>
#include <utility>

// create an Entity

void ECS::Update( const sf::Time& dt )
{
	Refresh();
	for( auto& e : entities )
	{
		e->Update( dt );
	}
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
	// remove dead entities and entities within wrong groups
	for( auto i( 0u ); i < ecs::maxGroups; ++i )
	{
		auto& g( groupedEntities[i] );

		g.erase( std::remove_if(g.begin(), g.end(),
			[i](Entity* mEntity)
			{
				return !mEntity->IsAlive() || !mEntity->HasGroup( i );
			} ),
			g.end() );
	}
	// remove dead entities
	entities.erase( std::remove_if( entities.begin(), entities.end(),
		[]( const std::unique_ptr<Entity>& mEntity )
		{
			return !mEntity->IsAlive();
		} ),
		entities.end() );
}
