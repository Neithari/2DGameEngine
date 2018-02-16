#include "Component.h"
#include "Entity.h"

namespace ecs
{
	void Drawable::Init()
	{
		draw = true;
		entity->AddGroup( ECSSystems::RenderGroup );
	}
	void Drawable::Toggle()
	{
		if( draw )
		{
			draw = false;
			entity->DelGroup( ECSSystems::RenderGroup );
		}
		else
		{
			draw = true;
			entity->AddGroup( ECSSystems::CollisionGroup );
		}
	}
	void Player::Init()
	{
		player = true;
	}
	void Sprite::SetTexture( const sf::Texture & texture )
	{
		sprite.setTexture( texture );
	}
	void Sprite::SetRect( const sf::Vector2i & pos, const sf::Vector2i dim )
	{
		textureRect.left = pos.x;
		textureRect.top = pos.y;
		textureRect.width = dim.x;
		textureRect.height = dim.y;
	}
	void Input::Init()
	{
		handleInput = true;
		entity->AddGroup( ECSSystems::InputGroup );
	}
	void Heading::Init()
	{
		direction = Direction::DOWN;
		entity->AddGroup( ECSSystems::PhysicsGroup );
	}
	void Environment::Init()
	{
		environment = true;
	}
	void Collision::Init()
	{
		entity->AddGroup( ECSSystems::CollisionGroup );
	}
	void Collision::Terminate()
	{
		entity->DelGroup( ECSSystems::CollisionGroup );
	}
	void Enemy::Init()
	{
		enemy = true;
	}
}