#include "Entity.h"
#include "ECS.h"



// check if the entity is alive

Entity::Entity( ecs::EntityID id, ECS & manager )
	:
	alive( true ),
	entityID( id ),
	manager( manager )
{
}

// update all components

void Entity::Update( const sf::Time & dt )
{
	for( auto& c : components )
	{
		c->Update( dt );
	}
}

// draw all components

void Entity::Draw( sf::RenderWindow & window ) const
{
	for( auto& c : components )
	{
		c->Draw( window );
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

ecs::EntityID Entity::GetEntityID() const
{
	return entityID;
}

void Entity::AddGroup( ecs::Group mGroup )
{
	groupBitset[mGroup] = true;
	manager.AddToGroup( *this, mGroup );
}

void Entity::DelGroup( ecs::Group mGroup )
{
	groupBitset[mGroup] = false;
}
