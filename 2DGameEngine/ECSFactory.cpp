#include "ECSFactory.h"

namespace ecs
{
	ECSFactory::ECSFactory( EntityManager& entityManager, ResourceManager& resManager )
		:
		entityManager( entityManager ),
		resManager( resManager )
	{
	}

	Entity& ECSFactory::CreateSkeleton()
	{
		auto& skeleton( entityManager.CreateEntity() );
		resManager.AddTexture( "skeleton", "Sprite\\Skeleton.png" );
		skeleton.AddComponent<Sprite>( resManager.GetTexture( "skeleton" ) );
		skeleton.AddComponent<Drawable>();
		skeleton.AddComponent<Position>( sf::Vector2f{ 300.f, 130.f } );
		skeleton.AddComponent<Hitpoints>( 10 );
		skeleton.AddComponent<Animation>( sf::IntRect{ 0,5,66,72 } );
		skeleton.AddGroup( ecs::ECSGroups::NPC );
		return skeleton;
	}
}