#include "Component.h"
#include "Entity.h"

void Animation::Init()
{
	sprite = &entity->GetComponent<Sprite>();
}

void Animation::Update( const sf::Time& dt )
{
	if( lastTime.asSeconds() >= 1.0f )
	{
		if( sx >= 4 )
		{
			spriteRect.left = startRect.left;
			sx = 0;
			sy++;;
		}
		if( sy >= 4 )
		{
			spriteRect.top = startRect.top;
			sy = 0;
		}
		spriteRect.left = sx * spriteRect.width;
		spriteRect.top = sy * ( spriteRect.height - startRect.top );
		sx++;
	
		sf::Time reset{};
		lastTime = reset;
	}
	lastTime += dt;
	sprite->sprite.setTextureRect( spriteRect );
}

void Position::Init()
{
	sprite = &entity->GetComponent<Sprite>();
}

void Position::Update( const sf::Time& dt )
{
	sprite->sprite.setPosition( pos );
}
