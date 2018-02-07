#pragma once

#include "Entity.h"
#include <vector>
#include <memory>
// Entity Manager
// TODO: get rid of the normal pointers and use smart pointers
class ECS
{
public:
	// update all entities
	void Update( const sf::Time& dt );
	// draw all drawable entities
	void Draw( sf::RenderWindow& window ) const;
	// create an Entity
	Entity& CreateEntity();
	// put an entity inside a group -> use only from entity
	void AddToGroup( Entity& entity, ecs::Group mGroup );
	// get entities that belong to a group
	std::vector<Entity*>& GetEntitiesByGroup( ecs::Group mGroup );

private:
	// erase dead entities
	void Refresh();
	// returns a unique id for each call
	ecs::EntityID GetUniqueEntityID() noexcept
	{
		static ecs::EntityID lastID{ 0u };
		return lastID++;
	}
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, ecs::maxGroups> groupedEntities;
};