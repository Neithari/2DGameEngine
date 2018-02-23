#pragma once
#include <bitset>
#include <memory>

// Definitions for the Entity Component System
namespace ecs
{
	// declared some usings for better readability
	constexpr std::size_t maxComponent{ 32u };
	constexpr std::size_t maxEntities{ 512u };
	using EntityID = std::size_t;
	using ComponentID = std::size_t;
	using ResID = std::size_t;
	// forward declare for the array
	struct Component;
	using ComponentArray = std::array<std::shared_ptr<Component>, maxEntities>;

	// enums for identifying resources
	enum class Texture : ResID
	{
		SKELETON,
		CUPHEAD
	};
	enum class Font : ResID
	{
	};
	enum class Sound : ResID
	{
	};
	enum class Music : ResID
	{
	};
}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAME_NAME "2D Game Engine"