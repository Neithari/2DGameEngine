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
		// components
		skeleton.AddComponent<Sprite>();
		skeleton.GetComponent<Sprite>().SetTexture( resManager.GetTexture( "skeleton" ) );
		skeleton.AddComponent<Drawable>();
		skeleton.AddComponent<Position>();
		skeleton.GetComponent<Position>().SetPos( 300.f, 130.f );
		skeleton.AddComponent<Velocity>();
		skeleton.GetComponent<Velocity>().vel = 100.0f;
		skeleton.AddComponent<Hitpoints>( 10 );
		sf::IntRect startRect{ 0,5,66,72 };
		skeleton.AddComponent<Animation>( startRect );
		skeleton.GetComponent<Sprite>().sprite.setTextureRect( startRect );
		skeleton.AddComponent<Collision>();
		sf::Vector2i dim{ 66, 67 };
		skeleton.GetComponent<Collision>().dim = dim;
		skeleton.AddComponent<Enemy>();

		return skeleton;
	}
	Entity& ECSFactory::CreatePlayer()
	{
		auto& player( entityManager.CreateEntity() );
		resManager.AddTexture( "skeleton", "Sprite\\Skeleton.png" );
		// components
		player.AddComponent<Sprite>();
		player.GetComponent<Sprite>().SetTexture( resManager.GetTexture( "skeleton" ) );
		player.AddComponent<Drawable>();
		player.AddComponent<Position>();
		player.GetComponent<Position>().SetPos( 100.f, 100.f );
		player.AddComponent<Velocity>();
		player.GetComponent<Velocity>().vel = 100.0f;
		player.AddComponent<Hitpoints>( 10 );
		sf::IntRect startRect{ 0,5,66,72 };
		player.AddComponent<Animation>( startRect );
		player.GetComponent<Sprite>().sprite.setTextureRect( startRect );
		player.AddComponent<Collision>();
		sf::Vector2i dim{ 66, 67 };
		player.GetComponent<Collision>().dim = dim;

		player.AddComponent<Input>();
		player.AddComponent<Heading>();
		player.AddComponent<Player>();

		return player;
	}
}