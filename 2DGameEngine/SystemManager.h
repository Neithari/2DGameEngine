#pragma once
#include <SFML\Graphics.hpp>
#include "EntityManager.h"

namespace ecs
{
	class CollisionSystem
	{
	public:
		CollisionSystem( EntityManager& eManager );
		
		void CheckCollisions();
	private:
		EntityManager& entityManager;
	};
	class RenderSystem
	{
	public:
		RenderSystem( EntityManager& eManager );
		void Draw( sf::RenderWindow& window, const float interpolation );
	private:
		EntityManager& entityManager;
	};
	class InputSystem
	{
	public:
		InputSystem( EntityManager& eManager );

		void Update( const float tick );
	private:
		EntityManager& entityManager;
	};
}