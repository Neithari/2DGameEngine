#include "ECSFactory.h"

namespace ecs
{
	ECSFactory::ECSFactory( EntityManager& entityManager, ResourceManager& resManager )
		:
		entityManager( entityManager ),
		resManager( resManager )
	{
	}
	void ECSFactory::CreateEnvironment()
	{
		auto eID = entityManager.CreateEntity();
		entityManager.AddComponent<Environment>( eID );
	}
	void ECSFactory::CreatePlayer()
	{
		auto eID = entityManager.CreateEntity();
		resManager.AddTexture( Texture::CUPHEAD, "Sprite\\Cuphead.png" );
		// components
		sf::Vector2f startPos{ 19.f, 11.f };
		sf::Vector2f vel{ 100.f, 100.f };
		sf::Vector2i spriteStartPos{ 19, 11 };
		sf::Vector2i dim{ 64, 100 };
		sf::Vector2i padding{ 39, 11 };
		sf::IntRect startRect{ spriteStartPos, dim };
		entityManager.AddComponent<Player>( eID );
		entityManager.AddComponent<Input>( eID );
		entityManager.AddComponent<Heading>( eID );
		entityManager.AddComponent<Position>( eID );
		entityManager.GetComponent<Position>( eID )->pos = startPos;
		entityManager.AddComponent<Collision>( eID );
		entityManager.AddComponent<Dimention>( eID );
		entityManager.GetComponent<Dimention>( eID )->dim = dim;
		entityManager.AddComponent<Drawable>( eID );
		entityManager.AddComponent<Sprite>( eID );
		entityManager.GetComponent<Sprite>( eID )->textureRect = startRect;
		entityManager.GetComponent<Sprite>( eID )->sprite.setTexture( resManager.GetTexture( Texture::CUPHEAD ) );
		entityManager.GetComponent<Sprite>( eID )->sprite.setTextureRect( startRect );
		entityManager.AddComponent<Animation>( eID );
		entityManager.GetComponent<Animation>( eID )->padding = padding;
		entityManager.GetComponent<Animation>( eID )->startRect = startRect;
		entityManager.GetComponent<Animation>( eID )->spriteRect = startRect;
		entityManager.AddComponent<Velocity>( eID );
		entityManager.GetComponent<Velocity>( eID )->vel = vel;
	}
	void ECSFactory::CreateSkeleton( int count )
	{
		resManager.AddTexture( Texture::SKELETON, "Sprite\\Skeleton.png" );
		sf::Vector2f startPos{ 19.f, 11.f };
		sf::Vector2f vel{ 100.f, 100.f };
		sf::Vector2i spriteStartPos{ 0, 5 };
		sf::Vector2i dim{ 66, 67 };
		sf::Vector2i padding{ 0, 5 };
		sf::IntRect startRect{ spriteStartPos, dim };

		for( ; count <= 0; count-- )
		{
			auto eID = entityManager.CreateEntity();
			// add and set components
			entityManager.AddComponent<Enemy>( eID );
			entityManager.AddComponent<Heading>( eID );
			entityManager.AddComponent<Position>( eID );
			entityManager.GetComponent<Position>( eID )->pos = startPos;
			entityManager.AddComponent<Collision>( eID );
			entityManager.AddComponent<Dimention>( eID );
			entityManager.GetComponent<Dimention>( eID )->dim = dim;
			entityManager.AddComponent<Drawable>( eID );
			entityManager.AddComponent<Sprite>( eID );
			entityManager.GetComponent<Sprite>( eID )->textureRect = startRect;
			entityManager.GetComponent<Sprite>( eID )->sprite.setTexture( resManager.GetTexture( Texture::SKELETON ) );
			entityManager.GetComponent<Sprite>( eID )->sprite.setTextureRect( startRect );
			entityManager.AddComponent<Animation>( eID );
			entityManager.GetComponent<Animation>( eID )->padding = padding;
			entityManager.GetComponent<Animation>( eID )->startRect = startRect;
			entityManager.GetComponent<Animation>( eID )->spriteRect = startRect;
			entityManager.AddComponent<Velocity>( eID );
			entityManager.GetComponent<Velocity>( eID )->vel = vel;
			// set a new position beside the old one
			startPos.x += dim.x + padding.x;
			startPos.y += dim.y + padding.y;
		}
	}
	void ECSFactory::CreateCuphead( int count )
	{
		resManager.AddTexture( Texture::CUPHEAD, "Sprite\\Cuphead.png" );
		sf::Vector2f startPos{ 19.f, 11.f };
		sf::Vector2f vel{ 100.f, 100.f };
		sf::Vector2i spriteStartPos{ 19, 11 };
		sf::Vector2i dim{ 64, 100 };
		sf::Vector2i padding{ 39, 11 };
		sf::IntRect startRect{ spriteStartPos, dim };

		for( ; count > 0; --count )
		{
			auto eID = entityManager.CreateEntity();
			// add and set components
			entityManager.AddComponent<Enemy>( eID );
			entityManager.AddComponent<Heading>( eID );
			entityManager.AddComponent<Position>( eID );
			entityManager.GetComponent<Position>( eID )->pos = startPos;
			entityManager.AddComponent<Collision>( eID );
			entityManager.AddComponent<Dimention>( eID );
			entityManager.GetComponent<Dimention>( eID )->dim = dim;
			entityManager.AddComponent<Drawable>( eID );
			entityManager.AddComponent<Sprite>( eID );
			entityManager.GetComponent<Sprite>( eID )->textureRect = startRect;
			entityManager.GetComponent<Sprite>( eID )->sprite.setTexture( resManager.GetTexture( Texture::CUPHEAD ) );
			entityManager.GetComponent<Sprite>( eID )->sprite.setTextureRect( startRect );
			entityManager.AddComponent<Animation>( eID );
			entityManager.GetComponent<Animation>( eID )->padding = padding;
			entityManager.GetComponent<Animation>( eID )->startRect = startRect;
			entityManager.GetComponent<Animation>( eID )->spriteRect = startRect;
			entityManager.AddComponent<Velocity>( eID );
			entityManager.GetComponent<Velocity>( eID )->vel = vel;
			// set a new position beside the old one
			startPos.x += dim.x + padding.x;
			startPos.y += dim.y + padding.y;
		}
	}
}