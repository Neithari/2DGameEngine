#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

namespace ecs
{
	// forward declare Entity to be able to create a pointer to the parent Entity
	class Entity;
	// forward declare Sprite because it is used in Animation
	struct Sprite;

	// Component as data only
	struct Component
	{
		Entity* entity;

		virtual void Init() {}
		virtual void Update( const float tick ) {}
		virtual void Draw( sf::RenderWindow& window, const float interpolation ) const {}
		virtual ~Component() {}
	};

	struct Animation : public Component
	{
		Animation( const sf::IntRect& rect )
			:
			spriteRect( rect ),
			startRect( rect )
		{}
		void Init() override;
		void Update( const float tick ) override;
		float lastTime{};
		Sprite* sprite;
		int sx = 0;
		int sy = 0;

		const sf::IntRect startRect;
		sf::IntRect spriteRect;
	};
	struct Damage : public Component
	{
		int damage;
	};
	struct Drawable : public Component
	{
		void Init() override;
		bool isDrawable;
	};
	struct Hitbox : public Component
	{
		sf::Rect<int> hitBox;
	};
	struct Hitpoints : public Component
	{
		Hitpoints( int hp )
			:
			hp( hp )
		{
		}
		int hp;
	};
	struct Name : public Component
	{
		Name( std::string name )
			:
			name( name )
		{
		}
		std::string name;
	};
	struct Player : public Component
	{
		bool isPlayer = true;
	};
	struct Position : public Component
	{
		Position( const sf::Vector2f& pos )
			:
			pos( pos )
		{}
		void Init() override;
		void Update( const float tick ) override;
		Sprite* sprite;
		sf::Vector2f pos;
		float X() { return pos.x; }
		float Y() { return pos.y; }
	};
	// declare a texture in the ResourceManager and give it to the Sprite component with a ref
	struct Sprite : public Component
	{
		Sprite( const sf::Texture& texture )
			:
			texture( texture )
		{
			sprite.setTexture( texture );
		}
		void Draw( sf::RenderWindow& window, const float interpolation ) const override
		{
			window.draw( sprite );
		}
		const sf::Texture& texture;
		sf::Sprite sprite;
	};
	struct Velocity : public Component
	{
		float vx;
		float vy;
	};
}