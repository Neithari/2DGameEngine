#pragma once

#include "Entity.h"
#include <vector>
#include <memory>
#include "Definitions.h"

namespace ecs
{
	// Entity Manager
	class EntityManager
	{
	public:
		void Update( const float tick );
		// create an Entity
		Entity& CreateEntity();
		// get all entities to iterate over them
		std::vector<std::unique_ptr<Entity>>& GetEntities();
		// put an entity inside a group -> use only from entity
		void AddToGroup( Entity& entity, Group group );
		// get entities that belong to a group
		std::vector<Entity*>& GetEntitiesByGroup( Group group );
		// destroy an Entity by ID
		void DestroyEntity( EntityID eID );

	private:
		// erase dead entities
		void Refresh();
		// returns a unique id for each call
		EntityID GetUniqueEntityID() noexcept
		{
			static EntityID lastID{ 0u };
			return lastID++;
		}
	private:
		std::vector<std::unique_ptr<Entity>> entities;
		std::array<std::vector<Entity*>, maxGroups> groupedEntities;
	};
}