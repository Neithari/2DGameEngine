#pragma once
#include "ECS.h"

class ECSFactory
{
public:
	ECSFactory( ECS& manager);
	Entity& CreateSkeleton();
	~ECSFactory();
private:
	ECS& manager;
};

