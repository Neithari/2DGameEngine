#pragma once

#include "Component.h"
#include <memory>
#include <vector>
#include <bitset>
#include <array>
#include <cassert>
#include <algorithm>
#include <utility>
#include "Definitions.h"

namespace ecs
{
	// forward declare ECS to be able to create a reference to the manager
	class EntityManager;
	// container of Component and System logic
	class Entity
	{
	public:
		Entity( EntityID id, EntityManager& manager );

		bool IsAlive() const;
		// destroy the entity
		void Destroy();
		// get entity id
		EntityID GetEntityID() const;
		// factory function
		template<typename T, typename... TArgs>
		T& AddComponent( TArgs&&... mArgs )
		{
			static_assert( std::is_base_of<Component, T>::value, "T must inherit from Component" );
			// assert if we already have the Component
			assert( !HasComponent<T>() );
			// create a new component of type T on the heap and store it in the component vector
			auto c( std::make_unique<T>( std::forward<TArgs>( mArgs )... ) );
			// initiate the parent pointer
			c->entity = this;
			// if there is a init function call it
			c->Init();
			//create a unique pointer
			components.emplace_back( std::move( c ) );
			// store the pointer in our component array
			componentArray[GetComponentTypeID<T>()] = components.back().get();
			// set the bitset
			componentBitset[GetComponentTypeID<T>()] = true;
			//return a reference to our component
			return *static_cast<T*>( components.back().get() );
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
		T& GetComponent()
		{
			assert( HasComponent<T>() );
			Component* ptr( componentArray[GetComponentTypeID<T>()] );
			return *static_cast<T*>( ptr );
		}
		// return true if entitiy is in group
		bool HasGroup( Group group ) const noexcept
		{
			return groupBitset[group];
		}
		// add the entity to a group
		void AddGroup( Group group );
		// delete the group
		void DelGroup( Group group );

	private:
		// each call will return a unique id, only call from GetComponentTypeID
		ComponentID GetUniqueComponentID() noexcept
		{
			static ComponentID lastID{ 0u };
			return lastID++;
		}
		// each call with the same T will return the same id
		template<typename T>
		ComponentID GetComponentTypeID() noexcept
		{
			static_assert( std::is_base_of<Component, T>::value, "T must inherit from Component" );
			static ComponentID typeID{ GetUniqueComponentID() };
			return typeID;
		}

	private:
		bool alive = false;
		const EntityID entityID;
		EntityManager& manager;
		std::vector<std::unique_ptr<Component>> components;
		ComponentArray componentArray;
		ComponentBitset componentBitset;
		GroupBitset groupBitset;
	};
}