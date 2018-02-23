#pragma once

#include "Definitions.h"
#include "Entity.h"
#include "Component.h"
#include <vector>
#include <memory>
#include <array>
#include <utility>
#include <iostream>

namespace ecs
{
	// Entity Manager
	class EntityManager
	{
	public:
		void Update( const float tick );
		// create an Entity
		const EntityID CreateEntity();
		// get all entities to iterate over them
		std::vector<Entity>& GetEntities();
		// destroy an Entity by ID
		void DestroyEntity( EntityID eID );
		// add component to entity
		template<typename C>
		void AddComponent( EntityID eID )
		{
			static_assert( std::is_base_of<Component, C>::value, "C must inherit from Component" );
			auto cID = GetComponentTypeID<C>();
			// if there is not already a container for the component create it
			if( components.size() <= cID )
			{
				components.emplace_back();
			}
			try
			{
				if( components.at( cID ).at( eID ) == nullptr )
				{
					components.at( cID ).at( eID ) = std::move( std::make_shared<C>() );
				}
				components.at( cID ).at( eID )->entity = eID;
			}
			catch( const std::out_of_range )
			{
				std::cout << "There is no component or entity with id: " << eID << std::endl;
				throw;
			}
		}
		// get component for entity
		template<typename C>
		std::shared_ptr<C> GetComponent( EntityID eID )
		{
			static_assert( std::is_base_of<Component, C>::value, "C must inherit from Component" );
			auto cID = GetComponentTypeID<C>();
			try
			{
				return std::static_pointer_cast<C>( components.at( cID ).at( eID ) );
			}
			catch( const std::out_of_range )
			{
				std::cout << "There is no component or entity with id: " << eID << std::endl;
				throw;
			}
		}
		// get component array
		template<typename C>
		ComponentArray& GetComponentArray()
		{
			static_assert( std::is_base_of<Component, C>::value, "C must inherit from Component" );
			auto cID = GetComponentTypeID<C>();
			try
			{
				return components.at( cID );
			}
			catch( const std::out_of_range )
			{
				std::cout << "There is no component with id: " << cID << std::endl;
				throw;
			}
		}
	private:
		// erase dead entities
		//void Refresh();
		// returns a unique id for each call
		EntityID GetUniqueEntityID() noexcept
		{
			static EntityID lastID{ 0u };
			return lastID++;
		}	
		// each call will return a unique id, only call from GetComponentTypeID
		ComponentID GetUniqueComponentID() noexcept
		{
			static ComponentID lastID{ 0u };
			return lastID++;
		}
		// each call with the same T will return the same id
		template<typename C>
		ComponentID GetComponentTypeID() noexcept
		{
			static_assert( std::is_base_of<Component, C>::value, "C must inherit from Component" );
			static ComponentID typeID{ GetUniqueComponentID() };
			return typeID;
		}
	private:
		std::vector<Entity> entities;
		std::vector<ComponentArray> components;
	};
}