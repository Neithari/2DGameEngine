#include "ECSFactory.h"



ECSFactory::ECSFactory( ECS& manager )
	:
	manager( manager )
{
}

Entity& ECSFactory::CreateSkeleton()
{
	auto& skeleton( manager.CreateEntity() );
	skeleton.AddComponent<Position>( sf::Vector2f{ 10.f, 10.f } );
	skeleton.AddComponent<NPC>();
	skeleton.AddComponent<Hitpoints>( 10 );
	skeleton.AddComponent<Sprite>( "Sprite\\Skeleton.png" );
	return skeleton;
}


ECSFactory::~ECSFactory()
{
}
