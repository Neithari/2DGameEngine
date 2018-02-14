#include "ECS.h"

void ECS::Update( const float tick )
{
	entityManager.Update( tick );
}

void ECS::Draw( sf::RenderWindow & window, const float interpolation )
{
	entityManager.Draw( window, interpolation );
}

void ECS::CreateEntities()
{
	factory.CreateSkeleton();
}
