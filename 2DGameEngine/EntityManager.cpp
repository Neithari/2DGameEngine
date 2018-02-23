#include "EntityManager.h"
#include <algorithm>

namespace ecs
{
	// create an Entity

	void EntityManager::Update( const float tick )
	{
		
	}

	const EntityID EntityManager::CreateEntity()
	{
		auto eID = GetUniqueEntityID();
		entities.emplace_back( eID );
		return eID;
	}

	std::vector<Entity>& EntityManager::GetEntities()
	{
		return entities;
	}

	void EntityManager::DestroyEntity( EntityID eID )
	{
		try
		{
			entities.at( eID ).Destroy();
		}
		catch( const std::out_of_range )
		{
			std::cout << "There is no entity with id: " << eID << std::endl;
			throw;
		}
	}

	/*void EntityManager::Refresh()
	{
		// remove dead entities
		entities.erase( std::remove_if( entities.begin(), entities.end(),
			[]( const Entity& entity )
		{
			return !entity.IsAlive();
		} ),
			entities.end() );
	}*/
}
