#include "EntityManager.h"
#include <algorithm>
#include <utility>
#include <iostream>

namespace ecs
{
	// create an Entity

	void EntityManager::Update( const float tick )
	{
		Refresh();
	}

	Entity& EntityManager::CreateEntity()
	{
		entities.emplace_back( std::make_unique<Entity>( GetUniqueEntityID(), *this ) );
		return *entities.back();
	}

	std::vector<std::unique_ptr<Entity>>& EntityManager::GetEntities()
	{
		return entities;
	}

	// put an entity inside a group

	void EntityManager::AddToGroup( Entity& entity, Group group )
	{
		groupedEntities[group].emplace_back( &entity );
	}

	// get entities that belong to a group

	std::vector<Entity*>& EntityManager::GetEntitiesByGroup( Group group )
	{
		return groupedEntities[group];
	}

	void EntityManager::DestroyEntity( EntityID eID )
	{
		try
		{
			entities.at( eID )->Destroy();
		}
		catch( const std::out_of_range )
		{
			std::cout << "There is no entity with id: " << eID << std::endl;
			throw;
		}
	}

	void EntityManager::Refresh()
	{
		// remove dead entities and entities within wrong groups from grouped entities
		for( auto i( 0u ); i < maxGroups; ++i )
		{
			auto& g( groupedEntities[i] );

			g.erase( std::remove_if( g.begin(), g.end(),
				[i]( const Entity* pEntity )
			{
				return !pEntity->IsAlive() || !pEntity->HasGroup( i );
			} ),
				g.end() );
		}
		// remove dead entities
		entities.erase( std::remove_if( entities.begin(), entities.end(),
			[]( const std::unique_ptr<Entity>& entity )
		{
			return !entity->IsAlive();
		} ),
			entities.end() );
	}
}
