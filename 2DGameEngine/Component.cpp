#include "Component.h"
#include "Entity.h"

namespace ecs
{
	void Animation::Init()
	{
		sprite = &entity->GetComponent<Sprite>();
	}

	void Animation::Update( const float tick )
	{
		if( lastTime >= 1.0f )
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

			float reset = 0.0f;
			lastTime = reset;
		}
		lastTime += tick;
		sprite->sprite.setTextureRect( spriteRect );
	}

	void Position::Init()
	{
		sprite = &entity->GetComponent<Sprite>();
	}

	void Position::Update( const float tick )
	{
		sprite->sprite.setPosition( pos );
	}
	void Drawable::Init()
	{
		isDrawable = true;
	}
}