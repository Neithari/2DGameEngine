#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

// forward declare Entity to be able to create a pointer to the parent Entity
class Entity;

// Component as data only
struct Component
{
	Entity* entity;

	virtual void Init() {}
	virtual void Update( const sf::Time& dt ) {}
	virtual void Draw( sf::RenderWindow& window ) const {}
	virtual ~Component() {}
};

struct Animation : public Component
{
	sf::Rect<int> spriteRect;
};
struct Damage : public Component
{
	int damage;
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
struct NPC : public Component
{
	bool isNPC = true;
};
struct Player : public Component
{
	bool isPlayer = true;
};
struct Position : public Component
{
	Position( float x, float y )
		:
		x(x),
		y(y)
	{}
	float x;
	float y;
};
struct Sprite : public Component
{
	Sprite( const std::string& file )
	{
		bool loaded = texture.loadFromFile( file );
		assert( loaded );
		sprite.setTexture( texture );
	}
	void Draw( sf::RenderWindow& window ) const override
	{
		window.draw( sprite );
	}
	sf::Texture texture;
	sf::Sprite sprite;
};
 struct Velocity : public Component
{
	float vx;
	float vy;
};