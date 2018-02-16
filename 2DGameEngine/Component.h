#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

namespace ecs
{
	// forward declare Entity to be able to create a pointer to the parent Entity
	class Entity;

	// Component as data only
	struct Component
	{
		Entity* entity;

		virtual void Init() {}
		virtual ~Component() {};
	};
	struct Animation : public Component
	{
		Animation( const sf::IntRect& rect )
			:
			spriteRect( rect ),
			startRect( rect )
		{}

		const sf::IntRect startRect;
		sf::IntRect spriteRect;
	};
	struct Collision : public Component
	{
		void Init() override;
		// remove the entity from the CollisionSystem
		void Terminate();

		sf::Vector2i dim;
	};
	struct Player : public Component
	{
		void Init() override;

		bool player;
	};
	struct Enemy : public Component
	{
		void Init() override;

		bool enemy;
	};
	struct Environment : public Component
	{
		void Init() override;

		bool environment;
	};
	struct Damage : public Component
	{
		int damage;
	};
	struct Drawable : public Component
	{
		void Init() override;
		void Toggle();

		bool draw;
	};
	struct Heading : public Component
	{
		void Init() override;

		enum Direction
		{
			DOWN,
			UP,
			LEFT,
			Right
		}direction;
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
	struct Input : public Component
	{
		void Init() override;

		bool handleInput;
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
	struct Position : public Component
	{
		float X() { return pos.x; }
		float Y() { return pos.y; }
		void SetX( float x ) { pos.x = x; }
		void SetY( float y ) { pos.y = y; }
		void SetPos( float x, float y )
		{ 
			SetX( x );
			SetY( y );
		}

		sf::Vector2f pos;
	};
	// declare a texture in the ResourceManager and give it to the Sprite component with a ref
	struct Sprite : public Component
	{
		void SetTexture( const sf::Texture& texture );
		void SetRect( const sf::Vector2i& pos, const sf::Vector2i dim );

		sf::Sprite sprite;
		sf::IntRect textureRect;
	};
	struct Velocity : public Component
	{
		float vel;
	};
}