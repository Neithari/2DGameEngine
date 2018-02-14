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
		// update all entities
		void Update( const float tick );
		// draw all drawable entities
		void Draw( sf::RenderWindow& window, const float interpolation ) const;
		// create an Entity
		Entity& CreateEntity();
		// put an entity inside a group -> use only from entity
		void AddToGroup( Entity& entity, Group mGroup );
		// get entities that belong to a group
		std::vector<Entity*>& GetEntitiesByGroup( Group mGroup );
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