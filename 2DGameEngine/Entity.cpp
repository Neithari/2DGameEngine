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

	// update all components

	void Entity::Update( const float tick )
	{
		for( auto& c : components )
		{
			c->Update( tick );
		}
	}

	// draw all components

	void Entity::Draw( sf::RenderWindow& window, const float interpolation ) const
	{
		for( auto& c : components )
		{
			c->Draw( window, interpolation );
		}
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

	void Entity::AddGroup( Group mGroup )
	{
		groupBitset[mGroup] = true;
		manager.AddToGroup( *this, mGroup );
	}

	void Entity::DelGroup( Group mGroup )
	{
		groupBitset[mGroup] = false;
	}
}