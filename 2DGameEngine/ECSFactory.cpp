#include "ECSFactory.h"



ECSFactory::ECSFactory( ECS& ecsManager, ResourceManager& resManager )
	:
	ecsManager( ecsManager ),
	resManager( resManager )
{
}

Entity& ECSFactory::CreateSkeleton()
{
	auto& skeleton( ecsManager.CreateEntity() );
	resManager.AddTexture( "skeleton", "Sprite\\Skeleton.png" );
	skeleton.AddComponent<Sprite>( resManager.GetTexture( "skeleton" ) );
	skeleton.AddComponent<Position>( sf::Vector2f{ 300.f, 130.f } );
	skeleton.AddComponent<NPC>();
	skeleton.AddComponent<Hitpoints>( 10 );
	skeleton.AddComponent<Animation>( sf::IntRect{ 0,5,66,72 } );
	skeleton.AddGroup( ecs::ECSGroups::PC );
	return skeleton;
}
