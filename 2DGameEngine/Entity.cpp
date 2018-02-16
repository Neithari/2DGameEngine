#include "Entity.h"
#include "EntityManager.h"

namespace ecs
{

	// check if the entity is alive

	Entity::Entity( EntityID id, EntityManager& manager )
		:
		alive( true ),
		entityID( id ),
		manager( manager )
	{
	}

	bool Entity::IsAlive() const
	{
		return alive;
	}

	void Entity::Destroy()
	{
		alive = false;
	}

	// get entity id

	EntityID Entity::GetEntityID() const
	{
		return entityID;
	}

	void Entity::AddGroup( Group group )
	{
		groupBitset[group] = true;
		manager.AddToGroup( *this, group );
	}

	void Entity::DelGroup( Group group )
	{
		groupBitset[group] = false;
	}
}