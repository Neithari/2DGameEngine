#pragma once

#include "Component.h"
#include <memory>
#include <vector>
#include <bitset>
#include <array>
#include <cassert>
#include <algorithm>
#include <utility>

// forward declare ECS to be able to create a reference to the manager
class ECS;


// declared some usings for better readability and hide them inside a namespace
namespace ecs
{
	constexpr std::size_t maxComponent{ 32 };
	using ComponentArray = std::array<Component*, maxComponent>;
	using ComponentBitset = std::bitset<maxComponent>;
	using ComponentID = std::size_t;
	using EntityID = std::size_t;
	constexpr std::size_t maxGroups{ 32 };
	using Group = std::size_t;
	using GroupBitset = std::bitset<maxGroups>;
}
// container of Component and System logic
class Entity
{
public:
	Entity( ecs::EntityID id, ECS& manager )
		:
		alive( true ),
		entityID( id ),
		manager( manager )
	{
	}

	// update all components
	void Update( const sf::Time& dt )
	{
		for( auto& c : components )
		{
			c->Update( dt );
		}
	}
	// draw all components
	void Draw( sf::RenderWindow& window ) const
	{
		for( auto& c : components )
		{
			c->Draw( window );
		}
	}
	// check if the entity is alive
	bool IsAlive() const
	{
		return alive;
	}
	// destroy the entity
	void Destroy();

	// get entity id
	ecs::EntityID GetEntityID() const;
	// factory function
	template<typename T, typename... TArgs>
	T& AddComponent( TArgs&&... mArgs )
	{
		static_assert( std::is_base_of<Component, T>::value, "T must inherit from Component" );
		// assert if we already have the Component
		assert( !HasComponent<T>() );
		// create a new component of type T on the heap and store it in the component vector
		T* c( new T( std::forward<TArgs>( mArgs )... ) );
		// initiate the parent pointer
		c->entity = this;
		//create a unique pointer
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back( std::move( uPtr ) );
		// store the pointer in our component array
		componentArray[GetComponentTypeID<T>()] = c;
		// set the bitset
		componentBitset[GetComponentTypeID<T>()] = true;
		// if there is a init function call it
		c->Init();
		//return a reference to our component
		return *c;
	}
	// return true if an Entity has a specific Component
	template<typename T>
	bool HasComponent()
	{
		static_assert( std::is_base_of<Component, T>::value, "T must inherit from Component" );
		return componentBitset[GetComponentTypeID<T>()];
	}
	// get a specific component
	template<typename T>
	Component& GetComponent() const
	{
		assert( HasComponent<T>() );
		return *static_cast<T*>( componentArray[GetComponentTypeID<T>()] );
	}
	// return true if entitiy is in group
	bool HasGroup( ecs::Group mGroup ) const noexcept
	{
		return groupBitset[mGroup];
	}
	// add the entity to a group
	void AddGroup( ecs::Group mGroup );
	// delete the group
	void DelGroup( ecs::Group mGroup );

private:
	// each call will return a unique id
	ecs::ComponentID GetUniqueComponentID() noexcept
	{
		static ecs::ComponentID lastID{ 0u };
		return lastID++;
	}
	// each call with the same T will return the same id
	template<typename T>
	ecs::ComponentID GetComponentTypeID() noexcept
	{
		static_assert( std::is_base_of<Component, T>::value, "T must inherit from Component" );
		static ecs::ComponentID typeID{ GetUniqueComponentID() };;
		return typeID;
	}
	
private:
	bool alive = false;
	const ecs::EntityID entityID;
	ECS& manager;
	std::vector<std::unique_ptr<Component>> components;
	ecs::ComponentArray componentArray;
	ecs::ComponentBitset componentBitset;
	ecs::GroupBitset groupBitset;
};