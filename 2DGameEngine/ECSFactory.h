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

		void CreateEnvironment();
		void CreatePlayer();
		void CreateSkeleton( int count );
		void CreateCuphead( int count );
	private:
		EntityManager& entityManager;
		ResourceManager& resManager;
	};
}