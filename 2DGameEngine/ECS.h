#pragma once
#include <SFML\Graphics.hpp>
#include <bitset>
#include "ECSFactory.h"
#include "EntityManager.h"
#include "ResourceManager.h"

// Entity Component System
class ECS
{
public:
	void Update( const float tick );
	void Draw( sf::RenderWindow& window, const float interpolation );
	void CreateEntities();
public:
	ecs::EntityManager entityManager;
	ResourceManager resManager;
	ecs::ECSFactory factory{ entityManager, resManager };
private:

};