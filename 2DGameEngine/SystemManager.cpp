#include "SystemManager.h"

namespace ecs
{
	CollisionSystem::CollisionSystem( EntityManager& eManager )
		:
		entityManager( eManager )
	{}
	void CollisionSystem::CheckCollisions()
	{
		// get all entities that can collide with something
		auto group = entityManager.GetEntitiesByGroup( ECSSystems::CollisionGroup );

		// cache all entities in seperate containers to iterate over
		std::vector<Entity*> playerCache, enemyCache, environmentCache;
		for( auto entity : group )
		{
			if( entity->HasComponent<Player>() )
			{
				playerCache.emplace_back( std::move( entity ) );
			}
			else if( entity->HasComponent<Enemy>() )
			{
				enemyCache.emplace_back( std::move( entity ) );
			}
			else if( entity->HasComponent<Environment>() )
			{
				environmentCache.emplace_back( std::move( entity ) );
			}
		}
		// check if a player entity is colliding with environment and enemy
		for( auto player : playerCache )
		{
			bool collided = false;
			// create the player hitbox to check against
			sf::IntRect playerRect;
			{
				sf::Vector2f playerPos = player->GetComponent<Position>().pos;
				sf::Vector2i playerDim = player->GetComponent<Collision>().dim;
				playerRect.left = int( playerPos.x );
				playerRect.top = int( playerPos.y );
				playerRect.width = playerDim.x;
				playerRect.height = playerDim.y;
			}
			for( auto environment : environmentCache )
			{
				// create the environment hitbox to check against
				sf::IntRect environmentRect;
				{
					sf::Vector2f environmentPos = environment->GetComponent<Position>().pos;
					sf::Vector2i environmentDim = environment->GetComponent<Collision>().dim;
					environmentRect.left = int( environmentPos.x );
					environmentRect.top = int( environmentPos.y );
					environmentRect.width = environmentDim.x;
					environmentRect.height = environmentDim.y;
				}
				if( playerRect.intersects( environmentRect ) )
				{
					// send msg player collided with environment
					collided = true;
					break;
				}
			}
			if( !collided )
			{
				for( auto enemy : enemyCache )
				{
					// create the enemy hitbox to check against
					sf::IntRect enemyRect;
					{
						sf::Vector2f enemyPos = enemy->GetComponent<Position>().pos;
						sf::Vector2i enemyDim = enemy->GetComponent<Collision>().dim;
						enemyRect.left = int( enemyPos.x );
						enemyRect.top = int( enemyPos.y );
						enemyRect.width = enemyDim.x;
						enemyRect.height = enemyDim.y;
					}
					if( playerRect.intersects( enemyRect ) )
					{
						// send msg player collided with enemy
						enemy->GetComponent<Sprite>().sprite.setColor( sf::Color( 255, 255, 255, 128 ) ); // testcode
						break;
					}
					else
					{
						// check if enemy collided with environment
						for( auto environment : environmentCache )
						{
							// create the environment hitbox to check against
							sf::IntRect environmentRect;
							{
								sf::Vector2f environmentPos = environment->GetComponent<Position>().pos;
								sf::Vector2i environmentDim = environment->GetComponent<Collision>().dim;
								environmentRect.left = int( environmentPos.x );
								environmentRect.top = int( environmentPos.y );
								environmentRect.width = environmentDim.x;
								environmentRect.height = environmentDim.y;
							}
							if( enemyRect.intersects( environmentRect ) )
							{
								// send msg enemy collided with environment
								break;
							}
						}
					}
				}
			}
		}
	}
	RenderSystem::RenderSystem( EntityManager& eManager )
		:
		entityManager( eManager )
	{}
	void RenderSystem::Draw( sf::RenderWindow& window, const float interpolation )
	{
		// get all entities that need to be drawn
		auto group = entityManager.GetEntitiesByGroup( ECSSystems::RenderGroup );

		for( auto entity : group )
		{
			auto sprite = entity->GetComponent<Sprite>();
			sprite.sprite.setPosition( entity->GetComponent<Position>().pos );
			window.draw( sprite.sprite );
		}
	}
	InputSystem::InputSystem( EntityManager& eManager )
		:
		entityManager( eManager )
	{}
	void InputSystem::Update( const float tick )
	{
		// get all entities that need to be drawn
		auto group = entityManager.GetEntitiesByGroup( ECSSystems::InputGroup );
		auto heading = Heading::DOWN;
		sf::Vector2f velocity;
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
		{
			heading = Heading::UP;
			velocity.y = -1.0f;
		}
		else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
		{
			heading = Heading::DOWN;
			velocity.y = 1.0f;
		}
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
		{
			heading = Heading::LEFT;
			velocity.x = -1.0f;
		}
		else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
		{
			heading = Heading::Right;
			velocity.x = 1.0f;
		}
		for( auto entity : group )
		{
			entity->GetComponent<Heading>().direction = heading;
			velocity = velocity * entity->GetComponent<Velocity>().vel;
			entity->GetComponent<Position>().pos += velocity * tick;
		}
	}
}