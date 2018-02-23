#include "Entity.h"

namespace ecs
{
	Entity::Entity( EntityID id )
		:
		alive( true ),
		entityID( id )
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

	EntityID Entity::GetEntityID() const
	{
		return entityID;
	}
}