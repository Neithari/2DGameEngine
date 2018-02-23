#include "ECS.h"

void ECS::Update( const float tick )
{
	input.Update( tick );
	collisionSystem.CheckCollisions();
}

void ECS::Draw( sf::RenderWindow& window, const float interpolation )
{
	renderSystem.Draw( window, interpolation );
}

void ECS::CreateEntities()
{
	// create environment
	factory.CreateEnvironment();
	// create player
	factory.CreatePlayer();
	// create enemies
	factory.CreateCuphead(2);
}
