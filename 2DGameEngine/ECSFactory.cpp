#include "ECSFactory.h"



ECSFactory::ECSFactory( ECS& manager )
	:
	manager( manager )
{
}

Entity& ECSFactory::CreateSkeleton()
{
	auto& skeleton( manager.CreateEntity() );
	skeleton.AddComponent<Sprite>( "Sprite\\Skeleton.png" );
	skeleton.AddComponent<Position>( sf::Vector2f{ 300.f, 130.f } );
	skeleton.AddComponent<NPC>();
	skeleton.AddComponent<Hitpoints>( 10 );
	skeleton.AddComponent<Animation>( sf::IntRect{ 0,5,66,72 } );
	skeleton.AddGroup( 0u );
	return skeleton;
}
