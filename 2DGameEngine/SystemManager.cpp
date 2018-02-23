#include "SystemManager.h"

namespace ecs
{
	CollisionSystem::CollisionSystem( EntityManager& eManager )
		:
		entityManager( eManager )
	{
	}
	void CollisionSystem::CheckCollisions()
	{
		// get all the containers for collision
		auto player = entityManager.GetComponentArray<Player>();
		auto enemy = entityManager.GetComponentArray<Enemy>();
		auto environment = entityManager.GetComponentArray<Environment>();
		// for every player check if it collides with environment and then enemy
		for( auto p : player )
		{
			if( p != nullptr )
			{
				EntityID pID = std::static_pointer_cast<Input>( p )->entity;
				if( entityManager.GetComponent<Collision>( pID )->canCollide )
				{
					sf::IntRect playerRect{ static_cast<sf::Vector2i>( entityManager.GetComponent<Position>( pID )->pos ), entityManager.GetComponent<Dimention>( pID )->dim };
					// check if player pID collides with environment eID
					for( auto e : environment )
					{
						if( e != nullptr )
						{
							EntityID eID = std::static_pointer_cast<Input>( e )->entity;
							if( entityManager.GetComponent<Collision>( eID )->canCollide )
							{
								sf::IntRect environmentRect{ static_cast<sf::Vector2i>( entityManager.GetComponent<Position>( eID )->pos ), entityManager.GetComponent<Dimention>( eID )->dim };
								if( playerRect.intersects( environmentRect ) )
								{
									// msg player pID collided with environment eID
									break;
								}
							}
						}
					}
					// check if player pID collides with enemy eID
					for( auto e : enemy )
					{
						if( e != nullptr )
						{
							EntityID eID = std::static_pointer_cast<Enemy>( e )->entity;
							if( entityManager.GetComponent<Collision>( eID )->canCollide )
							{
								sf::IntRect enemyRect{ static_cast<sf::Vector2i>( entityManager.GetComponent<Position>( eID )->pos ), entityManager.GetComponent<Dimention>( eID )->dim };
								if( playerRect.intersects( enemyRect ) )
								{
									// msg player pID collided with enemy eID
									break;
								}
								// check if enemy eID collided with environment envID
								for( auto env : environment )
								{
									if( env != nullptr )
									{
										EntityID envID = std::static_pointer_cast<Environment>( env )->entity;

										if( entityManager.GetComponent<Collision>( envID )->canCollide )
										{
											sf::IntRect environmentRect{ static_cast<sf::Vector2i>( entityManager.GetComponent<Position>( envID )->pos ), entityManager.GetComponent<Dimention>( envID )->dim };
											if( enemyRect.intersects( environmentRect ) )
											{
												// msg enemy eID collided with environment envID
												break;
											}
										}
									}
								}
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
	{
	}
	void RenderSystem::Draw( sf::RenderWindow& window, const float interpolation )
	{
		// get the draw container
		auto drawable = entityManager.GetComponentArray<Drawable>();
		// set sprite position and draw every entity that needs to be drawn
		for( auto d : drawable )
		{
			if( d != nullptr )
			{
				EntityID eID = std::static_pointer_cast<Drawable>( d )->entity;
				if( entityManager.GetComponent<Drawable>( eID )->draw )
				{
					auto draw = entityManager.GetComponent<Sprite>( eID );
					draw->sprite.setPosition( entityManager.GetComponent<Position>( eID )->pos * interpolation );
					window.draw( draw->sprite );
				}
			}
		}
	}
	InputSystem::InputSystem( EntityManager& eManager )
		:
		entityManager( eManager )
	{
	}
	void InputSystem::Update( const float tick )
	{
		// get the input  container
		auto input = entityManager.GetComponentArray<Input>();
		// set heading and velocity based on input, to later update the position
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
		// for every entity that has an input -> handle the input
		for( auto in : input )
		{
			if( in != nullptr )
			{
				EntityID eID = std::static_pointer_cast<Input>( in )->entity;
				if( entityManager.GetComponent<Input>( eID )->handleInput )
				{
					entityManager.GetComponent<Heading>( eID )->direction = heading;
					auto vel = entityManager.GetComponent<Velocity>( eID )->vel;
					velocity.x *= vel.x;
					velocity.y *= vel.y;
					entityManager.GetComponent<Position>( eID )->pos += velocity * tick;
				}
			}
		}
	}
}