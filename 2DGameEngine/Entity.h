#pragma once

#include "Definitions.h"

namespace ecs
{
	// forward declare ECS to be able to create a reference to the manager
	class EntityManager;
	// container of Component and System logic
	class Entity
	{
	public:
		Entity( EntityID id );

		bool IsAlive() const;
		// destroy the entity and all it's components
		void Destroy();
		// get entity id
		EntityID GetEntityID() const;

	private:
		bool alive = false;
		const EntityID entityID;
	};
}