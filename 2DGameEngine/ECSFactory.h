#pragma once
#include "ECS.h"
#include "ResourceManager.h"

class ECSFactory
{
public:
	ECSFactory( ECS& ecsManager, ResourceManager& resManager );
	Entity& CreateSkeleton();
private:
	ECS& ecsManager;
	ResourceManager& resManager;
};

