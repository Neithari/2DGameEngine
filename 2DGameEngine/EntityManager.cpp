#include "EntityManager.h"
#include <algorithm>
#include <utility>

namespace ecs
{

	void EntityManager::Update( const float tick )
	{
		Refresh();
		for( auto& e : entities )
		{
			e->Update( tick );
		}
	}

	void EntityManager::Draw( sf::RenderWindow& window, const float interpolation ) const
	{
		for( auto& e : entities )
		{
			if( e->HasComponent<Drawable>() )
			{
				e->Draw( window, interpolation );
			}
		}
	}

	// create an Entity

	Entity& EntityManager::CreateEntity()
	{
		entities.emplace_back( std::make_unique<Entity>( GetUniqueEntityID(), *this ) );
		return *entities.back();
	}

	// put an entity inside a group

	void EntityManager::AddToGroup( Entity& entity, Group mGroup )
	{
		groupedEntities[mGroup].emplace_back( &entity );
	}

	// get entities that belong to a group

	std::vector<Entity*>& EntityManager::GetEntitiesByGroup( Group mGroup )
	{
		return groupedEntities[mGroup];
	}

	void EntityManager::DestroyEntity( EntityID eID )
	{
		entities.at( eID )->Destroy();
	}

	void EntityManager::Refresh()
	{
		// remove dead entities and entities within wrong groups from grouped entities
		for( auto i( 0u ); i < maxGroups; ++i )
		{
			auto& g( groupedEntities[i] );

			g.erase( std::remove_if( g.begin(), g.end(),
				[i]( Entity* mEntity )
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
}
