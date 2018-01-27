#include "Entity.h"
#include "ECS.h"


inline void Entity::Destroy()
{
	alive = false;
}

inline ecs::EntityID Entity::GetEntityID() const
{
	return entityID;
}

inline void Entity::AddGroup( ecs::Group mGroup )
{
	groupBitset[mGroup] = true;
	manager.AddToGroup( this, mGroup );
}

inline void Entity::DelGroup( ecs::Group mGroup )
{
	groupBitset[mGroup] = false;
}
