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

// create an Entity

Entity& ECS::CreateEntity()
{
	entities.emplace_back( std::make_unique<Entity>( GetUniqueEntityID(), *this ) );
	return *entities.back();
}

// put an entity inside a group

void ECS::AddToGroup( Entity& entity, ecs::Group mGroup )
{
	groupedEntities[mGroup].emplace_back( &entity );
}

// get entities that belong to a group

std::vector<Entity*>& ECS::GetEntitiesByGroup( ecs::Group mGroup )
{
	return groupedEntities[mGroup];
}

void ECS::Refresh()
{
	// remove dead entities and entities within wrong groups from grouped entities
	for( auto i( 0u ); i < ecs::maxGroups; ++i )
	{
		auto& g( groupedEntities[i] );

		g.erase( std::remove_if(g.begin(), g.end(),
			[i](Entity* mEntity)
			{
				if( !mEntity->HasGroup( i ) )
				{
					mEntity->Destroy();
				}
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
