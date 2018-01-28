#pragma once
#include "ECS.h"

class ECSFactory
{
public:
	ECSFactory( ECS& manager);
	Entity& CreateSkeleton();
private:
	ECS& manager;
};

