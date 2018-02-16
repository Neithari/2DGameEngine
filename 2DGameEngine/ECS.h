#pragma once
#include <SFML\Graphics.hpp>
#include <bitset>
#include "ECSFactory.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "SystemManager.h"

// Entity Component System
class ECS
{
public:
	void Update( const float tick );
	void Draw( sf::RenderWindow& window, const float interpolation );
	void CreateEntities();
private:
	ecs::EntityManager entityManager;
	ResourceManager resManager;
	ecs::ECSFactory factory{ entityManager, resManager };
	ecs::RenderSystem renderSystem{ entityManager };
	ecs::InputSystem input{ entityManager };
	ecs::CollisionSystem collisionSystem{ entityManager };
};