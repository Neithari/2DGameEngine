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
	Entity& CreateEntity()
	{
		Entity* e{ new Entity{ GetUniqueEntityID() } };
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back( std::move( uPtr ) );
		return *e;
	}
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
};