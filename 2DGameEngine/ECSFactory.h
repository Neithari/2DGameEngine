#pragma once
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Definitions.h"

namespace ecs
{
	class ECSFactory
	{
	public:
		ECSFactory( EntityManager& entityManager, ResourceManager& resManager );
		Entity& CreateSkeleton();
		Entity& CreatePlayer();
	private:
		EntityManager& entityManager;
		ResourceManager& resManager;
	};
}