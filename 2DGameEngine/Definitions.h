#pragma once
#include <bitset>

// Definitions for the Entity Component System
namespace ecs
{
	// forward declare Component
	struct Component;
	// declared some usings for better readability
	constexpr std::size_t maxComponent{ 32 };
	using ComponentArray = std::array<Component*, maxComponent>;
	using ComponentBitset = std::bitset<maxComponent>;
	using ComponentID = std::size_t;
	using EntityID = std::size_t;
	constexpr std::size_t maxGroups{ 32 };
	using Group = std::size_t;
	using GroupBitset = std::bitset<maxGroups>;
	// enum for entity groups -> each system has a group to iterate over
	enum ECSSystems : Group
	{
		RenderGroup,
		CollisionGroup,
		PhysicsGroup,
		InputGroup
	};
}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAME_NAME "2D Game Engine"