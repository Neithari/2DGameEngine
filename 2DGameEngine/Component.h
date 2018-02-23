#pragma once

#include <SFML/Graphics.hpp>

namespace ecs
{
	// Component as data only
	struct Component
	{
		EntityID entity;
	};
	struct Animation : public Component
	{
		sf::Vector2i padding;
		sf::IntRect startRect;
		sf::IntRect spriteRect;
	};
	struct Collision : public Component
	{
		bool canCollide = true;
	};
	struct Player : public Component
	{
		bool player = true;
	};
	struct Enemy : public Component
	{
		bool enemy = true;
	};
	struct Environment : public Component
	{
		bool environment = true;
	};
	struct Damage : public Component
	{
		int damage;
	};
	struct Drawable : public Component
	{
		bool draw = true;
	};
	struct Heading : public Component
	{
		enum Direction
		{
			DOWN,
			UP,
			LEFT,
			Right
		}
		direction = DOWN;
	};
	struct Hitpoints : public Component
	{
		int hp;
	};
	struct Input : public Component
	{
		bool handleInput = true;
	};
	struct Name : public Component
	{
		std::string name;
	};
	struct Position : public Component
	{
		sf::Vector2f pos;
	};
	struct Dimention : public Component
	{
		sf::Vector2i dim;
	};
	// declare a texture in the ResourceManager and give it to the Sprite component with a ref
	struct Sprite : public Component
	{
		sf::Sprite sprite;
		sf::IntRect textureRect;
	};
	struct Velocity : public Component
	{
		sf::Vector2f vel;
	};
}